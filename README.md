# ICT1009-In4B00king

A Movie-booking Database Management System, this project is written in C++ using the QT Creator IDE.

The objective of this project is to experiment Object-oriented Programming (OOP) features on C++.

# Installation

## For Windows
If you need to load the project and see the UI, please install QT Creator at https://www.qt.io/download .

Load the project by File -> Open File or Project -> In4B00king.pro.

Our project also uses CURL for some functionality, so for in order to compile probably you would need to install the latest Curl for Windows at https://curl.se/download.html

Extract the contents (lib, include and bin) and place them in your QT Folder. (i.e. C:\Qt\6.0.3\mingw81_64)

After that, edit the LIBS path (bolded text) in In4Booking.pro to the path where you placed curl. (i.e. LIBS += -L**C:/Qt/6.0.3/mingw81_64/lib** -lcurl)

