#-------------------------------------------------
#
# Project created by QtCreator 2013-10-03T12:27:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = window/mainwindow

TEMPLATE = app

include(modules/edition/edition.pri)
include(modules/manipulation/manipulation.pri)
include(modules/processing/processing.pri)
include(modules/histogram/histogram.pri)
include(modules/imageviewer/imageviewer.pri)
include(library/QColorRampEditor/qcolorrampeditor.pri)
include(window/window.pri)

SOURCES += \
    main.cpp \
    coral.cpp \

RESOURCES += \
    resources/resources.qrc

TRANSLATIONS = \
    resources/translations/coral_fr.ts \
    resources/translations/coral_es.ts

HEADERS += \
    coral.hpp \
