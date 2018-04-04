TEMPLATE = app
TARGET = refactory
DEPENDPATH += . debug
INCLUDEPATH += .
MOC_DIR = .
UID_DIR = .

# Input
HEADERS += ./os.hpp \
		   ./log.hpp \
		   ./vxcom.hpp \
		   ./modulewidget.hpp \
		   ./comwidget.hpp

SOURCES += ./os.cpp \
		   ./log.cpp \
           ./vxcom.cpp \
           ./modulewidget.cpp \
		   ./comwidget.cpp \
           ./main.cpp

FORMS += formmodule.ui
