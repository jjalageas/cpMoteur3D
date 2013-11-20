TEMPLATE = app

CONFIG += console qt
QT += sql

VPATH += src/ \
         src/database/ \
        src/gui

SOURCES += main.cpp \
    gui/SliceViewer.cpp \
    src/FilterWindowTester.cpp \
    src/gui/LoginFrame.cpp \
    src/gui/NewAccount.cpp \
    src/database/DatabaseManager.cpp

HEADERS += \
    gui/SliceViewer.h \
    src/FilterWindowTester.h \
    src/gui/LoginFrame.h \
    src/gui/NewAccount.h \
    src/database/DatabaseManager.h \
    src/database/Tables.h

FORMS += \
    src/ui/SliceViewer.ui \
    src/ui/LoginFrame.ui \
    src/ui/NewAccount.ui


LIBS += -L"$$_PRO_FILE_PWD_/../lib-core/bin/" -limage3D
INCLUDEPATH += "$$_PRO_FILE_PWD_/../lib-core/include"
DEFINES += HAVE_CONFIG_H


CONFIG(debug, debug|release) {
    message(debug compilation)
    CONFIG += debug declarative_debug warn_on
    CONFIG -= release
    message($${CONFIG})
} else {
    message(release compilation)
    CONFIG += release warn_on
    CONFIG -= debug
    DEFINES += NDEBUG
    message($${CONFIG})
}

ContinuousIntegrationConfig {
    CONFIG += UnitTestConfig
}

UnitTestConfig {
    DEFINES += UNIT_TESTS GRAPHICAL_UNIT_TESTS
    LIBS += -lcppunit -lqxcppunitd # the test runner library depends on your system.
    VPATH += src/test/
    INCLUDEPATH += src/test/
    TEMPLATE = app
    SOURCES -= main.cpp

    message(unitTest)
    message($${CONFIG})
}

ContinuousIntegrationConfig {
    DEFINES -= GRAPHICAL_UNIT_TESTS
}

UnitTestConfig:HEADERS += \
            DbmTest.h

UnitTestConfig:SOURCES += \
            DbmTest.cpp \
            mainTest.cpp # run the tests !!

INCLUDEPATH += src/gui/ \
               src \
               src/database/ \
               \ # dcmtk includes
               /usr/include/dcmtk/dcmimgle \
               /usr/include/dcmtk/config \
               /usr/include/dcmtk/dcmdata \
               /usr/include/dcmtk/dcmimage \
               /usr/include/dcmtk/dcmjpeg \
               /usr/include/dcmtk/dcmjpls \
               /usr/include/dcmtk/dcmnet \
               /usr/include/dcmtk/dcmpstat \
               /usr/include/dcmtk/dcmqrdb \
               /usr/include/dcmtk/dcmsign \
               /usr/include/dcmtk/dcmsr \
               /usr/include/dcmtk/dcmtls \
               /usr/include/dcmtk/dcmwlm \
               /usr/include/dcmtk/oflog \
               /usr/include/dcmtk/ofstd

LIBS += \
    #-ldcmimage \
    -ldcmimgle \
    -ldcmdata \
    -lofstd \
    -ldcmdsig \
    #-ldcmjpeg \
    #-ldcmjpls \
    #-ldcmnet \
    #-ldcmpstat \
    #-ldcmqrdb \
    -ldcmsr \
    #-ldcmtls \
    #-ldcmwlm \
    #-li2d \
    #-lijg12 \
    #-lijg16 \
    #-lijg8 \
    -loflog \
    #-lpng \
    #-ltiff \
    #-ljpg \
    -lz \
    -lpthread
    # -lws2_32 # dcmtk dependency
    #-lnetapi32 \
