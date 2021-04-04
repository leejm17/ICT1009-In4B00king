#include "editprofile.h"
#include "ui_editprofile.h"

editprofile::editprofile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editprofile)
{
    ui->setupUi(this);
    //QSqlQuery query(MyDB::getInstance()->getDBInstance());
    //query.prepare("");
}

editprofile::~editprofile()
{
    delete ui;
}
