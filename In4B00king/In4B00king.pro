QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    confirmationscreen.cpp \
    diamondhall.cpp \
    economyhall.cpp \
    editprofile.cpp \
    forgetpassword.cpp \
    main.cpp \
    login.cpp \
    mainpage.cpp \
    movieinformation.cpp \
    movielist.cpp \
    movies.cpp \
    mydb.cpp \
    register.cpp \
    seatselection.cpp \
    halls.cpp

HEADERS += \
    confirmationscreen.h \
    diamondhall.h \
    economyhall.h \
    editprofile.h \
    forgetpassword.h \
    login.h \
    mainpage.h \
    movieinformation.h \
    movielist.h \
    movies.h \
    mydb.h \
    register.h \
    seatselection.h\
    halls.h

FORMS += \
    confirmationscreen.ui \
    diamondhall.ui \
    economyhall.ui \
    editprofile.ui \
    forgetpassword.ui \
    login.ui \
    mainpage.ui \
    movieinformation.ui \
    movielist.ui \
    register.ui \
    seatselection.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
