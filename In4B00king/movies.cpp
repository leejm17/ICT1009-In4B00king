/*
    Objective: Source file for Movie classes.
    Author: Lee Jun Ming (1802971).
*/

#include <movies.h>
#include <QDate>
#include <QCalendar>
#include <QLabel>

/* default constructor */
MovieListInfo::MovieListInfo() {

}

/* (1) Call this func in MainScreen_Cust to display an array/series of movies currently on show. */
void MovieListInfo::displayMovieList(Movie* movies) {
    getMovieList_Db();  // populate movieNameList & movieDurationList variables
    qDebug() << "hi3";
    for (int cnt=0; cnt < this->movieNameList.size(); cnt++) {
        qDebug() << "hi4";
        QString duration = movieDurationList.at(cnt);
        if (duration == "0") {
            duration = "TBA";
        } else {
            duration += QString(" mins");
        }
        movies[cnt].title->setText(this->movieNameList.at(cnt));
        movies[cnt].duration->setText(duration);
    }
    qDebug() << "hi5";
}

/* DB QUERY to retrieves a list of movies & duration from DB & append to their respective arrays. */
void MovieListInfo::getMovieList_Db() {
    QSqlQuery query(MyDB::getInstance()->getDBInstance());
    query.prepare(
        "SELECT movie_ID, name, duration"
        " FROM MovieList"
        " WHERE (debut <= DATE() AND finale >= DATE());"
    );

    if(!query.exec()) {
        qDebug() << query.lastError().text() << query.lastQuery();
    } else {
        qDebug() << "getMovieList_Db() read query for all movies was successful.";
        while(query.next()) {
            movieNameList.append(query.value(1).toString());
            movieDurationList.append(query.value(2).toString());
        }
    }
    MyDB::ResetInstance();
}


/* (2) When Customer clicks on a Movie in MainScreen via this Constructor, initialise the data members. */
/* Calls getMovieDetails_Db() to retrieve description & array of movieDates, then initialise them. */
/* Redirect Customer to MovieDetails screen. */
MovieInfo::MovieInfo(QString movieName, int duration) {
    this->movieName = movieName;
    this->movieDuration = duration;
    getMovieDetails_Db();

    // code to redirect customer to movieinformation page
}

/* Call getMovieDetails_Db() from MovieInfo() Constructor. */
void MovieInfo::getMovieDetails_Db() {
    QSqlQuery query(MyDB::getInstance()->getDBInstance());
    query.prepare(
        "SELECT debut, description FROM MovieList"
        " WHERE (name=:name);"
    );
    query.bindValue(":name", this->movieName);

    if(!query.exec()) {
        qDebug() << query.lastError().text() << query.lastQuery();
    } else {
        qDebug() << "getMovieDetails_Db() read query for " << this->movieName
                 << " was successful.";
        while(query.next()) {
            this->movieDebut = query.value(0).toString();
            this->movieDesc = query.value(1).toString();
        }
    }
    MyDB::ResetInstance();
}

/* (3) Call displayMovieDetails() in MovieDetails to display a movie's information with its corresponding timeslots based on a given day. */
void ShowtimesInfo::displayMovieDetails() {
    // code to run when customer clicks on a date in movieinformation page
    QString name;   // var of moviename from ui
    QString date;   // var of moviedate from ui
    ShowtimesInfo::getShowtimes_Db(name, date);
    // display movie showtimes with timeslots & halls array
}

/* (4) When Customer clicks on a movie date, call getShowtimes_Db(). */
/* Retrieves a list of timeslots & hallIDs from DB, and append to their respective arrays. */
void ShowtimesInfo::getShowtimes_Db(QString movieName, QString movieDate) {
    QSqlQuery query(MyDB::getInstance()->getDBInstance());
    query.prepare("SELECT timeslot, hall_ID FROM MovieShowing"
                  " JOIN MovieList ON (MovieShowing.movie_ID = MovieList.movie_ID)"
                  " WHERE (MovieList.name=:name AND MovieShowing.date=:date);");
    query.bindValue(":name", movieName);
    query.bindValue(":date", movieDate);

    if(!query.exec()) {
        qDebug() << query.lastError().text() << query.lastQuery();
    } else {
        qDebug() << "getShowtimes_Db() read query for " << movieName
                 << " on " << movieDate
                 << " was successful.";
        while(query.next()) {
            retrieve_timeslots.append(query.value(0).toString());
            retrieve_halls.append(query.value(1).toInt());
        }
    }
    MyDB::ResetInstance();
}


