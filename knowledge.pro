######################################################################
# Automatically generated by qmake (2.01a) Thu Nov 18 23:46:03 2010
######################################################################

TEMPLATE = app
TARGET = Knowledge
DEPENDPATH += . src
INCLUDEPATH += . src

QT += gui xml

OBJECTS_DIR = tmp
MOC_DIR = tmp
DESTDIR = build

# Input
HEADERS += src/KDocument.h \
           src/KQuestion.h \
           src/KMainWindow.h \
           src/KGame.h \
           src/KTTTGame.h \
           src/AutoScalingView.h


SOURCES += src/KDocument.cpp \
           src/KQuestion.cpp \
           src/main.cpp \
           src/KMainWindow.cpp \
           src/KTTTGame.cpp
