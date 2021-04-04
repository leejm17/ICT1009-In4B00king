/*
    Objective: Header file for Movie classes.
    Author: Lee Jun Ming (1802971).
*/
#ifndef MOVIES_H
#define MOVIES_H

#include <QMainWindow>
#include <QMessageBox>
#include <mydb.h>

/* Forward declaration for friend-function. */
class ShowtimesInfo;


/* Class to store movie information for a list of movies (Screen: MainScreen). */
class MovieListInfo {
private:
    QList<QString> movieNameList;    // stores an array of movie names in same order as movieDurationList[] (from DB)
    QList<int> movieDurationList; // stores an array of movie duration in same order as movieNameList[] (from DB)
public:
    void getMovieList_Db();
    void displayMovieList(); // movieNameList[], movieDurationList[]
};


/* Class to store movie information for any 1 movie (Screen: MainScreen_Admin). */
class MovieInfo {
//friend void displayMovieDetails(MovieInfo, ShowtimesInfo);  // movieName, movieDuration, movieDesc, movieDates, timeslots, halls
private:
    int movieID;    // store movieID from DB
    QString movieName;
    int movieDuration;
    QString movieDebut;  // first date to show movie
    QString movieFinale;   // last date to show movie
    QString movieDesc;   // movie synopsis
    QList<QString> movieDates;    // generate an array of dates from movieDebut to movieFinale
public:
    MovieInfo();    // unused default constructor
    MovieInfo(QString, int);  // movieName, movieDuration
    MovieInfo(QString, int, QString, QString, QString); // movieName, movieDuration, movieDebut, movieFinale, movieDesc
    void getMovieDetails_Db();
    void generateMovieDates();

friend void addMovie_Db(MovieInfo, ShowtimesInfo);   // movieName, movieDuration, movieDebut, movieFinale, movieDesc, movieDates, timeslots
};


/* Class to store showtimes for any 1 movie based on a given date (Screen: MovieDetails & MainScreen_Admin). */
class ShowtimesInfo : MovieInfo {
private:
    QList<QString> timeslots;    // stores an array of timeslots for a given movie on a given day in same order as halls[] (from DB)
    QList<int> halls; // stores an array of halls the cinema has in same order as timeslots[] (from DB)
public:
    ShowtimesInfo();    // unused default constructor
    void getShowtimes_Db(QString, QString); // movieName, movieDate
    void generateShowtimes(QString); // movieDate
    void displayMovieDetails();  // movieName, movieDuration, movieDesc, movieDates, timeslots, halls

friend void addMovie_Db(MovieInfo, ShowtimesInfo);   // movieName, movieDuration, movieDebut, movieFinale, movieDesc, movieDates, timeslots
};


class MovieSelection : ShowtimesInfo {
private:
    QString selectedTimeslot;
    int selectedHall;
public:
    /* (5) When Customer clicks on movie timeslot, via this constructor, initialise data members, then load the hall layout. */
    /* Calls displayLayout() based on hallID (eg if hallID<10, normal layout; if hallID>10, diamond layout) */
    //MovieSelection(QString, QString, QString, int);    // movieName, movieDate, timeslot, hall
};

#endif
