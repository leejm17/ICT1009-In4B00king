#ifndef MAINPAGE2_H
#define MAINPAGE2_H

#include <QMainWindow>
#include "movieinformation.h"

namespace Ui {
class Mainpage2;
}

class Mainpage2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit Mainpage2(QWidget *parent = nullptr);
    ~Mainpage2();

private slots:

    void on_SelectButton_clicked();

private:
    Ui::Mainpage2 *ui;
};

#endif // MAINPAGE_H
