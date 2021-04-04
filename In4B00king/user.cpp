#include "user.h"
#include "mydb.h"
user::user()
{

}

void user::GetUserVariables(QString username){
    qDebug() << "I am inside GetUserVariables();";

    QSqlQuery query(MyDB::getInstance()->getDBInstance());
    query.prepare("Select * FROM User WHERE email_ID='" + username + "';");

    if(!query.exec()){
        qDebug() << "wtf" << query.lastError().text() << query.lastQuery();
    }else{
        qDebug() << "I am here at else";
        while(query.next()){
            qDebug() << query.lastQuery();
            qDebug() << "I am the Next "<< query.value(0).toString();
            this-> email_ID = query.value(0).toString();
            QString fname = query.value(2).toString();
            QString lname = query.value(3).toString();
            this-> name = fname + lname;
            this-> age = query.value(4).toString();
            this-> about = query.value(5).toString();
            this-> type = query.value(7).toString();
        }
    }
}
