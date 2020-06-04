#include "db.h"

DB* DB::instance = nullptr;

DB::DB()
{
    init();
}

DB::~DB()
{
   qDebug() << "closing database connection";
   db.close();
}

void DB::init()
{
    qDebug() << "in init()";
    db = QSqlDatabase::addDatabase("QSQLITE", "Data");
    db.setDatabaseName("/home/hayouniaymen/Documents/QT_Projects/BikeParking/cppbuzz_bikeparking.sqlite");

    if(QFile::exists("/home/hayouniaymen/Documents/QT_Projects/BikeParking/cppbuzz_bikeparking.sqlite"))
            qDebug() << "DB file exist";
        else
           qDebug() << "DB file doesn't exists";

        if (!db.open())
            qDebug() << db.lastError().text();
        else
            qDebug() << "Database loaded successfull!";

}

DB *DB::getInstance()
{
    qDebug() << "in DB::getInstance()";

    if(instance == nullptr)
        instance = new DB();

    return instance;
}

QSqlDatabase DB::getDBInstance()
{
    qDebug() <<"in getDBInstance()";
    return db;
}

void DB::ResetInstance()
{
      qDebug() << "deleting instance of MyDB";
      delete instance;
      instance = nullptr;
}
