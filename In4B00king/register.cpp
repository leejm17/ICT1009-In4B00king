#include "register.h"
#include "ui_register.h"
#include "login.h"
#include <QMessageBox>

Register::Register(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
    ui->comboBox->addItem("@gmail.com");
    ui->comboBox->addItem("@hotmail.com");
}

Register::~Register()
{
    delete ui;
}

void Register::on_Register_2_clicked()
{
    QString gender,email, pwd, pwd2, fname, lname;
    bool emailcheck = false;
    bool accountcreated = false;
    email = ui->Email->text() + ui->comboBox->currentText();
    pwd = ui->Password->text();
    pwd2 = ui->Password_2->text();
    fname = ui->Fname->text();
    lname = ui->Lname->text();
    QString age = ui->Age->text();
    QSqlQuery query(MyDB::getInstance()->getDBInstance());
    query.prepare("SELECT * FROM User WHERE email_ID='" + email + "';");
    if(!query.exec()){
            qDebug() << query.lastError().text() << query.lastQuery();
    }else if (query.exec()){
        if(query.next()){
            emailcheck = true;
        }
    }
    if(ui->Male->isChecked()){
        gender = "Male";
    }else if (ui->Female->isChecked()){
        gender = "Female";
    }
    if (ui->Email->text().isEmpty()){
        QMessageBox::warning(this, "Empty Email", "Please enter your email!");
    }else if (ui->Password->text().isEmpty() || ui->Password->text().isEmpty()){
        QMessageBox::warning(this, "Empty Password", "Please enter your password!");
    }else if(pwd != pwd2) {
        QMessageBox::warning(this, "Incorrect password", "Password does not match!");
    }else if (ui->Fname->text().isEmpty()){
        QMessageBox::warning(this, "Empty first name", "Please enter your first name!");
    }else if (ui->Lname->text().isEmpty()){
        QMessageBox::warning(this, "Empty last name", "Please enter your last name!");
    }else if (gender.isEmpty()){
        QMessageBox::warning(this, "Invalid gender", "Please select your gender!");
    }else if (emailcheck){
        QMessageBox::warning(this, "Duplicate Email", "Please enter a new email, email has been used already!");
    }else{
        QMessageBox::StandardButton reply = QMessageBox::question(this, "Register Account", "Are you sure you want to register this account?\nEmail:"+
                                                                  email + "\nFirst name:" + fname + "\nLast name:" + lname + "\nAge:" +
                                                                  age + "\nGender:" + gender, QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            qDebug() << "Yes was clicked";
            QSqlQuery query(MyDB::getInstance()->getDBInstance());
            query.prepare("INSERT INTO User(email_ID,password,first_name,last_name,age,gender,type) VALUES (:email, :password, :fname, :lname, :age, :gender, 'customer')");
            query.bindValue(":email", email);
            query.bindValue(":password", pwd);
            query.bindValue(":fname", fname);
            query.bindValue(":lname", lname);
            query.bindValue(":age", age);
            query.bindValue(":gender", gender);
            Login *loginpage = new Login();
            loginpage->show();
            accountcreated = true;
        } else {
            qDebug() << "Yes was not clicked";
        }
    }
    if (accountcreated){
        this->close();
    }
}
