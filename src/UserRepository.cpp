#include "../include/database/UserRepository.h"
#include "../include/database/DatabaseManager.h"
#include "qsize.h"

#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>

qsizetype UserRepository::insertClient(const Cliente &_client) {
    QSqlQuery query(DatabaseManager::instance().database());

    if (!query.prepare("INSERT INTO usuarios (tipo_usuario, nome, email, cpf, "
                       "data_nascimento, foto_perfil) VALUES ('CLIENTE', :nome, "
                       ":email, :cpf, :dataNascimento, :fotoPerfil) RETURNING id")) {

        qDebug() << "Error at preparing Database Query!";
        return false;
    }

    query.bindValue(":nome", _client.getNome());
    query.bindValue(":email", _client.getEmail());
    query.bindValue(":cpf", _client.getCpf());
    query.bindValue(":dataNascimento", _client.getDataNascimento());
    query.bindValue(":fotoPerfil", _client.getFotoPerfil());


    if (query.exec()) {
      if (query.next()) {
          qsizetype _id_returned = query.value(0).toInt();
          qDebug() << "Usuario inserido com ID " << _id_returned;
          return _id_returned;
      }
    } else {
        qDebug() << "Erro ao inserir: " << query.lastError().text();

    }

    return -1;
}

qsizetype UserRepository::insertSupplier(const Fornecedor &_supplier) {
    return -1;

}

Cliente* UserRepository::loginUser(const QString &email, const QString &cpf) {

    QSqlQuery query(DatabaseManager::instance().database());
    if(!query.prepare("SELECT * FROM usuarios WHERE email = :_email AND cpf = :_cpf"))
        return nullptr;

    query.bindValue(":_email", email);
    query.bindValue(":_cpf", cpf);

    if (!query.exec()) {
        qDebug() << "Error at Searching User in the Database!" << query.lastError().text();
        return nullptr;
    }

    if (query.next()) {
        QString _nome = query.value("nome").toString();
        QString _email = query.value("email").toString();
        QString _cpf   = query.value("cpf").toString();
        QString _dataNasc = query.value("data_nascimento").toString();
        QString _fotoPerfil = query.value("foto_perfil").toString();
        QString _tipo_usuario = query.value("tipo_usuario").toString();
        qsizetype _id = query.value("id").toInt();


        if (_tipo_usuario == "CLIENTE")
            return new Cliente(_nome, _email, _cpf, _dataNasc, _fotoPerfil, _id);
        else
            // TODO: get supplier fields;
            return nullptr;
    }

    qDebug() << "Error at login User" << query.lastError().text();

    return nullptr;

}
