#ifndef USER_H
#define USER_H

#include <QMainWindow>
#include <QMessageBox>

using namespace std;

class user
{
public:
    user();
    void GetUserVariables(QString username);
    QString type;
private:
    QString email_ID;
    QString name;
    QString age;
    QString about;

};

#endif // USER_H
