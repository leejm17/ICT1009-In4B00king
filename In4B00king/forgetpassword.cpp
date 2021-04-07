#include "forgetpassword.h"
#include "ui_forgetpassword.h"
#include "login.h"
#include <QMessageBox>
#include <curl/curl.h>
#include "register.h"
#include <QCryptographicHash>

forgetpassword::forgetpassword(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::forgetpassword)
{
    ui->setupUi(this);
}

forgetpassword::~forgetpassword()
{
    delete ui;
}

void forgetpassword::on_HomePage_clicked()
{
    close();
}

void forgetpassword::on_resetpassword_clicked()
{
    //Getting information from UI
    QString username = ui->Email->text();
    QString pwd1 = ui->pwd->text();
    QString pwd2 = ui->pwd2->text();
    QString salted_password = username + pwd1;

    // SHA1 Hash
    QByteArray hashed_password = QCryptographicHash::hash(salted_password.toUtf8(),QCryptographicHash::Md5);
    QString inputHash = QLatin1String(hashed_password.toHex());

    if (pwd1.isEmpty()){
        QMessageBox::warning(this, "Please enter new password", "Empty new password!");
    }else if (pwd2.isEmpty()){
        QMessageBox::warning(this, "Please confirm new password", "Empty confirm new password!");
    }else if (pwd1 == pwd2){
        QSqlQuery updatequery(MyDB::getInstance()->getDBInstance());
        updatequery.prepare("UPDATE User SET password ='"+ inputHash +"' WHERE email_ID='"+ username +"';");
        if(!updatequery.exec()){
                qDebug() << updatequery.lastError().text() << updatequery.lastQuery();
        }else{
            qDebug() << "read was successful "<< updatequery.lastQuery();
        }
        QMessageBox::information(this, "Successful Change", "Password has been changed");
        close();
    }else{
        QMessageBox::warning(this, "Password Mismatch", "Password does not match");
    }
}

void forgetpassword::on_resetpassword_3_clicked()
{
    bool emailcheck = false;
    // Initializes SQL.
    QSqlQuery query(MyDB::getInstance()->getDBInstance());
    QString user_email= ui->Email->text();
    query.prepare("SELECT * FROM User WHERE email_ID='" + user_email + "';");
    if(!query.exec()){
            qDebug() << query.lastError().text() << query.lastQuery();
    }else if (query.exec()){
        if(query.next()){
            emailcheck = true;
        }
    }
    if (!emailcheck){
            QMessageBox::warning(this, "Invalid Email", "Email not found!");
    } else{
        //Disable send email button
        ui->resetpassword_3->setEnabled(false);
        email.SendEmail(user_email);
        ui->verifyButton->setEnabled(true);
        QMessageBox::information(this, "Verification", "Email sent! Please check your email and enter the verification code!");
    }


}
// Onclick Event for Verify button.
// Checks OTP and if matches, enable the reset password button.
void forgetpassword::on_verifyButton_clicked()
{
    //Add the checking of curl email
    QString verifyText;
    verifyText = ui->verify->text();
    // Checks if the code they enter matches

    if(verifyText == email.getEmail_OTP()){
        ui->resetpassword->setEnabled(true);
        QMessageBox::information(this, "Verified", "Verification successful");
    }else{
        QMessageBox::information(this, "Verification", "Wrong verification code! Please try again");
    }
}
