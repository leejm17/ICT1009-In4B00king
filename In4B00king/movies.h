/*
    Objective: Header file for Movie classes.
    Author: Lee Jun Ming (1802971).
*/
#ifndef MOVIES_H
#define MOVIES_H

#include <QMainWindow>
#include <QMessageBox>
#include <QComboBox>
#include "mydb.h"

/* Forward declaration for friend-function. */
//class ShowtimesInfo;

struct Movie
{
    QLabel* title;
    QLabel* duration;
};

/* Class to store movie information for a list of movies (Screen: MainScreen). */
class MovieListInfo {
private:
    QList<int> movieIDList;         // stores an array of movie IDs in the same order as the two lists below (from DB)
    QList<QString> movieNameList;    // stores an array of movie names in same order as movieDurationList[] (from DB)
    QList<QString> movieDurationList; // stores an array of movie duration in same order as movieNameList[] (from DB)
public:
    MovieListInfo() {};    // default constructor
    void getMovieList_Db();     // getMovies for customer where date range of movie is within current date
    void displayMovieList(Movie*); // Movie is a struct defined in movielist.h, but passing over a struct array
    void getAllMovieList_Db();  // getAllMovies for admin
    QList<QString> getMovieNameList();  // getter to get movieNameList
};


/* Base/Parent class for child MovieInfo */
class MovieBasic {
private:
    QString movieName;
    int movieDuration;
public:
    MovieBasic() {};   // default constructor
    MovieBasic(QString, int);   // movieName, movieDuration

    /* Getters & Setters */
    QString getName();
    void setName(QString);  // movieName
    int getDuration();
    void setDuration(int);  // movieDuration
};


/* Class to store movie information for any 1 movie (Screen: MainScreen_Admin). */
class MovieInfo : public MovieBasic {
private:
    int movieID;    // store movieID from DB
    QString movieDebut;  // first date to show movie
    QString movieFinale;   // last date to show movie
    QString movieDesc;   // movie synopsis
    QList<QString> movieDates;    // generate an array of dates from movieDebut to movieFinale
    QString newMovieName;

    int priority;
    QList<QString> economy_timeslots;   // stores an array of timeslots for a given movie on a given day in same order as halls[] (from DB)
    QList<int> economy_halls;           // stores an array of halls the cinema has in same order as timeslots[] (from DB)
    QList<QString> diamond_timeslots;   // similar to economy_timeslots, but for diamond halls
    QList<int> diamond_halls;           // similar to economy_halls, but for diamond halls
public:
    MovieInfo() {};    // default constructor
    MovieInfo(QString, int);  // movieName, movieDuration
    void getMovieDetails_Db();

    MovieInfo(QString, int, QString, QString, QString); // movieName, movieDuration, movieDebut, movieFinale, movieDesc
    void generateMovieDates();
    void appendMovieDate(int, int, int);    // year, month, date
    void getPriority_Db();
    void generateShowtimes();
    void addMovie_Db();   // movieName, movieDuration, movieDebut, movieFinale, movieDesc, movieDates, timeslots
    void deleteMovie_Db(QString);  // movieName
    void updateMovie_Db();

    /* Getters & Setters */
    MovieInfo(QString);     // movieName
	int getMovieID();
    /*QString getMovieName();
    int getMovieDuration();*/
    QString getDebut();
    QString getDesc();
    QString getNewName();
    void updateMovieDetails();
    MovieInfo(QString, QString, int, QString);  // oldName, newName, duration, desc
};


/* Class to store showtimes for any 1 movie based on a given date (Screen: MovieDetails & MainScreen_Admin). */
class ShowtimesInfo {
private:
    QString movieName;
    QString movieDate;
    QList<QString> retrieve_timeslots;
    QList<int> retrieve_halls;
    QList<QString> retrieve_dates;
public:
    ShowtimesInfo() {};   // unused default constructor
    void displayMovieDetails(QString, QString);  // movieName, movieDate
    void getShowtimes_Db(QString, QString); // movieName, movieDate

    // 2nd
    void displayMovieDetails(QString, QComboBox*);  // movieName, movieDate
    void getShowtimes_Db(QString); // movieName, movieDate
};

#endif
