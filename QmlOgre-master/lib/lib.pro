CONFIG += qt
QT += qml quick
TEMPLATE = lib
TARGET = qmlogre


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



UI_DIR = ./.ui
OBJECTS_DIR = ./.obj
MOC_DIR = ./.moc


SOURCES += ogreitem.cpp \
    ogrenode.cpp \
    ogrecamerawrapper.cpp \
    ogreengine.cpp \
    predicates.cxx \
    tetgen.cxx

HEADERS += \
    ogreitem.h \
    ogrenode.h \
    ogrecamerawrapper.h \
    ogreengine.h \
    tetgen.h \
    mesh.hpp \
    ../../../../../Downloads/oomph-lib-0.90/src/meshes/tetgen_mesh.template.h \
    ../../../../../Downloads/oomph-lib-0.90/src/meshes/tetgen_mesh.h

# Copy all headers to build folder
Headers.path = $$OUT_PWD/include
Headers.files = $$files(*.h)
INSTALLS += Headers

OTHER_FILES += \
    oomph-lib-0.90/src/advection_diffusion/Makefile.in \
    oomph-lib-0.90/src/advection_diffusion/Makefile.am \
    oomph-lib-0.90/src/generic/mumps_fortran_solver.F \
    oomph-lib-0.90/src/generic/Makefile.in \
    oomph-lib-0.90/src/generic/Makefile.am \
    oomph-lib-0.90/src/advection_diffusion_reaction/Makefile.in \
    oomph-lib-0.90/src/advection_diffusion_reaction/Makefile.am \
    oomph-lib-0.90/src/axisym_navier_stokes/Makefile.in \
    oomph-lib-0.90/src/axisym_navier_stokes/Makefile.am \
    oomph-lib-0.90/src/axisym_spherical_solid/Makefile.in \
    oomph-lib-0.90/src/axisym_spherical_solid/Makefile.am \
    oomph-lib-0.90/src/beam/Makefile.in \
    oomph-lib-0.90/src/beam/Makefile.am \
    oomph-lib-0.90/src/biharmonic/Makefile.in \
    oomph-lib-0.90/src/biharmonic/Makefile.am \
    oomph-lib-0.90/src/constitutive/Makefile.in \
    oomph-lib-0.90/src/constitutive/Makefile.am \
    oomph-lib-0.90/src/fluid_interface/Makefile.in \
    oomph-lib-0.90/src/fluid_interface/Makefile.am \
    oomph-lib-0.90/src/flux_transport/Makefile.in \
    oomph-lib-0.90/src/flux_transport/Makefile.am \
    oomph-lib-0.90/src/linear_elasticity/Makefile.in \
    oomph-lib-0.90/src/linear_elasticity/Makefile.am \
    oomph-lib-0.90/src/linear_wave/Makefile.in \
    oomph-lib-0.90/src/linear_wave/Makefile.am \
    oomph-lib-0.90/src/meshes/mesh_names.list \
    oomph-lib-0.90/src/meshes/mesh_names.aux \
    oomph-lib-0.90/src/meshes/mesh_clean.aux \
    oomph-lib-0.90/src/meshes/Makefile.in \
    oomph-lib-0.90/src/meshes/Makefile.am \
    oomph-lib-0.90/src/multi_physics/Makefile.in \
    oomph-lib-0.90/src/multi_physics/Makefile.am \
    oomph-lib-0.90/src/navier_stokes/Makefile.in \
    oomph-lib-0.90/src/navier_stokes/Makefile.am \
    oomph-lib-0.90/src/poisson/Makefile.in \
    oomph-lib-0.90/src/poisson/Makefile.am \
    oomph-lib-0.90/src/shell/Makefile.in \
    oomph-lib-0.90/src/shell/Makefile.am \
    oomph-lib-0.90/src/spherical_navier_stokes/Makefile.in \
    oomph-lib-0.90/src/spherical_navier_stokes/Makefile.am \
    oomph-lib-0.90/src/solid/Makefile.in \
    oomph-lib-0.90/src/solid/Makefile.am \
    oomph-lib-0.90/src/unsteady_heat/Makefile.in \
    oomph-lib-0.90/src/unsteady_heat/Makefile.am \
    oomph-lib-0.90/src/womersley/Makefile.in \
    oomph-lib-0.90/src/womersley/Makefile.am \
    oomph-lib-0.90/src/young_laplace/Makefile.in \
    oomph-lib-0.90/src/young_laplace/Makefile.am

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../../usr/lib/release/ -lvtkCommon
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../../usr/lib/debug/ -lvtkCommon
else:unix: LIBS += -L$$PWD/../../../../../../../usr/lib/ -lvtkCommon

INCLUDEPATH += $$PWD/../../../../../../../usr/include
DEPENDPATH += $$PWD/../../../../../../../usr/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../../usr/lib/release/ -lvtkGraphics
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../../usr/lib/debug/ -lvtkGraphics
else:unix: LIBS += -L$$PWD/../../../../../../../usr/lib/ -lvtkGraphics

INCLUDEPATH += $$PWD/../../../../../../../usr/include
DEPENDPATH += $$PWD/../../../../../../../usr/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../../usr/lib/release/ -lvtkFiltering
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../../usr/lib/debug/ -lvtkFiltering
else:unix: LIBS += -L$$PWD/../../../../../../../usr/lib/ -lvtkFiltering

INCLUDEPATH += $$PWD/../../../../../../../usr/include
DEPENDPATH += $$PWD/../../../../../../../usr/include
