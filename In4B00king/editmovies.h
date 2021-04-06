#ifndef EDITMOVIES_H
#define EDITMOVIES_H
#include "mydb.h"
#include "movies.h"
#include "editmovie.h"

#include <QDialog>

namespace Ui {
class editmovies;
}

class editmovies : public QDialog
{
    Q_OBJECT

public:
    explicit editmovies(QWidget *parent = nullptr);
    ~editmovies();


private slots:
    void on_CreateMovie_clicked();

    void on_editmovie_clicked();

    void on_Close_clicked();

    void on_deletemovie_clicked();

signals:
    void sendData(QString);


private:
    Ui::editmovies *ui;
    editMovie *movieinfopage;
};

#endif // EDITMOVIES_H
