######################################################################
# Automatically generated by qmake (2.01a) ?? 3? 6 13:43:48 2018
######################################################################

TEMPLATE = app
TARGET = 
DEPENDPATH += . debug
INCLUDEPATH += .

# Input
HEADERS += can.hpp DEF_P303.h EXPORT_P303.h mainwindow.hpp os.hpp
FORMS += mainwindow.ui
SOURCES += can.cpp main.cpp mainwindow.cpp os.cpp
RESOURCES += rtqt.qrc
LIBS += -L. -lP303RT
QMAKE_CXXFLAGS += -std=c++0x