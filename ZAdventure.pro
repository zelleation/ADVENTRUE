QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bullet.cpp \
    choicebutton.cpp \
    levelswindow.cpp \
    main.cpp \
    homewindow.cpp \
    mapdata.cpp \
    playscene.cpp \
    user.cpp

HEADERS += \
    bullet.h \
    choicebutton.h \
    homewindow.h \
    levelswindow.h \
    mapdata.h \
    playscene.h \
    user.h

FORMS += \
    homewindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    rsc.qrc
