CONFIG += qt
QT += qml quick \
    widgets
TEMPLATE = app
TARGET = qmlogre

LIBS += -lqmlogre -ldcmdata -loflog -lofstd -ldcmimgle -L../lib/ \
        -lpcl_registration -lpcl_sample_consensus -lpcl_features -lpcl_filters -lpcl_surface -lpcl_segmentation \
        -lpcl_search -lpcl_kdtree -lpcl_octree -lflann_cpp -lpcl_common -lpcl_io \
        -lpcl_visualization \

UI_DIR = ./.ui
OBJECTS_DIR = ./.obj
MOC_DIR = ./.moc

SOURCES += main.cpp \
    DebugDrawer.cpp \
    cameranodeobject.cpp \
    exampleapp.cpp \
    coral.cpp \
    model/parser/ParserDicom.cpp\
    model/Vector3d.cpp

HEADERS += DebugDrawer.h \
    cameranodeobject.h \
    exampleapp.h \
    coral.h \
    model/parser/ParserDicom.h\
    model/Vector3d.h

OTHER_FILES += resources/example.qml \
    resources/Campan_MethodeHB_Seuil_970_Plus60_thinning_sliceBranchePropre2.bmi3d \
    resources/Dicom/IM-0001-0001.dcm

macx {
    OGREDIR = $$(OGRE_HOME)
    isEmpty(OGREDIR) {
        error(QmlOgre needs Ogre to be built. Please set the environment variable OGRE_HOME pointing to your Ogre root directory.)
    } else {
        message(Using Ogre libraries in $$OGREDIR)
        INCLUDEPATH += $$OGREDIR/include/OGRE
        INCLUDEPATH += $$OGREDIR/include/OGRE/RenderSystems/GL
        QMAKE_LFLAGS += -F$$OGREDIR/lib/release
        LIBS += -framework Ogre

        BOOSTDIR = $$OGREDIR/boost_1_42
        !isEmpty(BOOSTDIR) {
            INCLUDEPATH += $$BOOSTDIR
#            LIBS += -L$$BOOSTDIR/lib -lboost_date_time-xgcc40-mt-1_42 -lboost_thread-xgcc40-mt-1_42
        }
    }
} else:unix {
    CONFIG += link_pkgconfig
    PKGCONFIG += OGRE
} else:win32 {
    OGREDIR = C:/Ogre
    isEmpty(OGREDIR) {
        error(QmlOgre needs Ogre to be built. Please set the environment variable OGRE_HOME pointing to your Ogre root directory.)
    } else {
        message(Using Ogre libraries in $$OGREDIR)
        INCLUDEPATH += $$OGREDIR/include/OGRE
        INCLUDEPATH += $$OGREDIR/include/OGRE/RenderSystems/GL
        CONFIG(release, debug|release) {
            LIBS += -L$$OGREDIR/lib/release -L$$OGREDIR/lib/release/opt -lOgreMain -lRenderSystem_GL
        } else {
            LIBS += -L$$OGREDIR/lib/debug -L$$OGREDIR/lib/debug/opt -lOgreMain_d -lRenderSystem_GL_d
        }

        BOOSTDIR = $$OGREDIR/OgreVC/boost
        !isEmpty(BOOSTDIR) {
            INCLUDEPATH += $$BOOSTDIR
            CONFIG(release, debug|release) {
                LIBS += -L$$BOOSTDIR/lib -llibboost_date_time-vc100-mt-1_49 -llibboost_thread-vc100-mt-1_49
            } else {
                LIBS += -L$$BOOSTDIR/lib -llibboost_date_time-vc100-mt-gd-1_49 -llibboost_thread-vc100-mt-gd-1_49
            }
        }
    }
}


RESOURCES += resources/resources.qrc

# Copy all resources to build folder
Resources.path = $$OUT_PWD/resources
Resources.files = resources/*.zip

# Copy all config files to build folder
Config.path = $$OUT_PWD
Config.files = config/*

# make install
INSTALLS += Resources Config

DEPENDPATH += . \
              model \
              model/filters \
              model/model \
              model/parser \
              model/filters/3D \
              model/utils \


INCLUDEPATH += . \
               model \
               model/model \
               model/filters \
               model/filters/3D \
               model/parser \
               model/utils \
               "/usr/include/pcl-1.7/" \
               "/usr/include/flann/" \
               "/usr/include/eigen3/" \
               "/usr/include/openni/" \



HEADERS += model/model/InterfaceTranscriber.h \
           model/model/Examen.h \
           model/model/Information.h \
           model/model/Image3d.hpp \
           model/model/Skeleton.h \
           model/parser/Parser.h \
           model/parser/ParserManager.h \
           model/parser/ParserMi3DBinary.h \
           model/filters/3D/AlgoVolume.h \
           model/filters/3D/AlgoVolumeMorpho.h \
           model/filters/3D/StructuringElement.h \
           model/utils/debug.h \
           model/model/ExamenParams.h \
           model/utils/Tools.h \
           model/model/Struct.hpp \
           model/model/ImageMask2d.h \
           model/model/SliceType.h \
           model/model/Image.hpp \
           model/model/GrayValue.h \
           model/model/GrayViewWindow.h \
           model/model/Container2D.h \
    model/filters/Filterv2.h \
    model/filters/Filter2d.h \
    model/filters/Filter3d.h \
    model/filters/FilterArgument.h \
    model/filters/2D/GaussianFilter2d.h \
    model/filters/Filters.h \
    model/parser/ParserNMI3D.h

SOURCES += model/model/InterfaceTranscriber.cpp \
           model/model/Skeleton.cpp \
           model/parser/ParserManager.cpp \
           model/filters/3D/AlgoVolume.cpp \
           model/filters/3D/AlgoVolumeMorpho.cpp \
           model/model/Examen.cpp \
           model/model/ExamenParams.cpp \
           model/utils/Tools.cpp \
           model/model/Information.cpp \
           model/model/ImageMask2d.cpp \
           model/parser/Parser.cpp \
           model/parser/ParserMi3DBinary.cpp \
           model/utils/debug.cpp \
           model/model/GrayValue.cpp \
           model/model/GrayViewWindow.cpp \
           model/model/Container2D.cpp \
    model/filters/Filterv2.cpp \
    model/filters/Filter2d.cpp \
    model/filters/Filter3d.cpp \
    model/filters/FilterArgument.cpp \
    model/filters/2D/GaussianFilter2d.cpp \
    model/filters/Filters.cpp \
    model/parser/ParserNMI3D.cpp

include(modules/edition/edition.pri)
include(modules/manipulation/manipulation.pri)
include(modules/processing/processing.pri)
include(modules/histogram/histogram.pri)
include(modules/imageviewer/imageviewer.pri)
include(library/QColorRampEditor/qcolorrampeditor.pri)
include(window/window.pri)
include(modules/dicomdialog/dicomdialog.pri)
