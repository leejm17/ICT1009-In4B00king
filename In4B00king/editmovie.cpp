#include "editmovie.h"
#include "ui_editmovie.h"

editMovie::editMovie(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editMovie)
{
    ui->setupUi(this);

}

editMovie::~editMovie()
{
    delete ui;
}

void editMovie::on_Close_clicked()
{
    hide();
}

void editMovie::receiveData(QString moviename){
    this->oldmoviename = moviename;
    MovieInfo newmovie(moviename);
    ui->Mname->setText(newmovie.getMovieName());
    ui->Duration->setText(QString::number(newmovie.getMovieDuration()));
    ui->MDesc->setText(newmovie.getMovieDesc());
}

void editMovie::on_EditMovie_clicked()
{
    QString moviename = ui->Mname->text();
    QString duration = ui->Duration->text();
    QString description = ui->MDesc->text();

    QMessageBox::StandardButton reply = QMessageBox::question(this, "Edit Movie", "Are you sure you want to edit this movie?\nMovie name:"+
                                                              moviename + "\nMovie Duration:" + duration + "\nMovie Description:" + description
                                                              , QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        qDebug() << "Yes was clicked";
        MovieInfo editmove(oldmoviename, moviename, duration.toInt(), description);
        hide();
    }else{
        qDebug() << "No was clicked";
    }
}
