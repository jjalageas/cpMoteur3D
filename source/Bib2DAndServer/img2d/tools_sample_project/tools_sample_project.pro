#-------------------------------------------------
#
# Project created by QtCreator 2012-09-25T21:48:42
#
#-------------------------------------------------

QT       += core gui

TARGET = tools_sample_project
TEMPLATE = app


# If you want to do unitTest and to test for assertions, you must make CONFIG+=debug

# If you want some graphical tests,
# add DEFINE+=GRAPHICAL_UNIT_TEST in your qmake command

ContinuousIntegrationConfig {
    CONFIG += UnitTestConfig
}

UnitTestConfig {
    # qxcppunitd is for QML projects
    # qttestrunner is for QWidgets project
    DEFINES += UNIT_TESTS GRAPHICAL_UNIT_TESTS
    LIBS += -lcppunit -lqxcppunitd
    VPATH += test/
    INCLUDEPATH += test/
    message(unitTest)
    message($${CONFIG})
}

ContinuousIntegrationConfig {
    DEFINES -= GRAPHICAL_UNIT_TESTS
}

CONFIG(debug, debug|release) {
    message(debug compilation)
    CONFIG += debug declarative_debug warn_on
    CONFIG -= release #...
    message($${CONFIG})
} else {
    message(release compilation)
    CONFIG += release warn_on
    CONFIG -= debug #...
    DEFINES += NDEBUG
    message($${CONFIG})
}

#DebugConfig {
#    CONFIG += debug declarative_debug warn_on
#    CONFIG -= release #...
#    message(debug)
#    message($${CONFIG})
#}

#ReleaseConfig {
#    CONFIG += release warn_on
#    CONFIG -= debug #...
#    DEFINES += NDEBUG
#    message(release)
#    message($${CONFIG})
#}

GenerateDoc { # need a Doxyfile to run correctly
    system(doxygen)
    # An unexpected Makefile is generated here.
    # It can be prevented by adding error(""),
    # but this displays an error message to the user
}
#doc.commands = doxygen
#doc.target = doc
##doc.depends = $(SOURCES) $(HEADERS) "./Doxyfile"
#QMAKE_EXTRA_TARGETS += doc
#doc.files = Doxyfile
#QMAKE_POST_LINK = $(COPY_FILE) Doxyfile output.txt


VPATH += src/ \
         include/ \ # to generate the mock files
         ui/

INCLUDEPATH += include/

SOURCES += main.cpp\
           mainwindow.cpp
HEADERS  += mainwindow.h \
    include/debug.h


UnitTestConfig:HEADERS += mainwindowtest.h
UnitTestConfig:SOURCES += mainwindowtest.cpp


FORMS    += mainwindow.ui
