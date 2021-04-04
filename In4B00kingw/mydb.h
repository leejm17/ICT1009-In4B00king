#ifndef MYDB_H
#define MYDB_H
#include <QDebug>

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QFile>
#include <QDebug>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQueryModel>

class MyDB
{
private:
    MyDB();
    static MyDB *instance;
    void init();
    QSqlDatabase db;
public:
    static MyDB* getInstance();
    static void ResetInstance();
    QSqlDatabase getDBInstance();
    ~MyDB();
};
#endif // MYDB_H
