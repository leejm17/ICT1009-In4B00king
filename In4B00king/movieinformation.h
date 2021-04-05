#ifndef MOVIEINFORMATION_H
#define MOVIEINFORMATION_H

#include <QMainWindow>
#include <QDebug>
#include "movies.h"

namespace Ui {
class MovieInformation;
}

class MovieInformation : public QMainWindow
{
    Q_OBJECT

public:
    explicit MovieInformation(QWidget *parent = nullptr);
    ~MovieInformation();

private slots:
    void receiveData(MovieInfo);

    void on_Back_clicked();

private:
    Ui::MovieInformation *ui;
};

#endif // MOVIEINFORMATION_H
