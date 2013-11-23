######################################################################
# Automatically generated by qmake (2.01a) Sun Sep 30 17:48:50 2012
######################################################################

QT += core gui opengl  # TODO : remove gui ! Move ImageViewer out of the library...

TEMPLATE = lib
TARGET = image3D
CONFIG += staticlib
DEFINES += HAVE_CONFIG_H # make dcmtk happy

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
    TEMPLATE = app

    message(unitTest)
    message($${CONFIG})
}

ContinuousIntegrationConfig {
    DEFINES -= GRAPHICAL_UNIT_TESTS
}

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

DEPENDPATH += . \
              src \
              src/filters \
              src/dialogue \
              src/model \
              src/openGL \
              src/parser \
              src/viewer2D \
              src/filters/3D \
              src/utils \
              test

INCLUDEPATH += . \
               src \
               src/model \
               src/filters \
               src/dialogue \
               src/viewer2D \
               src/filters/3D \
               src/openGL \
               src/parser \
               src/utils \
               test \
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

HEADERS += src/model/InterfaceTranscriber.h \
           src/dialogue/FilterDialog.h \
           src/model/Examen.h \
           src/model/Information.h \
           src/model/Image3d.hpp \
           src/model/Skeleton.h \
           src/parser/Parser.h \
           src/parser/ParserDicom.h \
           src/parser/ParserManager.h \
           src/parser/ParserMi3DBinary.h \
           src/viewer2D/ImageViewer.h \
           src/viewer2D/InformationViewer.h \
           #src/viewer2D/Viewer2DController.h \
           src/filters/3D/AlgoVolume.h \
           src/filters/3D/AlgoVolumeMorpho.h \
           src/dialogue/FilterController.h \
           src/filters/3D/StructuringElement.h \
           src/utils/debug.h \
           src/model/ExamenParams.h \
           src/utils/Tools.h \
           src/viewer2D/ImageViewerModel.h \
           src/model/Struct.hpp \
           src/model/ImageMask2d.h \
           src/model/SliceType.h \
           src/model/Image.hpp \
           src/model/GrayValue.h \
           src/model/GrayViewWindow.h \
    src/filters/Filterv2.h \
    src/filters/Filter2d.h \
    src/filters/Filter3d.h \
    src/filters/FilterArgument.h \
    src/filters/2D/GaussianFilter2d.h \
    src/filters/Filters.h \
    src/FilterWindow.h \
    src/parser/ParserNMI3D.h

SOURCES += src/model/InterfaceTranscriber.cpp \
           src/dialogue/FilterDialog.cpp \
           src/model/Skeleton.cpp \
           src/parser/ParserManager.cpp \
           src/viewer2D/ImageViewer.cpp \
           src/viewer2D/InformationViewer.cpp \
           #src/viewer2D/Viewer2DController.cpp \
           src/filters/3D/AlgoVolume.cpp \
           src/filters/3D/AlgoVolumeMorpho.cpp \
           src/dialogue/FilterController.cpp \
           src/model/Examen.cpp \
           src/model/ExamenParams.cpp \
           src/utils/Tools.cpp \
           src/viewer2D/ImageViewerModel.cpp \
           src/model/Information.cpp \
           src/model/ImageMask2d.cpp \
           src/parser/ParserDicom.cpp \
           src/parser/Parser.cpp \
           src/parser/ParserMi3DBinary.cpp \
           src/utils/debug.cpp \
           src/model/GrayValue.cpp \
           src/model/GrayViewWindow.cpp \
    src/filters/Filterv2.cpp \
    src/filters/Filter2d.cpp \
    src/filters/Filter3d.cpp \
    src/filters/FilterArgument.cpp \
    src/filters/2D/GaussianFilter2d.cpp \
    src/filters/Filters.cpp \
    src/FilterWindow.cpp \
    src/parser/ParserNMI3D.cpp


UnitTestConfig:HEADERS += \
           GrayValueTest.h \
           GrayViewWindowTest.h \
           Image2dTest.h \
           ParserBmi3dTest.h

UnitTestConfig:SOURCES += \
           mainTest.cpp \ # run the tests !!
           GrayValueTest.cpp \
           GrayViewWindowTest.cpp \
           Image2dTest.cpp \
           ParserBmi3dTest.cpp

LIBS += \
    -ldcmimage \
    -ldcmimgle \
    -ldcmdata \
    -lofstd \
    -ldcmdsig \
    -ldcmjpeg \
    -ldcmjpls \
    -ldcmnet \
    -ldcmpstat \
    -ldcmqrdb \
    -ldcmsr \
    -ldcmtls \
    -ldcmwlm \
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

target.path += "$$_PRO_FILE_PWD_"/bin # copy the lib into bin directory
headers.files   += $$HEADERS
headers.path += "$$_PRO_FILE_PWD_"/include # copy the includes into the include directory
INSTALLS += target headers

OTHER_FILES += \
    test/data/README