#ifndef DATABASEMANAGER_H_
#define DATABASEMANAGER_H_

#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>

#include "Usuario.h"
class DatabaseManager {
    DatabaseManager();
    QSqlDatabase m_db;

    public:
    static DatabaseManager& instance();
    DatabaseManager(const DatabaseManager&) = delete;
    void operator= (const DatabaseManager&) = delete;

    bool connect();
    bool addClient(Usuario* _user);
    bool addProvider(Usuario* _user);
    QSqlDatabase database() const;

};


#endif // DATABASEMANAGER_H_
