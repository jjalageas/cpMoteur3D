PCL - Point CLoud Library installation

-Meshing a 3D object requires the installation of the PCL library.
To obtain PCL, type these commands in the shell:

sudo add-apt-repository ppa:v-launchpad-jochen-sprickerhof-de/pcl
sudo apt-get update
sudo apt-get install libpcl-all

-to be added to .pro file:
LIBS += -lpcl_registration -lpcl_sample_consensus -lpcl_features -lpcl_filters -lpcl_surface -lpcl_segmentation \
-lpcl_search -lpcl_kdtree -lpcl_octree -lflann_cpp -lpcl_common -lpcl_io \
-lpcl_visualization \

INCLUDEPATH += . \
               "/usr/include/pcl-1.7/" \
               "/usr/include/flann/" \
               "/usr/include/eigen3/" \
               "/usr/include/openni/" \



PCL methods:

-setSearchRadius(double): sets the biggest size allowed for a face.
-setMaximumNearestNeighbors(unsigned): defines how many neighbors are sarched for.
-setMu(double): defines the maximum distance for a point to be considered.
-setMinimumAngle(double) - setMaximumAngle(double): sets minimum and maximun angles in triangles.
