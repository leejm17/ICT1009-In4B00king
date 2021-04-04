#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QDialog>
#include "mydb.h"

namespace Ui {
class Mainpage;
}

class Mainpage : public QDialog
{
    Q_OBJECT

public:
    explicit Mainpage(QWidget *parent = nullptr);
    ~Mainpage();

private:
    Ui::Mainpage *ui;
};

#endif // MAINPAGE_H
