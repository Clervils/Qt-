QT       += core gui quickwidgets positioning location widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    indexes.cpp \
    inference.cpp \
    locationmanager.cpp \
    main.cpp \
    mainwindow.cpp \
    rating.cpp \
    ratingbutton.cpp

HEADERS += \
    indexes.h \
    inference.h \
    locationmanager.h \
    mainwindow.h \
    rating.h \
    ratingbutton.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image.qrc \
    image2.qrc \
    image3.qrc \
    image4.qrc \
    image5.qrc \
    image6.qrc \
    qml.qrc

DISTFILES += \
    Gate.png \
    R-C.png \
    baozi.png \
    coffee.png \
    dd.png \
    hotpot.png \
    noodle.jpg \
    noodles.png \
    quick.jpg \
    search.png \
    south.png
