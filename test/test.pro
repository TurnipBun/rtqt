TEMPLATE = app
TARGET = test
DEPENDPATH += . debug ../include ../src ../3rdparty/include
INCLUDEPATH += . ../include ../3rdparty/include C:\\msys64\\usr\\local\\include
MOC_DIR = .
UID_DIR = .

# Input
HEADERS += ../include/os.hpp \
		   ../include/log.hpp \
		   ../include/comm.hpp \
		   ../include/can.hpp \
		   ../include/wincom.hpp \
		   ../include/sock.hpp \
		   ../include/modulewidget.hpp \
		   ../include/comwidget.hpp \
		   ../include/canwidget.hpp \
		   ../include/sockWidget.hpp \
           ../include/mainwindow.hpp \

SOURCES += ../src/os.cpp \
		   ../src/log.cpp \
		   ../src/can.cpp \
           ../src/wincom.cpp \
		   ../src/sock.cpp \
           ../src/modulewidget.cpp \
		   ../src/comwidget.cpp \
		   ../src/canwidget.cpp \
		   ../src/sockwidget.cpp \
		   ../src/mainwindow.cpp \
		   test_rtqt.cpp \
		   gtest_main.cpp

FORMS += ../ui/formmodule.ui
RESOURCES += ../rtqt.qrc

LIBS += -L../3rdparty/lib -lP303RT -lws2_32 -lpthread -LC:\\msys64\\usr\\local\\lib -lgtest