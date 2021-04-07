#include "mydb.h"
#include <QtConcurrent>
MyDB* MyDB::instance = nullptr;

MyDB::MyDB()
{
    init();
}

void MyDB::init()
{
    db = QSqlDatabase::addDatabase("QSQLITE", "Data");
    db.setDatabaseName("../in4b00king.db");

    // Checks whether DB file exists.
    try {
        if(QFile::exists("../in4b00king.db"))
                qDebug() << "DB file exist.";
            else
               qDebug() << "DB file doesn't exists.";

            if (!db.open())
                qDebug() << db.lastError().text();
                throw 1;
            else
                qDebug() << "Database loaded successfully!";
    }catch(std::exception& e){
       qDebug() << e.what();

    }
    catch (...) {
        qDebug() << "Unknown Error";
    }


}

MyDB *MyDB::getInstance()
{
    if(instance == nullptr)
        instance = new MyDB();

    return instance;
}

QSqlDatabase MyDB::getDBInstance()
{
    //qDebug() <<"in getDBInstance()";
    return db;
}

void MyDB::ResetInstance()
{
      //qDebug() << "deleting instance of MyDB...";
      delete instance;
      instance = nullptr;
}

MyDB::~MyDB()
{
   //qDebug() << "closing database connection...";
   db.close();
}
