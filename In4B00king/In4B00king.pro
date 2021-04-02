QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    economyhall.cpp \
    economyselection.cpp \
    main.cpp \
    login.cpp \
    mainpage.cpp \
    mainpage2.cpp \
    movieinformation.cpp \
    mydb.cpp

HEADERS += \
    economyhall.h \
    economyselection.h \
    login.h \
    mainpage.h \
    mainpage2.h \
    movieinformation.h \
    mydb.h

FORMS += \
    economyhall.ui \
    economyselection.ui \
    login.ui \
    mainpage.ui \
    mainpage2.ui \
    movieinformation.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
