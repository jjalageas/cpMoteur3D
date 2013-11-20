#ifndef EXAMEN_PARAMS_H
#define EXAMEN_PARAMS_H

#include "Struct.hpp"
#include "GrayValue.h"
#include "GrayViewWindow.h"

#include <string>


class Information;

// Todo : remove windowing center/width or windowing min/max of this class (it should be part of the view !)

/**
  ExamenParams contains a description of the examen (patient, sex, ...)
  are stocked in an Information structure
  _View_ Contrast and Luminosity are stocked in a GrayViewWindow structure
  The GrayTranslationFunction cannot be changed : it provides a means of converting
  image encoding gray levels to HundsField unit and the contrary.
  Various other informations.
  */
class ExamenParams
{
public:
    ExamenParams(GrayTranslationFunction&, std::string &filename, Information* contentInfos = NULL);
    ExamenParams(const ExamenParams& params);
    ~ExamenParams();

    int width, height, depth;
    float resolutionX, resolutionY, resolutionZ;

    inline Information* getContentInformations() const { return _contentInfos; }

    inline std::string getPath() const { return _path; }
    //inline void setFilename(std::string filename) { _filename = filename; } ! No!!

    /*inline GrayValue& getWindowingMin() const { return *_windowingMin; }
    inline GrayValue& getWindowingMax() const { return *_windowingMax; }*/

    /** Modify the GrayViewWindow to adjust the contrast/luminosity */
    inline GrayViewWindow& getGrayViewWindow() { return *_grayWindowView; }

    inline GrayTranslationFunction& getGrayTranslationFunction() { return _gtf; }

    /*inline float getResolutionX() const { return _dx; }
    inline float getResolutionY() const { return _dy; }
    inline float getResolutionZ() const { return _dz; }
    void setResolution(float dx, float dy, float dz);*/

    /*inline int getSlope() const { return _slope; }
    inline int getIntercept() const { return _intercept; }*/

    //void setParametersSI(int slope, int intercept);
    //void setParametersSI(int slope, int intercept, int Wcenter, int Wwidth, float Sthickness);
    void setParametersSI(/*int Wcenter, int Wwidth, */ float Sthickness);

private:
    Information* _contentInfos;
    MiList<Information*> _lstInfoCoupe;
    Point3D_t<int> _seed;

    std::string _path;
    GrayTranslationFunction _gtf; // slope, intercept
    GrayViewWindow* _grayWindowView;
};

#endif // EXAMEN_PARAMS_H
