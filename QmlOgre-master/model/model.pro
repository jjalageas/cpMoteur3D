######################################################################
# Automatically generated by qmake (2.01a) Sun Sep 30 17:48:50 2012
######################################################################


TEMPLATE = lib
TARGET = image3D

DEPENDPATH += . \
              src \
              src/filters \           
              src/model \              
              src/parser \              
              src/filters/3D \
              src/utils \
              test

INCLUDEPATH += . \
               src \
               src/model \
               src/filters \
               src/filters/3D \              
               src/parser \
               src/utils \
               test \


HEADERS += src/model/InterfaceTranscriber.h \           
           src/model/Examen.h \
           src/model/Information.h \
           src/model/Image3d.hpp \
           src/model/Skeleton.h \
           src/parser/Parser.h \           
           src/parser/ParserManager.h \
           src/parser/ParserMi3DBinary.h \          
           src/filters/3D/AlgoVolume.h \
           src/filters/3D/AlgoVolumeMorpho.h \         
           src/filters/3D/StructuringElement.h \
           src/utils/debug.h \
           src/model/ExamenParams.h \
           src/utils/Tools.h \           
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
    src/parser/ParserNMI3D.h

SOURCES += src/model/InterfaceTranscriber.cpp \          
           src/model/Skeleton.cpp \
           src/parser/ParserManager.cpp \          
           src/filters/3D/AlgoVolume.cpp \
           src/filters/3D/AlgoVolumeMorpho.cpp \         
           src/model/Examen.cpp \
           src/model/ExamenParams.cpp \
           src/utils/Tools.cpp \           
           src/model/Information.cpp \
           src/model/ImageMask2d.cpp \          
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
    src/parser/ParserNMI3D.cpp

HEADERS += \
           #test/GrayValueTest.h \
           #test/GrayViewWindowTest.h \
           test/Image2dTest.h \
          # test/ParserBmi3dTest.h

SOURCES += \
           test/mainTest.cpp \ # run the tests !!
          # test/GrayValueTest.cpp \
           #test/GrayViewWindowTest.cpp \
           test/Image2dTest.cpp \
           #test/ParserBmi3dTest.cpp

LIBS += \
   # -ldcmimage \
   # -ldcmimgle \
   # -ldcmdata \
   # -lofstd \
   # -ldcmdsig \
   # -ldcmjpeg \
   # -ldcmjpls \
  #  -ldcmnet \
  #  -ldcmpstat \
  #  -ldcmqrdb \
 #   -ldcmsr \
   # -ldcmtls \
  #  -ldcmwlm \
    #-li2d \
    #-lijg12 \
    #-lijg16 \
    #-lijg8 \
  #  -loflog \
    #-lpng \
    #-ltiff \
    #-ljpg \
    -lz \
    -lpthread
    # -lws2_32 # dcmtk dependency
    #-lnetapi32 \
