TEMPLATE = app
TARGET = rtqt
DEPENDPATH += . debug ../include ../src ../3rdparty/include
INCLUDEPATH += . .. ../include ../3rdparty/include
MOC_DIR = .
UID_DIR = ../include

# Input
HEADERS += ../include/os.hpp \
		   ../include/log.hpp \
		   ../include/comm.hpp \
		   ../include/can.hpp \
		   ../include/wincom.hpp \
		   ../include/modulewidget.hpp \
		   ../include/comwidget.hpp \
		   ../include/canwidget.hpp \
           ../include/mainwindow.hpp \

SOURCES += ../src/os.cpp \
		   ../src/log.cpp \
		   ../src/can.cpp \
           ../src/wincom.cpp \
           ../src/modulewidget.cpp \
		   ../src/comwidget.cpp \
		   ../src/canwidget.cpp \
		   ../src/mainwindow.cpp \
		   ./main.cpp 

FORMS += ../ui/formmodule.ui
RESOURCES += ../rtqt.qrc
LIBS +=  -L../3rdparty/lib -lP303RT
