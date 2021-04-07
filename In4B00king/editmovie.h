#ifndef EDITMOVIE_H
#define EDITMOVIE_H

#include <QDialog>
#include <movies.h>

namespace Ui {
class editMovie;
}

class editMovie : public QDialog
{
    Q_OBJECT

public:
    explicit editMovie(QWidget *parent = nullptr);
    ~editMovie();

private slots:
    void on_Close_clicked();
    void receiveData(QString);


    void on_EditMovie_clicked();

private:
    Ui::editMovie *ui;
    QString oldmoviename;
};

#endif // EDITMOVIE_H
