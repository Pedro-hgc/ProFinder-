#include "../include/DatabaseManager.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>

DatabaseManager &DatabaseManager::instance() {

    static DatabaseManager _instance;
    return _instance;
}

DatabaseManager::DatabaseManager() {
    m_db = QSqlDatabase::addDatabase("QPSQL");
    m_db.setHostName("localhost");
    m_db.setPort(5432);
    m_db.setDatabaseName("ProFinderDb");
    m_db.setUserName("postgres");

}
bool DatabaseManager::connect () {
    if (m_db.isOpen()) return true;

    if (!m_db.open()) {
        qDebug() << "Erro ao se conectar com o Banco de Dados!" << m_db.lastError().text();
        return false;
    }

    return true;
}

bool DatabaseManager::addClient(Usuario *_user) {
    QSqlQuery query(DatabaseManager::instance().database());

    if (!query.prepare("INSERT INTO usuarios (tipo_usuario, nome, email, cpf, "
                       "data_nascimento, foto_perfil) VALUES ('CLIENTE', :nome, "
                       ":email, :cpf, :dataNascimento, :fotoPerfil)")) {

        qDebug() << "Error at preparing Database Query!";
        return false;
    }

    query.bindValue(":nome", _user->getNome());
    query.bindValue(":email", _user->getEmail());
    query.bindValue(":cpf", _user->getCpf());
    query.bindValue(":dataNascimento", _user->getDataNascimento());
    query.bindValue(":fotoPerfil", _user->getFotoPerfil());


    if (!query.exec()) {
        qDebug() << "Error at executing Database Query";
        return false;
    }
    return true;
}
QSqlDatabase DatabaseManager::database() const {
    return m_db;

}
