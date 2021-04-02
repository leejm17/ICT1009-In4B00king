QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    diamondhall.cpp \
    economyhall.cpp \
    main.cpp \
    login.cpp \
    mainpage.cpp \
    mainpage2.cpp \
    movieinformation.cpp \
    mydb.cpp \
    seatselection.cpp

HEADERS += \
    diamondhall.h \
    economyhall.h \
    login.h \
    mainpage.h \
    mainpage2.h \
    movieinformation.h \
    mydb.h \
    seatselection.h

FORMS += \
    diamondhall.ui \
    economyhall.ui \
    login.ui \
    mainpage.ui \
    mainpage2.ui \
    movieinformation.ui \
    seatselection.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
