#ifndef GRAYVALUE_H
#define GRAYVALUE_H

#include <iostream>


/**
   Convert back and forth a value read from a dicom file to HundsField unit.
   The dicom format uses the slope and intercept values to process this conversion\n
   => A GrayTranslationFunction is associated to a Dicom file and cannot be used
   with another dicom file...
  */
class GrayTranslationFunction {
public:
    GrayTranslationFunction(int slope, int intercept);
    float fromHU(int huVal) const;
    int toHU(float val) const;

    inline int getSlope() { return _slope; }
    inline int getIntercept() { return _intercept; }

private:
    int _slope;
    int _intercept;
};

// base value in [0, 4095] ? -> may depend on slope and intercept
// Hundsfield in [-1024, 1024]

/**
   Gray values represent gray levels of the images.
   They can be represented as Hundsfield values (normalized unit)
   or as image storage unit. The conversion is realized using a GrayTranslationFunction.\n
   Caution : a gray value is associated to an image or a dicom file.
   If necessary, copy it with another GrayTranslationFunction to use it
   in another Dicom file.
  */
class GrayValue
{
public:
    /** You should select a GrayTranslationFunction if the current GrayValue
     and the new GrayValue will live in different contexts (ie different image sources) */
    GrayValue* copy(const GrayTranslationFunction &t) const;
    GrayValue* copy() const;

    /** Get a value of the gray level that is compatible with the image encoding format */
    virtual float getExamenValue() const = 0;
    /** Get a value of the gray level in HundsField unit */
    virtual int getHundsfieldValue() const = 0;
    //virtual GrayValue* clone() = 0;

    virtual ~GrayValue();
protected:
    GrayValue(const GrayTranslationFunction &t);
    const GrayTranslationFunction _t;
};


class HundsfieldValue : public GrayValue {
public:
    HundsfieldValue(const GrayTranslationFunction& t, int value);
    //HundsfieldValue(const HundsfieldValue&);

    float getExamenValue() const;
    int getHundsfieldValue() const;

    static int max();
    static int min();
    //GrayValue* clone() const;

private:
    float _value;
    static const float _max = 2048; // -1024->1024
    static const float _min = -2048;// but more is tolerated.
};


class ExamenGrayValue : public GrayValue {
public:
    ExamenGrayValue(const GrayTranslationFunction&, float value);
    //ExamenGrayValue(const ExamenGrayValue&);
    float getExamenValue() const;
    int getHundsfieldValue() const;
    //GrayValue* clone() const;

private:
    float _value;
};

#endif // GRAYVALUE_H
