/*
    Objective: Header file for User classes.
    Author: Lee Jun Ming (1802971).
*/
#ifndef USER_H
#define USER_H

#include <iostream>
using namespace std;

/* Base Class inherited by Customer & Administrator. */
class User {
private:
    string name;
};


/* Class to store customer information. */
class Customer : User {
private:
    string email;
    string password;
    int age;
    char gender;
    string remarks;
public:
    /* When Customer creates an account via this Constructor, initialise the data members. */
    Customer(string, string, string, int, char, string);    // email, password, name, age, gender, remarks
    int getAge();
    char getGender();
    string getRemarks();

    /* addCustomer_Db() adds the customer record into Database. */
    /* INSERT INTO User (type, name, age, gender, remarks)
        VALUES ("customer", name, age, gender, remarks) */
    void addCustomer_Db(Customer);

    /* getCustomer_Db() retrieves the customer record from DB. */
    /* SELECT age, gender, remarks FROM User WHERE (type='customer' AND name=<whoever is logged in>) */
    void getCustomer_Db();
};


/* Class to store administrator information. */
class Administrator : User {
private:
public:
};

#endif