/* Admin Console: MovieInfo & addMovie_Db() */
/* When Admin creates a new movie in MainScreen_Admin, via this Constructor, initialise the data members. */
/* Call generateMovieDates() to generate dates from movie debut to movie finale. */
/* Call generateShowtimes() to generate showtimes based on a user-supplied movie priority. */
/* Call addMovie_Db() to add movie information + dates + showtimes into respective Tables in DB. */
MovieInfo::MovieInfo(QString movieName, int duration, QString debut, QString finale, QString desc) {
    this->movieName = movieName;
    this->movieDuration = duration;
    this->movieDebut = debut;
    this->movieFinale = finale;
    this->movieDesc = desc;
    generateMovieDates();
    generateShowtimes();
    addMovie_Db();
    /*qDebug() << this->movieName;
    qDebug() << this->movieDuration;
    qDebug() << this->movieDebut;
    qDebug() << this->movieFinale;
    qDebug() << this->movieDesc;
    for (int i=0; i<movieDates.length(); i++) {
        qDebug() << movieDates[i];
    }*/
    /*for (int i=0; i<movieDates.length(); i++) {
        qDebug() << movieDates[i];
    }*/
    /* SELECT MovieList.desc, MovieShowing.date FROM MovieList WHERE (MovieList.name=movieName)
        ON (MovieList.movieId = MovieShowing.movieId). */
}

/* Call this function in MainScreen_Admin to generate an incremental list of movie show dates & append to movieDates[]. */
void MovieInfo::generateMovieDates() {
    QDate debut = QDate::fromString(this->movieDebut, "yyyy-MM-dd");
    QDate finale = QDate::fromString(this->movieFinale, "yyyy-MM-dd");
    //QDate debut = QDate::fromString("2021-12-10", "yyyy-MM-dd");
    //QDate finale = QDate::fromString("2022-02-02", "yyyy-MM-dd");

    if (debut > finale) {
        qDebug() << "Debut cannot be after Finale!";
        exit(1);
    }

    QCalendar qCalendarObj;
    for (int month=debut.month(); month<=12+finale.month(); month++) { // for every month between debut & finale
        if (month > 12) {       // finale.month()+12 in case debut is Dec 2021 & finale is Feb 2022
            break;
        }
        int daysThisMonth = qCalendarObj.daysInMonth(month, debut.year());
        if (debut.month() == finale.month()) {
            for (int day=debut.day(); day<=finale.day(); day++) {
                appendMovieDate(debut.year(), month, day);    // append date to movieDates
            }
        } else if (month == debut.month()) {                       // if month is same as debut month
            for (int day=debut.day(); day<=daysThisMonth; day++) {  // from debut till end of month
                appendMovieDate(debut.year(), month, day);    // append date to movieDates
            }
        } else if (month == finale.month()) {               // else if month is same as finale month
            for (int day=1; day<=finale.day(); day++) {         // from start of month till finale
                appendMovieDate(debut.year(), month, day);    // append date to movieDates
            }
        } else {                                            // else if month is NOT debut nor finale month
            for (int day=1; day<=daysThisMonth; day++) {        // from start of month till end of month
                appendMovieDate(debut.year(), month, day);    // append date to movieDates
            }
        }
        if (month+12 == 12+finale.month()) {       // break if this month is the end of the same calendar year
            break;
        }
    }
}

/* Called by generateMovieDates() to append incremental movie dates to movieDates */
void MovieInfo::appendMovieDate(int year, int month, int day) {
    QString newMonth;
    QString newDay;

    if (month < 10) {                               // ensure month is 2 digits
        newMonth = "0" + QString::number(month);    // append a 0 to front if month is 1 digit
    } else {
        newMonth = QString::number(month);
    }
    if (day < 10) {                                 // ensure day is 2 digits
        newDay = "0" + QString::number(day);        // append a 0 to front if day is 1 digit
    } else {
        newDay = QString::number(day);
    }

    QString date = QString::number(year).append("-")
            .append(newMonth).append("-")
            .append(newDay);
    movieDates.append(date);
}

void MovieInfo::getPriority_Db() {
    QSqlQuery query(MyDB::getInstance()->getDBInstance());
    query.prepare(
        "SELECT movie_ID"
        " FROM MovieList"
        " ORDER BY movie_ID DESC LIMIT 1;"
    );
    if(!query.exec()) {
        qDebug() << query.lastError().text() << query.lastQuery();
    } else {
        qDebug() << "getPriority_Db() read query for last movie added was successful.";
        while(query.next()) {
            this->priority = query.value(0).toInt() % 4;
        }
    }
    MyDB::ResetInstance();  // close DB connection
}

QString MovieInfo::getMovieName()
{
    return movieName;
}

int MovieInfo::getMovieDuration()
{
    return movieDuration;
}
QString MovieInfo::getMovieDebut()
{
    return movieDebut;
}
QString MovieInfo::getMovieDesc()
{
    return movieDesc;
}

