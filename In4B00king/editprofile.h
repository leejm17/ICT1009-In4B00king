#ifndef EDITPROFILE_H
#define EDITPROFILE_H

#include "mydb.h"
#include <QDialog>

namespace Ui {
class editprofile;
}

class editprofile : public QDialog
{
    Q_OBJECT

public:
    explicit editprofile(QWidget *parent = nullptr);
    ~editprofile();

private:
    Ui::editprofile *ui;
};

#endif // EDITPROFILE_H
