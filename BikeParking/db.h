#ifndef DB_H
#define DB_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QFile>
#include <QDebug>
#include <QSqlError>
#include <QSqlQueryModel>


class DB
{
private:
    DB();
    static DB *instance;
    void init();
    QSqlDatabase db;
public:
    static DB* getInstance();
    static void ResetInstance();
    QSqlDatabase getDBInstance();
    ~DB();
};

#endif // DB_H
