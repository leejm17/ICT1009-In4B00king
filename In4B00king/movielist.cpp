#include "movielist.h"
#include "ui_movielist.h"
#include <QPixmap>
#include <QMessageBox>

MovieList::MovieList(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MovieList)
{
    ui->setupUi(this);
    economyHall = new EconomyHall(this);
    diamondHall = new DiamondHall(this);
    seatSelection = new SeatSelection(this);
    confirmationScreen = new ConfirmationScreen(this);

    connect(economyHall,SIGNAL(showSeatSelection()),seatSelection,SLOT(showSeatSelection()));
    connect(diamondHall,SIGNAL(showSeatSelection()),seatSelection,SLOT(showSeatSelection()));
    connect(seatSelection,SIGNAL(showConfirmation(QString)),confirmationScreen,SLOT(showConfirmation(QString)));
    connect(confirmationScreen,SIGNAL(updateSeats()),economyHall,SLOT(updateSeats()));
    connect(confirmationScreen,SIGNAL(updateSeats()),diamondHall,SLOT(updateSeats()));
    connect(this,SIGNAL(updateSeats()),economyHall,SLOT(updateSeats()));
    connect(this,SIGNAL(updateSeats()),diamondHall,SLOT(updateSeats()));

    db = MyDB::getInstance()->getDBInstance();

    currentOffset = 0;
    updateUI();
}

MovieList::~MovieList()
{
    delete ui;
}

void MovieList::on_SelectButton_clicked()
{
    //QMessageBox::information(this,"Hi","is_clicked");
    emit updateSeats();
    economyHall->show();
    //movieinformation = new MovieInformation(this);
    //movieinformation->show();
}

void MovieList::on_SelectButton_2_clicked()
{
    emit updateSeats();
    diamondHall->show();
}

void MovieList::updateUI()
{
    struct Movie
    {

        QLabel* title;
        QLabel* duration;

    };

    // just some bindings
    Movie movie0;
    movie0.title = ui->Movie_Title_1;
    movie0.duration = ui->Duration_1;

    Movie movie1;
    movie1.title = ui->Movie_Title_2;
    movie1.duration = ui->Duration_2;

    Movie movie2;
    movie2.title = ui->Movie_Title_3;
    movie2.duration = ui->Duration_3;

    Movie movies[3];
    movies[0] = movie0;
    movies[1] = movie1;
    movies[2] = movie2;

    // styling
    QPalette sample_palette;
    sample_palette.setColor(QPalette::WindowText, Qt::white);

    movies[0].title->setPalette(sample_palette);
    movies[0].duration->setPalette(sample_palette);

    movies[1].title->setPalette(sample_palette);
    movies[1].duration->setPalette(sample_palette);

    movies[2].title->setPalette(sample_palette);
    movies[2].duration->setPalette(sample_palette);

    qDebug() << "currentOffset: " << currentOffset;

    QSqlQuery query(db);
    query.prepare("SELECT name, duration FROM MovieList LIMIT 3 OFFSET " + QString(std::to_string(3*currentOffset).c_str()));
    if(!query.exec())
    {
        qDebug() << query.lastError().text() << query.lastQuery();
    }
    else
    {
        int currentIndex = 0;
        while (query.next())
        {
            /**
            if (currentIndex == 3)
            {
                currentIndex = 0;
            }**/

            movies[currentIndex].title->setText(query.value(0).toString());
            auto duration = query.value(1).toString();
            if (duration !=  QString("TBA"))
            {
                duration += QString(" mins");
            }

            movies[currentIndex].duration->setText(duration);

            currentIndex++;

            qDebug() << "title: " << query.value(0).toString().toUtf8().constData();
            qDebug() << " duration : " << query.value(1).toString().toUtf8().constData();
        }
    }
    query.finish();


    QPixmap pix(":/resources/img/Tom_and_Jerry.jpg");
    ui->Movie1->setPixmap(pix.scaled(221,300,Qt::KeepAspectRatio));
    QPixmap pix2(":/resources/img/Godzilla_Vs_Kong.jpg");
    ui->Movie2->setPixmap(pix2.scaled(221,300,Qt::KeepAspectRatio));
    QPixmap pix3(":/resources/img/FF9.jpg");
    ui->Movie3->setPixmap(pix3.scaled(221,300,Qt::KeepAspectRatio));
    /**


    setText("FF9");
    ui->Duration_1->setText("120min");

    ui->Movie2->setPixmap(pix.scaled(221,300,Qt::KeepAspectRatio));
    ui->Movie_Title_2->setText("FF9");
    ui->Duration_2->setText("120min");

    ui->Movie3->setPixmap(pix.scaled(221,300,Qt::KeepAspectRatio));
    ui->Movie_Title_3->setText("FF9");
    ui->Duration_3->setText("120min");
    **/
}



void MovieList::on_Next_Button_clicked()
{
    currentOffset++;
    updateUI();
}

void MovieList::on_Select_Button1_clicked()
{
    hide();
    (new MovieInformation())->show();
}
