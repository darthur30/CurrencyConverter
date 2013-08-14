#-------------------------------------------------
#
# Project created by QtCreator 2013-04-21T22:13:28
#
#-------------------------------------------------

QT       += core gui
QT       += webkit

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CurrencyConverter
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    generatemodel.cpp \
    generatevector.cpp \
    HttpRequest.cpp \
    resultdialog.cpp \
    aboutdialog.cpp

HEADERS  += mainwindow.h \
    programutilities.h \
    curl-7.30.0-devel-mingw32/include/curl/curl.h \
    ../../../Desktop/C++ Libraries/decimal_for_cpp/include/decimal.h \
    ../../../Desktop/C++ Libraries/decimal_for_cpp/include/decimal.h \
    decimal.h \
    resultdialog.h \
    aboutdialog.h

FORMS    += mainwindow.ui \
    resultdialog.ui \
    aboutdialog.ui





LIBS += C:/Qt/Qt5.0.2/Tools/MinGW/lib/libcurl.a

LIBS += C:/Qt/Qt5.0.2/Tools/MinGW/lib/libcurldll.a



INCLUDEPATH += C:/Qt/Qt5.0.2/Tools/MinGW/lib

INCLUDEPATH += C:/Qt/Qt5.0.2/Tools/MinGW/include

OTHER_FILES +=

RESOURCES += \
    MyResources.qrc




