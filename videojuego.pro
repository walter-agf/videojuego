QT       += core gui \
         multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dis_jefe_1.cpp \
    dis_jefe_2.cpp \
    disparo_c.cpp \
    disparo_m.cpp \
    elemento.cpp \
    grafica.cpp \
    inicio.cpp \
    jefe_uno.cpp \
    mago.cpp \
    main.cpp \
    mainwindow.cpp \
    minotauro.cpp \
    multiplayer.cpp \
    muros.cpp \
    niveles.cpp \
    oneplayer.cpp \
    score.cpp

HEADERS += \
    dis_jefe_1.h \
    dis_jefe_2.h \
    disparo_c.h \
    disparo_m.h \
    elemento.h \
    grafica.h \
    inicio.h \
    jefe_uno.h \
    mago.h \
    mainwindow.h \
    minotauro.h \
    multiplayer.h \
    muros.h \
    niveles.h \
    oneplayer.h \
    score.h

FORMS += \
    mainwindow.ui \
    multiplayer.ui \
    oneplayer.ui \
    score.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    pictures.qrc
