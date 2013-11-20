#include "GrayValue.h"
#include "debug.h"

using namespace std;

//////////
// Gray Translation Function
///

GrayTranslationFunction::GrayTranslationFunction(int slope, int intercept) :
    _slope(slope),
    _intercept(intercept)
{
    //eassert(slope != 0);
    //cout << "Slope : " << slope << ", int " << intercept << endl;
}

float
GrayTranslationFunction::fromHU(int huVal) const
{
    return (huVal - _intercept) / _slope;
}

int
GrayTranslationFunction::toHU(float val)  const
{
    return val * _slope + _intercept;
}

//////////
// Gray Value
///

GrayValue::GrayValue(const GrayTranslationFunction &t) :
    _t(t)
{}

GrayValue*
GrayValue::copy() const
{
    return new HundsfieldValue(_t, this->getHundsfieldValue()); // easy! :-D
}


GrayValue*
GrayValue::copy(const GrayTranslationFunction &t) const
{
    // Caution here ! This g value could come from another examen that the one we
    // intend to give a value to. Only HundsField values are normalized !
    // => the grayTranslationFunction may differ.
    // => We cannot trust the examValue
    return new HundsfieldValue(t, this->getHundsfieldValue());
}

GrayValue::~GrayValue()
{}

//////////
// Hundsfield Value
///
const float HundsfieldValue::_max;
const float HundsfieldValue::_min;

HundsfieldValue::HundsfieldValue(const GrayTranslationFunction& t, int value)
    : GrayValue(t)
{
    if (value > _max *2) { // *2 for intervals
        cerr << "Too big hundsfield value : " << value << endl;
        value = _max;
    }
    else if (value < _min *2) { // *2 for intervals
        cerr << "Too little hundsfield value : " << value << endl;
        value = _min;
    }
    _value = value;
}

/*HundsfieldValue::HundsfieldValue(const HundsfieldValue& v)
    : _value(v._value),
      _slope(v._slope),
      _intercept(c._intercept)
{}*/

float
HundsfieldValue::getExamenValue() const
{
    return _t.fromHU(_value);
}

int
HundsfieldValue::getHundsfieldValue() const
{
    return _value;
}

int
HundsfieldValue::max()
{
    return _max;
}

int
HundsfieldValue::min()
{
    return _min;
}

/*GrayValue*
HundsfieldValue::clone() const {
    return new HundsfieldValue(this);
}*/

//////////
// Examen Gray Value
///

ExamenGrayValue::ExamenGrayValue(const GrayTranslationFunction &t, float value)
    : GrayValue(t), _value(value)
{
    if (_t.toHU(_value) > 2*HundsfieldValue::max()) { // *2 for intervals
        cerr << "Too big examen value : " << value << endl;
        value = _t.fromHU(HundsfieldValue::max()) *2;
    }
    else if (_t.toHU(_value) < 2*HundsfieldValue::min()) { // *2 for intervals
        cerr << "Hundsfiled val : " << _t.toHU(_value) << endl;
        cerr << "Too little examen value : " << value << endl;
        value = _t.fromHU(HundsfieldValue::min()) *2;
    }
    _value = value;
}

/*ExamenGrayValue::ExamenGrayValue(const ExamenGrayValue& v)
    : _value(v._value),
      _slope(v._slope),
      _intercept(c._intercept)
{}*/

float
ExamenGrayValue::getExamenValue() const
{
    return _value;
}

int
ExamenGrayValue::getHundsfieldValue() const
{
    return _t.toHU(_value);
}

/*GrayValue*
ExamenGrayValue::clone() const
{
    return new ExamenGrayValue(this);
}*/
