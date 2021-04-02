/*
    Objective: Source file for Movie classes.
    Author: Lee Jun Ming (1802971).
*/

#include <movies.h>

/* Retrieves a list of movies & duration from DB & append to their respective arrays. */
void MovieListInfo::getMovieList_Db() {
    QSqlQuery query(MyDB::getInstance()->getDBInstance());
    query.prepare("SELECT name, duration FROM MovieList WHERE (debut <= DATE() AND finale >= DATE());");

    QString name;
    int duration;

    if(!query.exec()) {
        qDebug() << query.lastError().text() << query.lastQuery();
    } else {
        qDebug() << "getMovieList_Db() read query was successful.";
        while(query.next()) {
            name = query.value(0).toString();
            duration = query.value(1).toInt();

            movieNameList.append(name);
            movieDurationList.append(duration);
        }
        MyDB::ResetInstance();
    }
}

/* (1) Call displayMovieList() in MainScreen_Cust to display an array/series of movies currently on show. */
void MovieListInfo::displayMovieList(QList<QString> movieNameList, QList<int> movieDurationList) {
    for(int cnt=0; cnt<movieNameList.size(); cnt++) {
        qDebug() << movieNameList.at(cnt);
        qDebug() << movieDurationList.at(cnt);
    }
}

/* (2) When Customer clicks on a Movie in MainScreen, via this Constructor, initialise the data members. */
/* Calls getMovie_Db() to retrieve description & array of movieDates, then initialise them. */
MovieInfo::MovieInfo(QString, int) {

}

/* When Admin creates a new movie in MainScreen_Admin, via this Constructor, initialise the data members. */
MovieInfo::MovieInfo(QString, int, QString, QString, QString) {
    /* SELECT MovieList.desc, MovieShowing.date FROM MovieList WHERE (MovieList.name=movieName)
        ON (MovieList.movieId = MovieShowing.movieId). */
}

/* Call getMovie_Db() in MovieInfo() Constructor. */
void MovieInfo::getMovie_Db(QString) {

}

/* Call generateMovieDates() in MainScreen_Admin to generate an incremental list of movie show dates & append to movieDates[]. */
void MovieInfo::generateMovieDates() {

}

/* (4) Call displayMovieDetails() in MovieDetails to display a movie's information with its corresponding timeslots based on a given day. */
void displayMovieDetails(MovieInfo, ShowtimesInfo) {

}

/* addMovie_Db() adds the movie record into Database. */
void addMovie_Db(MovieInfo, ShowtimesInfo) {
/* INSERT INTO MovieList (name, duration, movieDebut, movieShut, description)
    VALUES (movieName, movieDuration, movieDebut, movieShut, movieDesc) */
/* INSERT INTO MovieShowing (date, timeslot)
    VALUES (movieDate, timeslot) */
/* INSERT INTO Hall (type)
    VALUES ('normal' OR 'diamond') */

}

/* (3) When Customer clicks on a movie date, call getShowtimes_Db(). */
/* Retrieves a list of timeslots & hallIDs from DB, and append to their respective arrays. */
void ShowtimesInfo::getShowtimes_Db(QString, QString) {
    /* SELECT timeslot, hallId FROM MovieShowing WHERE (MovieList.name=movieName AND
        MovieShowing.date=movieDate) ON (MovieList.movieId = MovieShowing.movieId) */
}

/* Call generateShowtimes() in MainScreen_Admin to generate a list of movie show times & match their halls, then append to their respective arrays. */
void ShowtimesInfo::generateShowtimes(QString) {

}

/* (5) When Customer clicks on movie timeslot, via this constructor, initialise data members, then load the hall layout. */
/* Calls displayLayout() based on hallID (eg if hallID<10, normal layout; if hallID>10, diamond layout) */
MovieSelection::MovieSelection(QString, QString, QString, int) {

}
