/*
    Objective: Header file for certain Hall classes interacting with DB.
    Author: Lee Jun Ming (1802971).
*/
#ifndef HALLS_H
#define HALLS_H

#include <mydb.h>

#define ECONOMYHALL_ROWS 4
#define ECONOMYHALL_COLS 14
#define ECONOMYHALL_SEATS ECONOMYHALL_ROWS*ECONOMYHALL_COLS
#define ECONOMYHALL_TABLES 0

#define DIAMONDHALL_ROWS 3
#define DIAMONDHALL_COLS 11
#define DIAMONDHALL_SEATS DIAMONDHALL_ROWS*DIAMONDHALL_COLS
#define DIAMONDHALL_TABLES 4

/* Class to store hall information. */
class Hall {
private:
    QString hallType;
    char rowID;
    int numOfRows;
    int numOfCols;
    int numOfSeats;
    int numOfTables;

    int hallID;
    QList<QString> seatAllocation;
public:
    Hall(QString);   // hallType
    void generateSeats(Hall);
    bool operator<(Hall);
    QList<QString> getSeatAllocation();
    void addNewHall_Db();
};

#endif
