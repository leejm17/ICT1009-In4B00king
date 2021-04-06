# ICT1009-In4B00king

A Movie-booking Database Management System, this project is written in C++ using the Qt Creator IDE.

The objective of this project is to experiment Object-oriented Programming (OOP) features on C++.

# Pre-requisites

Follow the steps below for program code inspection, or re-compilation and run through the program.

### Load the Project
1. Go to https://www.qt.io/download.
2. Click 'Download Qt Now' & Register for a trial account (a valid Qt account is required to start the installation).
3. Install Qt Creator.
4a. Once done, load the project by File -> Open File or Project -> In4B00king.pro.
4b. Or you could double-click on In4B00king.pro to launch Qt Creator (after installation).

### cURL (for re-compilation of program)
Our project also uses CURL for some functionality.

Follow the steps below to recompile the program with cURL.

1. You might need to install the latest cURL for Windows at https://curl.se/download.html.
2. Extract the contents (lib, include and bin) and place them in the respective directories of your Qt Folder (i.e. C:\Qt\6.0.3\mingw81_64).
3. Edit the LIBS path (bolded text) in In4B00king.pro to the path where you placed curl in Qt (i.e. LIBS += -L**C:/Qt/6.0.3/mingw81_64/lib** -lcurl).
