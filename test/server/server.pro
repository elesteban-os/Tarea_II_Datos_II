QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

LIBS += -lWs2_32
LIBS += -lwsock32
LIBS += -pthread
LIBS += -std=c++11
LIBS += -lpsapi

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    card.cpp \
    game.cpp \
    linkedcard.cpp \
    main.cpp \
    mainwindow.cpp \
    memory.cpp \
    server.cpp

HEADERS += \
    card.h \
    game.h \
    linkedcard.h \
    mainwindow.h \
    memory.h \
    server.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
