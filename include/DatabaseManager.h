#ifndef DATABASEMANAGER_H_
#define DATABASEMANAGER_H_

#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>

class DatabaseManager {
    DatabaseManager();
    QSqlDatabase m_db;

    public:
    static DatabaseManager& instance();
    DatabaseManager(const DatabaseManager&) = delete;
    void operator= (const DatabaseManager&) = delete;

    bool connect();
    QSqlDatabase database() const;

};


#endif // DATABASEMANAGER_H_
