TEMPLATE = app
TARGET = rtqt
DEPENDPATH += . debug ../include ../src ../3rdparty/include
INCLUDEPATH += . .. ../include ../3rdparty/include
MOC_DIR = .
UID_DIR = .

# Input
HEADERS += ../include/can.hpp \
           ../include/os.hpp \
           ../include/mainwindow.hpp \
           ../3rdparty/include/DEF_P303.h \
           ../3rdparty/include/EXPORT_P303.h

SOURCES += ../src/can.cpp ../src/os.cpp ../src/mainwindow.cpp  main.cpp 

FORMS += ../mainwindow.ui
RESOURCES += ../rtqt.qrc

LIBS += -pthread -L../3rdparty/lib -lP303RT