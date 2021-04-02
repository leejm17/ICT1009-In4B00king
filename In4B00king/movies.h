/*
    Objective: Header file for Movie classes.
    Author: Lee Jun Ming (1802971).
*/
#ifndef MOVIES_H
#define MOVIES_H

#include <QMainWindow>
#include <QMessageBox>
#include "mydb.h"

using namespace std;

/* Forward declaration for friend-function. */
class ShowtimesInfo;


/* Class to store movie information for a list of movies (Screen: MainScreen). */
class MovieListInfo {
private:
    QList<QString> movieNameList;    // stores an array of movie names in same order as movieDurationList[] (from DB)
    QList<int> movieDurationList; // stores an array of movie duration in same order as movieNameList[] (from DB)
public:
    void getMovieList_Db();
    void displayMovieList(QList<QString>, QList<int>); // movieNameList[], movieDurationList[]
};


/* Class to store movie information for any 1 movie (Screen: MainScreen_Admin). */
class MovieInfo {
private:
    QString movieName;
    int movieDuration;
    QString movieDebut;  // first date to show movie
    QString movieShut;   // last date to show movie
    QString movieDesc;   // movie synopsis
    QList<QString> movieDates;    // generate an array of dates from movieDebut to movieShut
public:
    MovieInfo();    // unused default constructor
    MovieInfo(QString, int);  // movieName, movieDuration
    MovieInfo(QString, int, QString, QString, QString); // movieName, movieDuration, movieDebut, movieShut, movieDesc
    void getMovie_Db(QString);   // movieName
    void generateMovieDates();

friend void displayMovieDetails(MovieInfo, ShowtimesInfo);  // movieName, movieDuration, movieDesc, movieDates, timeslots, halls
friend void addMovie_Db(MovieInfo, ShowtimesInfo);   // movieName, movieDuration, movieDebut, movieShut, movieDesc, movieDates, timeslots
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

friend void displayMovieDetails(MovieInfo, ShowtimesInfo);  // movieName, movieDuration, movieDesc, movieDates, timeslots, halls
friend void addMovie_Db(MovieInfo, ShowtimesInfo);   // movieName, movieDuration, movieDebut, movieShut, movieDesc, movieDates, timeslots
};


class MovieSelection : ShowtimesInfo {
private:
    QString selectedTimeslot;
    int selectedHall;
public:
    MovieSelection(QString, QString, QString, int);    // movieName, movieDate, timeslot, hall
};

#endif
