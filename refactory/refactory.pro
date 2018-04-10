TEMPLATE = app
TARGET = refactory
DEPENDPATH += . debug
INCLUDEPATH += .
MOC_DIR = .
UID_DIR = .

# Input
HEADERS += ./os.hpp \
		   ./log.hpp \
		   ./modulewidget.hpp \
		   ./com.hpp \
		   ./wincom.hpp \
		   ./comwidget.hpp

SOURCES += ./os.cpp \
		   ./log.cpp \
           ./modulewidget.cpp \
		   ./wincom.cpp \
		   ./comwidget.cpp \
           ./main.cpp

FORMS += formmodule.ui
