#include "../include/database/UserRepository.h"
#include "../include/database/DatabaseManager.h"

#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>

bool UserRepository::insertClient(const Cliente &_client) {
    QSqlQuery query(DatabaseManager::instance().database());

    if (!query.prepare("INSERT INTO usuarios (tipo_usuario, nome, email, cpf, "
                       "data_nascimento, foto_perfil) VALUES ('CLIENTE', :nome, "
                       ":email, :cpf, :dataNascimento, :fotoPerfil)")) {

        qDebug() << "Error at preparing Database Query!";
        return false;
    }

    query.bindValue(":nome", _client.getNome());
    query.bindValue(":email", _client.getEmail());
    query.bindValue(":cpf", _client.getCpf());
    query.bindValue(":dataNascimento", _client.getDataNascimento());
    query.bindValue(":fotoPerfil", _client.getFotoPerfil());


    if (!query.exec()) {
        qDebug() << "Error at executing Database Query";
        return false;
    }
    return true;

}

bool UserRepository::insertSupplier(const Fornecedor &_supplier) {
    return true;

}