/* Call this function in MainScreen_Admin to generate a list of movie show times & match their halls, then append to their respective arrays. */
void MovieInfo::generateShowtimes() {
    getPriority_Db();

    if (priority == 1) {        // super popular movie
        for (int hour=8; hour <= 22; hour++) {
            /* generate for Economy hall */
            if (hour%2 == 0) {                      // 1 economy showtime every 2 hours
                economy_timeslots.append(QString::number(hour).append(":00"));  // 8, 10, 12, 14, 16, 18, 20, 22
                if (hour%4 == 0) { economy_halls.append(1); }   // for 8, 12, 16, 20
                else { economy_halls.append(2); }               // for 10, 14, 18, 22
            }
            /* generate for Diamond hall */
            if (hour>=12 && hour%4 == 0) {   // 1 diamond showtime every 4 hours from 12PM onward
                diamond_timeslots.append(QString::number(hour).append(":00"));  // 12, 16, 20
                diamond_halls.append(7);
            }
        }

    } else if (priority == 2) { // quite popular movie
        for (int hour=8; hour <= 22; hour++) {
            /* generate for Economy hall */
            if (hour%3 == 0) {                          // 1 economy showtime every 3 hours
                economy_timeslots.append(QString::number(hour).append(":00"));  // 9, 12, 15, 18, 21
                if (hour%6 == 0) { economy_halls.append(4); }   // for 12, 18
                else { economy_halls.append(3); }               // for 9, 15, 21
            }
            /* generate fo Diamond hall */
            if (hour>=12 && (hour-1)%4 == 0) {   // 1 diamond showtime every 4 hours from 12PM onward
                diamond_timeslots.append(QString::number(hour).append(":00"));  // 13, 17, 21
                diamond_halls.append(8);
            }
        }

    } else if (priority == 3) { // popular movie
        /* generate for Economy hall */     // 11, 13, 17, 19, 21
        economy_timeslots.append("11:00"); economy_timeslots.append("13:00"); economy_timeslots.append("17:00");
        economy_timeslots.append("19:00"); economy_timeslots.append("21:00");
        economy_halls.append(5); economy_halls.append(6); economy_halls.append(5);
        economy_halls.append(6); economy_halls.append(5);

        /* generate for Diamond hall */     // 14, 18, 22
        diamond_timeslots.append("14:00"); diamond_timeslots.append("18:00"); diamond_timeslots.append("22:00");
        diamond_halls.append(9); diamond_halls.append(9); diamond_halls.append(9);

    } else {                    // normal movie
        for (int hour=8; hour <= 22; hour++) {
            /* generate for Economy hall */
            if (hour%5 == 0) {  // 1 showtime every 5 hours
                economy_timeslots.append(QString::number(hour).append(":00"));  // 10, 15, 20
            }
            /* generate for Diamond hall */
            if (hour>=12 && (hour-3)%4 == 0) {   // 1 diamond showtime every 4 hours from 12PM onward
                diamond_timeslots.append(QString::number(hour).append(":00"));  // 15, 19
                diamond_halls.append(10);
            }
        }
        economy_halls.append(6); economy_halls.append(4); economy_halls.append(4);
    }
}

