#include "editprofile.h"
#include "ui_editprofile.h"
#include <QCryptographicHash>

editprofile::editprofile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editprofile)
{
    ui->setupUi(this);


}

editprofile::~editprofile()
{
    delete ui;
}

void editprofile::receiveData(customer newcust){
    edituser = newcust;
    edituser.loadCust(newcust.getEmail());
    ui->Fname->setText(edituser.getFname());
    ui->Lname->setText(edituser.getLname());
    ui->Age->setValue(edituser.getAge());
    ui->about->setText(edituser.getAbout());
    if (edituser.getGender() == "male"){
        ui->Male->setChecked(true);
    }else{
        ui->Female->setChecked(true);
    }

}


void editprofile::on_Close_clicked()
{
    hide();
}

void editprofile::on_profilechange_clicked()
{
    QString fname, lname, about, gender, age;
    fname = ui->Fname->text();
    lname = ui->Lname->text();
    age = ui->Age->text();
    about = ui->about->text();
    if(ui->Male->isChecked()){
        gender = "Male";
    }else if (ui->Female->isChecked()){
        gender = "Female";
    }
    QString username = edituser.getEmail();
    QString password = ui->cpwd->text();
    QString salted_password = username + password;
    // SHA1 Hash
    QByteArray hashed_password = QCryptographicHash::hash(salted_password.toUtf8(),QCryptographicHash::Md5);
    QString inputHash = QLatin1String(hashed_password.toHex());

    QSqlQuery query(MyDB::getInstance()->getDBInstance());
    query.prepare("Select * FROM User WHERE email_ID='" + username + "' AND password='" + inputHash + "';");
    if(!query.exec()){
        qDebug() << query.lastError().text() << query.lastQuery();
    }else{
        if(query.next()){
            qDebug() << "read was successful "<< query.lastQuery();


            QSqlQuery updatequery(MyDB::getInstance()->getDBInstance());
            updatequery.prepare("UPDATE User SET first_name ='"+ fname +"', last_name='" + lname +"', age="+age+", about='"+about
                          +"', gender='"+ gender +"' WHERE email_ID='"+ username +"';");
            if(!updatequery.exec()){
                    qDebug() << updatequery.lastError().text() << updatequery.lastQuery();
            }else{
                qDebug() << "read was successful "<< updatequery.lastQuery();
            }
            QMessageBox::information(this, "Edit profile", "Details have been changed");
            hide();

        }else{
            qDebug() << "read was successful "<< query.lastQuery();
            QMessageBox::warning(this, "Login", "Wrong password");
        }
    }
    qApp->processEvents();

}

void editprofile::on_pwdchange_clicked()
{
    QString username = edituser.getEmail();
    QString password = ui->cpwd2->text();
    QString salted_password = username + password;
    // SHA1 Hash
    QByteArray hashed_password = QCryptographicHash::hash(salted_password.toUtf8(),QCryptographicHash::Md5);
    QString inputHash = QLatin1String(hashed_password.toHex());

    QString newpassword = ui->npwd->text();
    QString newpassword2 = ui->cnpwd->text();
    QString salted_password2 = username + newpassword;
    // SHA1 Hash
    QByteArray hashed_password2 = QCryptographicHash::hash(salted_password2.toUtf8(),QCryptographicHash::Md5);
    QString inputHash2 = QLatin1String(hashed_password2.toHex());

    QSqlQuery query(MyDB::getInstance()->getDBInstance());
    query.prepare("Select * FROM User WHERE email_ID='" + username + "' AND password='" + inputHash + "';");
    if(!query.exec()){
        qDebug() << query.lastError().text() << query.lastQuery();
    }else{
        if(query.next()){
            qDebug() << "read was successful "<< query.lastQuery();

            if (newpassword.isEmpty()){
                QMessageBox::warning(this, "Please enter new password", "Empty new password!");
            }else if (newpassword2.isEmpty()){
                QMessageBox::warning(this, "Please confirm new password", "Empty confirm new password!");
            }else if (newpassword == newpassword2){
                QSqlQuery updatequery(MyDB::getInstance()->getDBInstance());
                updatequery.prepare("UPDATE User SET password ='"+ inputHash2 +"' WHERE email_ID='"+ username +"';");
                if(!updatequery.exec()){
                        qDebug() << updatequery.lastError().text() << updatequery.lastQuery();
                }else{
                    qDebug() << "read was successful "<< updatequery.lastQuery();
                }
                QMessageBox::information(this, "Successful Change", "Password has been changed");
                hide();
            }else{
                QMessageBox::warning(this, "Password Mismatch", "Password does not match");
            }

        }else{
            qDebug() << "read was successful "<< query.lastQuery();
            QMessageBox::warning(this, "Current Password Wrong", "Wrong current password");
        }
    }
}
