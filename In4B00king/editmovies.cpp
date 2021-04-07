#include "editmovies.h"
#include "ui_editmovies.h"
#include "movies.h"
#include <QMessageBox>
#include <QSqlTableModel>

editmovies::editmovies(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editmovies)
{
    ui->setupUi(this);
    //Add movie name to combo box for administrator to select
    QList<QString> movielist = MovieListInfo().getMovieNameList();
    for (int i = 0; i < movielist.size(); i++){
        QString moviename = movielist.at(i);
        qDebug() << "movie: " + moviename;
        ui->movieCombo->addItem(movielist.at(i));
    }
}

editmovies::~editmovies()
{
    delete ui;
}

//Recieve privilege from main page to check if admin can delete and edit movie
void editmovies::receiveData(QString priv){
    if (priv == "2"){
        qDebug() << "Priv is 2";
        ui->deletemovie->setEnabled(false);
        ui->editmovie->setEnabled(false);
    }
}



void editmovies::on_CreateMovie_clicked()
{
    //Get movie information from UI
    QString Mname = ui->Mname->text();
    QString Duration = ui->Duration->text();
    QString Sdate = ui->Sdate->text();
    QString Edate = ui->Edate->text();
    QString Desc = ui->MDesc->text();
    QDate debut = ui->Sdate->date();
    QDate finale = ui->Edate->date();

    //Perform checks for user input on movie information
    if (Mname.isEmpty()){
        QMessageBox::warning(this, "Create Movie", "Please enter Movie Name!");
    }else if (Duration.isEmpty()){
        QMessageBox::warning(this, "Create Movie", "Please enter Movie Duration!");
    }else if (Sdate.isEmpty()){
        QMessageBox::warning(this, "Create Movie", "Please enter Start date!");
    }else if (Edate.isEmpty()){
        QMessageBox::warning(this, "Create Movie", "Please enter End date!");
    }else if (debut > finale){
        QMessageBox::warning(this, "Create Movie", "Start date cannot be after end date!");
    }else if (Desc.isEmpty()){
        QMessageBox::warning(this, "Create Movie", "Please enter Movie Description!");
    }else{
        //Create movie
        MovieInfo newmovie(Mname, Duration.toInt(), Sdate, Edate, Desc);
        QMessageBox::information(this, "Create movie", "Movie have been added!");
        hide();
    }
}


void editmovies::on_editmovie_clicked()
{
    //Show edit movie page
    movieinfopage = new editMovie(this);
    movieinfopage->show();
    QString moviename = ui->movieCombo->currentText();
    connect(this, SIGNAL(sendData(QString)), movieinfopage, SLOT(receiveData(QString)));
    emit sendData(moviename);

}

void editmovies::on_Close_clicked()
{
    hide();
}

void editmovies::on_deletemovie_clicked()
{
    //Delete movie from database
    QString moviename = ui->movieCombo->currentText();
    MovieInfo delMovie(moviename);
    delMovie.deleteMovie_Db(moviename);
    QMessageBox::information(this, "Delete movie", "Movie: "+ moviename +" has been deleted!");
    hide();

}
