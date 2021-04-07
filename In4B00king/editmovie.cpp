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

//Receive movie name from previous page
void editMovie::receiveData(QString moviename){
    this->oldmoviename = moviename;
    MovieInfo newmovie(moviename);
    newmovie.getMovieDetails_Db();
    //Set informaiton of movie into UI
    ui->Mname->setText(newmovie.getName());
    ui->Duration->setText(QString::number(newmovie.getDuration()));
    ui->MDesc->setText(newmovie.getDesc());
}

void editMovie::on_EditMovie_clicked()
{
    //Get movie informaiton from UI to update into database
    QString moviename = ui->Mname->text();
    QString duration = ui->Duration->text();
    QString description = ui->MDesc->text();

    QMessageBox::StandardButton reply = QMessageBox::question(this, "Edit Movie", "Are you sure you want to edit this movie?\nMovie name:"+
                                                              moviename + "\nMovie Duration:" + duration + "\nMovie Description:" + description
                                                              , QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        qDebug() << "Yes was clicked";
        MovieInfo editmove(oldmoviename, moviename, duration.toInt(), description);
        editmove.updateMovie_Db();
        hide();
    }else{
        qDebug() << "No was clicked";
    }
}
