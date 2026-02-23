#include "../include/DatabaseManager.h"

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

QSqlDatabase DatabaseManager::database() const {
    return m_db;

}
