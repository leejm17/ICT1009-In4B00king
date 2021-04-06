#include "user.h"
#include "mydb.h"
#include <QMessageBox>

user::user()
{

}

customer::customer(){

}

customer::customer(QString username){
    user::GetUserVariables(username);
}

administrator::administrator(){

}

administrator::administrator(QString username){
    user::GetUserVariables(username);
}

int administrator::getpriv(){
    QSqlQuery query(MyDB::getInstance()->getDBInstance());
    query.prepare("Select * FROM User WHERE email_ID='" + this->getEmail() + "';");
    if(!query.exec()){
        qDebug() << query.lastError().text() << query.lastQuery();
    }else{
        qDebug() << "Successful read";
        while(query.next()){
            this->privileges = query.value(8).toInt();
        }
    }
    return privileges;
}

void user::GetUserVariables(QString username){
    QSqlQuery query(MyDB::getInstance()->getDBInstance());
    query.prepare("Select * FROM User WHERE email_ID='" + username + "';");
    if(!query.exec()){
        qDebug() << query.lastError().text() << query.lastQuery();
    }else{
        qDebug() << "Successful read";

        while(query.next()){
            this->email = query.value(0).toString();
            this->name = query.value(2).toString() + query.value(3).toString();
            this->fname = query.value(2).toString();
            this->lname = query.value(3).toString();
            this->age = query.value(4).toInt();
            this->gender = query.value(5).toString();
            this->about = query.value(6).toString();
            this->type = query.value(7).toString();
        }
    }
}

QString user::getName() const
{
    return name;
}


int user::getAge() const
{
    return age;
}

QString user::getGender() const
{
    return gender;
}

QString user::getAbout() const
{
    return about;
}

QString user::getType() const
{
    return type;
}

QString user::getFname() const
{
    return fname;
}

QString user::getLname() const
{
    return lname;
}

QString user::getEmail() const
{
    return email;
}
