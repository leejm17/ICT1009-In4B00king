/*
    Objective: Header file for Movie classes.
    Author: Lee Jun Ming (1802971).
*/
#ifndef MOVIES_H
#define MOVIES_H

#include <iostream>
using namespace std;

/* Forward declaration for friend-function. */
class ShowtimesInfo;


/* Class to store movie information for a list of movies (Screen: MainScreen). */
class MovieListInfo {
private:
    char* movieNameList[10];    // stores an array of movie names in same order as movieDurationList[] (from DB)
    int* movieDurationList[10]; // stores an array of movie duration in same order as movieNameList[] (from DB)
public:
    /* getMovieList_Db() retrieves a list of movies & duration from DB & append to their respective arrays. */
    /* SELECT name, duration FROM MovieList WHERE (movieDebut <= currentDate() AND movieShut >= currentDate()) */
    void getMovieList_Db();

    /* (1) Call displayMovieList() in MainScreen_Cust to display an array/series of movies currently on show. */
    void displayMovieList(char*, int*); // movieNameList[], movieDurationList[]
};


/* Class to store movie information for any 1 movie (Screen: MainScreen_Admin). */
class MovieInfo {
private:
    string movieName;
    int movieDuration;
    string movieDebut;  // first date to show movie
    string movieShut;   // last date to show movie
    string movieDesc;   // movie synopsis
    char* movieDates[60];    // generate an array of dates from movieDebut to movieShut
public:
    /* (2) When Customer clicks on a Movie in MainScreen, via this Constructor, initialise the data members. */
    /* Calls getMovie_Db() to retrieve description & array of movieDates, then initialise them. */
    MovieInfo(string, int);  // movieName, movieDuration

    /* Call getMovie_Db() in MovieInfo() Constructor. */
    /* SELECT MovieList.desc, MovieShowing.date FROM MovieList WHERE (MovieList.name=movieName)
        ON (MovieList.movieId = MovieShowing.movieId). */
    void getMovie_Db(string);   // movieName

    /* When Admin creates a new movie in MainScreen_Admin, via this Constructor, initialise the data members. */
    MovieInfo(string, int, string, string, string); // movieName, movieDuration, movieDebut, movieShut, movieDesc

    /* Call generateMovieDates() in MainScreen_Admin to generate an incremental list of movie show dates & append to movieDates[]. */
    void generateMovieDates();

/* (4) Call displayMovieDetails() in MovieDetails to display a movie's information with its corresponding timeslots based on a given day. */
friend void displayMovieDetails(MovieInfo, ShowtimesInfo);  // movieName, movieDuration, movieDesc, movieDates, timeslots, halls

/* addMovie_Db() adds the movie record into Database. */
/* INSERT INTO MovieList (name, duration, movieDebut, movieShut, description)
    VALUES (movieName, movieDuration, movieDebut, movieShut, movieDesc) */
/* INSERT INTO MovieShowing (date, timeslot)
    VALUES (movieDate, timeslot) */
/* INSERT INTO Hall (type)
    VALUES ('normal' OR 'diamond') */
friend void addMovie_Db(MovieInfo, ShowtimesInfo);   // movieName, movieDuration, movieDebut, movieShut, movieDesc, movieDates, timeslots
};


/* Class to store showtimes for any 1 movie based on a given date (Screen: MovieDetails & MainScreen_Admin). */
class ShowtimesInfo : MovieInfo {
private:
    char* timeslots[10];    // stores an array of timeslots for a given movie on a given day in same order as halls[] (from DB)
    int* halls[10]; // stores an array of halls the cinema has in same order as timeslots[] (from DB)
public:
    /* (3) When Customer clicks on a movie date, call getShowtimes_Db(). */
    /* Retrieves a list of timeslots & hallIDs from DB, and append to their respective arrays. */
    /* SELECT timeslot, hallId FROM MovieShowing WHERE (MovieList.name=movieName AND 
        MovieShowing.date=movieDate) ON (MovieList.movieId = MovieShowing.movieId) */
    void getShowtimes_Db(string, string); // movieName, movieDate

    /* Call generateShowtimes() in MainScreen_Admin to generate a list of movie show times & match their halls, then append to their respective arrays. */
    void generateShowtimes(string); // movieDate

/* (4) Call displayMovieDetails() in MovieDetails to display a movie's information with its corresponding timeslots based on a given day. */
friend void displayMovieDetails(MovieInfo, ShowtimesInfo);  // movieName, movieDuration, movieDesc, movieDates, timeslots, halls

/* addMovie_Db() adds the movie record into Database. */
/* INSERT INTO MovieList (name, duration, movieDebut, movieShut, description)
    VALUES (movieName, movieDuration, movieDebut, movieShut, movieDesc) */
/* INSERT INTO MovieShowing (date, timeslot)
    VALUES (movieDate, timeslot) */
/* INSERT INTO Hall (type)
    VALUES ('normal' OR 'diamond') */
friend void addMovie_Db(MovieInfo, ShowtimesInfo);   // movieName, movieDuration, movieDebut, movieShut, movieDesc, movieDates, timeslots
};


class MovieSelection : MovieInfo, ShowtimesInfo {
private:
    string selectedTimeslot;
    int selectedHall;
public:
    /* (5) When Customer clicks on movie timeslot, via this constructor, initialise data members, then load the hall layout. */
    /* Calls displayLayout() based on hallID (eg if hallID<10, normal layout; if hallID>10, diamond layout) */
    MovieSelection(string, string, string, int);    // movieName, movieDate, timeslot, hall
};

#endif
