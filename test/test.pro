TEMPLATE = app
TARGET = test
DEPENDPATH += . debug ../include ../src ../3rdparty/include
INCLUDEPATH += . ../include ../3rdparty/include C:\\msys64\\usr\\local\\include
MOC_DIR = .
UID_DIR = .

# Input
HEADERS += ../include/can.hpp \
           ../include/os.hpp \
           ../include/mainwindow.hpp \
		   ../include/log.hpp \
           ../3rdparty/include/DEF_P303.h \
           ../3rdparty/include/EXPORT_P303.h

SOURCES += ../src/can.cpp \
           ../src/os.cpp \
		   ../src/mainwindow.cpp \
		   ../src/log.cpp \
		   test_can.cpp \
		   gtest_main.cpp

FORMS += ../mainwindow.ui
RESOURCES += ../rtqt.qrc

LIBS += -pthread -L../3rdparty/lib -lP303RT -LC:\\msys64\\usr\\local\\lib -lgtest