/* addMovie_Db() adds the movie record into Database tables MovieList, MovieShowing, MovieSeats. */
void MovieInfo::addMovie_Db() {
    QSqlQuery query(MyDB::getInstance()->getDBInstance());

    /* (1) INSERT movie details INTO MovieList */
    query.prepare(
        "INSERT INTO MovieList (name, duration, debut, finale, description)"
        " VALUES (:name, :duration, :debut, :finale, :desc);"
    );
    query.bindValue(":name", this->movieName);
    query.bindValue(":duration", this->movieDuration);
    query.bindValue(":debut", this->movieDebut);
    query.bindValue(":finale", this->movieFinale);
    query.bindValue(":desc", this->movieDesc);

    if(!query.exec()) {
        qDebug() << query.lastError().text() << query.lastQuery();
    } else {
        /*qDebug() << "addMovie() into MovieList write query for " << this->movieName
                 << " was successful.";*/
    }
    qDebug() << "Finished INSERT details INTO MovieList for " << this->movieName;

    /* (2) INSERT details INTO MovieShowing */
    /* (2a) SELECT movie_ID of Movie to add */
    query.prepare(
        "SELECT Movie_ID"
        " FROM MovieList"
        " WHERE (name=:name);"
    );
    query.bindValue(":name", this->movieName);
    if(!query.exec()) {
        qDebug() << query.lastError().text() << query.lastQuery();
    } else {
        /*qDebug() << "addMovie() read query for " << this->movieName
                 << " Movie_ID was successful.";*/
        while(query.next()) {
            this->movieID = query.value(0).toInt();
        }
    }
    qDebug() << "Finished SELECT movie_ID FROM MovieList for " << this->movieName;

    /* (2b) For every Date and their respective Timeslot,
     * INSERT the date, timeslots and halls INTO MovieShowing */
    for (int dateCnt=0; dateCnt < this->movieDates.length(); dateCnt++) {
        for (int slotCnt=0; slotCnt < this->economy_timeslots.length(); slotCnt++) {
            query.prepare(
                "INSERT INTO MovieShowing (movie_ID, date, timeslot, hall_ID)"
                " VALUES (:id, :date, :timeslot, :hall)"
            );
            query.bindValue(":id", this->movieID);
            query.bindValue(":date", this->movieDates[dateCnt]);
            query.bindValue(":timeslot", this->economy_timeslots[slotCnt]);
            query.bindValue(":hall", this->economy_halls[slotCnt]);
            if(!query.exec()) {
                qDebug() << query.lastError().text() << query.lastQuery();
            } else {
                /*qDebug() << "addMovie() into MovieShowing write query for " << this->movieName
                         << " on " << this->movieDates[dateCnt]
                         << " at " << this->economy_timeslots[slotCnt]
                         << " was successful.";*/
            }
        }
        for (int slotCnt=0; slotCnt < this->diamond_timeslots.length(); slotCnt++) {
            query.prepare(
                "INSERT INTO MovieShowing (movie_ID, date, timeslot, hall_ID)"
                " VALUES (:id, :date, :timeslot, :hall)"
            );
            query.bindValue(":id", this->movieID);
            query.bindValue(":date", this->movieDates[dateCnt]);
            query.bindValue(":timeslot", this->diamond_timeslots[slotCnt]);
            query.bindValue(":hall", this->diamond_halls[slotCnt]);
            if(!query.exec()) {
                qDebug() << query.lastError().text() << query.lastQuery();
            } else {
                /*qDebug() << "addMovie() into MovieShowing write query for " << this->movieName
                         << " on " << this->movieDates[dateCnt]
                         << " at " << this->diamond_timeslots[slotCnt]
                         << " was successful.";*/
            }
        }
    }
    qDebug() << "Finished INSERT details INTO MovieShowing for " << this->movieName;

    /* (3) INSERT INTO MovieSeats to make Seats available for booking */
    /* (3a) SELECT show_ID and their respective seat_ID & seat's condition based on hall_ID seating plan */
    QList<int> showIDs;
    QList<int> seatIDs;
    QList<QString> seatsCondition;
    query.prepare(
        "SELECT MovieShowing.show_ID, HallSeats.seat_ID, HallSeats.condition"
        " FROM MovieShowing"
        " JOIN HallSeats ON (MovieShowing.hall_ID = HallSeats.hall_ID)"
        " WHERE (movie_ID=:id);"
    );
    query.bindValue(":id", this->movieID);
    if(!query.exec()) {
        qDebug() << query.lastError().text() << query.lastQuery();
    } else {
        /*qDebug() << "addMovie() read query for " << this->movieName
                 << " Show_ID, Hall_ID and Seat_ID was successful.";*/
        while(query.next()) {
            showIDs.append(query.value(0).toInt());
            seatIDs.append(query.value(1).toInt());
            seatsCondition.append(query.value(2).toString());
        }
    }
    qDebug() << "Finished SELECT show_ID, hall_ID, seat_ID FROM MovieShowing & HallSeats for " << this->movieName;

    /* (3b) For every record, if seatsCondition is NOT 'good', replace it with 'FALSE', else 'TRUE' */
    for (int cnt=0; cnt<seatsCondition.length(); cnt++) {
        if (seatsCondition[cnt] != "good") {
            seatsCondition[cnt].replace(seatsCondition[cnt], "FALSE");
        } else {
            seatsCondition[cnt].replace(seatsCondition[cnt], "TRUE");
        }

        /* (3c) INSERT seat_ID & condition for the respective show_ID based on (3a) INTO MovieSeats */
        query.prepare(
            "INSERT INTO MovieSeats (show_ID, seat_ID, available)"
            " VALUES (:show, :seat, :avail);"
        );
        query.bindValue(":show", showIDs[cnt]);
        query.bindValue(":seat", seatIDs[cnt]);
        query.bindValue(":avail", seatsCondition[cnt]);
        if(!query.exec()) {
            qDebug() << query.lastError().text() << query.lastQuery();
        } else {
            /*qDebug() << "addMovie() into MovieSeats write query for " << this->movieName
                     << " Show_ID, Hall_ID and Seat_ID was successful.";*/
            while(query.next()) {
                showIDs.append(query.value(0).toInt());
                seatIDs.append(query.value(1).toInt());
                seatsCondition.append(query.value(3).toString());
            }
        }
    }
    qDebug() << "Finished INSERT details INTO MovieSeats for " << this->movieName;

    MyDB::ResetInstance();
}
