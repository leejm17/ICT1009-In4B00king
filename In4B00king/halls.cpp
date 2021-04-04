/*
    Objective: Source file for certain Hall classes.
    Author: Lee Jun Ming (1802971).
*/

#include <halls.h>

/* Call these to create a new hall & populate seats for the hall */
//Hall newEconomyHall1("economy");
//Hall newDiamondHall1("diamond");
//newEconomyHall1.generateSeats(newEconomyHall1);
//newDiamondHall1.generateSeats(newDiamondHall1);

/* Constructor for Halls */
Hall::Hall(QString type) {
    this->hallType = type;
    this->rowID = 'A';
    if (type == "economy") {
        this->numOfRows = ECONOMYHALL_ROWS;
        this->numOfCols = ECONOMYHALL_COLS;
        this->numOfSeats = ECONOMYHALL_SEATS;
        this->numOfTables = ECONOMYHALL_TABLES;
    } else {
        this->numOfRows = DIAMONDHALL_ROWS;
        this->numOfCols = DIAMONDHALL_COLS;
        this->numOfSeats = DIAMONDHALL_SEATS;
        this->numOfTables = DIAMONDHALL_TABLES;
    }
}

/* Generate seat numbers for a hall based on hall type & append to seatAllocation[] */
/* Add hall & seats information into DB with addNewHall_Db() */
void Hall::generateSeats(Hall hallObj) {
    for (this->rowID; hallObj<hallObj; this->rowID++) { // for every row -> for(char rowID='A'; rowID<4; rowID++)
        for (int colCnt=1; colCnt<=numOfCols; colCnt++) {   // for every column
            QString seatID = QString(this->rowID).append(QString::number(colCnt));
            seatAllocation.append(seatID);
        }
        hallObj.rowID += 1;
    }

    addNewHall_Db();
}

/* Operator Overload for 'smaller than' */
/* Hall.rowID is a char alphabet, 'A' is decimal 65
 * C++ cannot compare 'A' with 1 directly; it would become 65 compared to 1 */
bool Hall::operator<(Hall rows) {
    char hallRows[8] = "0ABCDEF";   // char array of potential row chars
    int i=1;    // counter
    while (i < 8) {
        if (rows.rowID == hallRows[i]) {    // if 'A' == an element in the row
            if (i != rows.numOfRows+1) {
                return true;                // return true and iterate the next for-loop
            }
        }
        i++;                                // increment index to the next element
    }
    return false;                           // if element does not exist in the row, return false and exit the for-loop
}

/* Function to create a new hall on DB */
void Hall::addNewHall_Db() {
    QSqlQuery query(MyDB::getInstance()->getDBInstance());  // open DB connection

    /* (1) INSERT hall details INTO Halls */
    query.prepare(
        "INSERT INTO Halls (type, numOfRows, numOfCols, numOfSeats, numOfTables)"
        " VALUES (:type, :rows, :cols, :seats, :tables);"
    );
    query.bindValue(":type", this->hallType);
    query.bindValue(":rows", this->numOfRows);
    query.bindValue(":cols", this->numOfCols);
    query.bindValue(":seats", this->numOfSeats);
    query.bindValue(":tables", this->numOfTables);

    if(!query.exec()) {
        qDebug() << query.lastError().text() << query.lastQuery();
    } else {
        qDebug() << "addNewHall() into Halls write query for " << this->hallType
                 << " hall was successful.";
    }

    /* (2) SELECT hall_ID of the hall (1) inserted into */
    query.prepare(
        "SELECT hall_ID"
        " FROM Halls"
        " ORDER BY hall_ID DESC LIMIT 1;"
    );
    if(!query.exec()) {
        qDebug() << query.lastError().text() << query.lastQuery();
    } else {
        qDebug() << "addNewHall() read query for new hall was successful.";
        while(query.next()) {
            this->hallID = query.value(0).toInt();
        }
    }

    /* (3) INSERT seats details INTO HallSeats */
    for (int seatCnt=0; seatCnt < seatAllocation.length(); seatCnt++) {
        query.prepare(
            "INSERT INTO HallSeats (hall_ID, seat_num, type, condition)"
            " VALUES (:id, :seat, :type, :condition);"
        );
        query.bindValue(":id", this->hallID);
        query.bindValue(":seat", this->seatAllocation[seatCnt]);
        query.bindValue(":type", "single");
        query.bindValue(":condition", "good");
        if(!query.exec()) {
            qDebug() << query.lastError().text() << query.lastQuery();
        } else {
            qDebug() << "addNewHall() into HallSeats write query for hallID: " << this->hallID
                     << " was successful.";
        }
    }

    MyDB::ResetInstance();  // close DB connection
}
