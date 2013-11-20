#ifndef GRAYVIEWWINDOW_H
#define GRAYVIEWWINDOW_H

#include <GrayValue.h>


/**
  Interval of gray levels visualized.
  You must set a gray translated function associated to
  a unique Examen / a unique image / a unique dicom file
  - The contrast is guaranted to be strictly positive
  - Changing the contrast may change the luminosity, and the contrary
  */
class GrayViewWindow
{
public:
    static GrayViewWindow* createFromLuminosityContrast(GrayTranslationFunction &gtf,
                                        int huLuminosity, int huContrast);
    static GrayViewWindow* createFromMinMax(GrayTranslationFunction &gtf, int, int);
    GrayViewWindow(const GrayViewWindow&);

    void setGrayTranslationFunction(GrayTranslationFunction &gtf);

    GrayValue* getMin() const;
    GrayValue* getMax() const;

    GrayValue* getLuminosity() const;
    GrayValue* getContrast() const;

    void setMin(int huMin);
    void setMax(int huMax);
    void setRange(int huMin, int huMax);

    void setLuminosity(int huLum);
    /** The contrast is guaranted to be strictly positive */
    void setContrast(int huContr);

protected:
    enum ContrastWindow { CONTRAST, WINDOW };
    GrayViewWindow(GrayTranslationFunction &gtf, int huMin, int huMax, ContrastWindow mode);
    void updateInterval(ContrastWindow);
    int _min, _max;
    int _lum, _contrast;
    GrayTranslationFunction _gtf;
    //ContrastWindow _currentMode;
};

#endif // GRAYVIEWWINDOW_H
