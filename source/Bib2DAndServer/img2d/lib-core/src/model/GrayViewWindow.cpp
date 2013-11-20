#include <GrayViewWindow.h>
#include <debug.h>
#include <cmath>
#include <iostream>
using namespace std;

GrayViewWindow* GrayViewWindow::createFromLuminosityContrast(GrayTranslationFunction &gtf,
                                    int huLuminosity, int huContrast)
{
    return new GrayViewWindow(gtf, huLuminosity, huContrast, CONTRAST);
}

GrayViewWindow* GrayViewWindow::createFromMinMax(GrayTranslationFunction &gtf,
                        int huMin, int huMax)
{
    return new GrayViewWindow(gtf, huMin, huMax, WINDOW);
}

GrayViewWindow::GrayViewWindow(GrayTranslationFunction &gtf, int val1, int val2,
                               ContrastWindow mode)
    : _gtf(gtf)
{
    if (mode == WINDOW) {
        _min = val1;
        _max = val2;
    }
    else {
        _lum = val1;
        _contrast = val2;
    }
    updateInterval(mode);
}

GrayViewWindow::GrayViewWindow(const GrayViewWindow& g)
    : _min(g._min),
      _max(g._max),
      _lum(g._lum),
      _contrast(g._contrast),
      _gtf(g._gtf)
{}

void
GrayViewWindow::setGrayTranslationFunction(GrayTranslationFunction &gtf) {
    _gtf = gtf;
}

GrayValue*
GrayViewWindow::getMin() const {
    return new HundsfieldValue(_gtf, _min);
}

GrayValue*
GrayViewWindow::getMax() const {
    return new HundsfieldValue(_gtf, _max);
}

GrayValue*
GrayViewWindow::getLuminosity() const {
    return new HundsfieldValue(_gtf, _lum);
}

GrayValue*
GrayViewWindow::getContrast() const {
    return new HundsfieldValue(_gtf, _contrast);
}

void
GrayViewWindow::setMin(int huMin) {
    /*if (_currentMode == CONTRAST) {
        toMinMaxState();
    }*/
    eassert(huMin >= HundsfieldValue::min());
    _min = huMin;
    if (_min == HundsfieldValue::max()) {
        _max = _min--;
    } else if (_max < huMin) {
        _max = _min +1;
    }
    updateInterval(WINDOW);
}

void
GrayViewWindow::setMax(int huMax) {
    /*if (_currentMode == CONTRAST) {
        toMinMaxState();
    }*/
    eassert(huMax <= HundsfieldValue::max());
    _max = huMax;
    if (_max == HundsfieldValue::min()) {
        _min = _max++;
    } else if (_min > huMax) {
        _min = _max -1;
    }
    updateInterval(WINDOW);
}

void
GrayViewWindow::setRange(int huMin, int huMax) {
    setMin(huMin);
    setMax(huMax);

    updateInterval(WINDOW);
}

void
GrayViewWindow::setLuminosity(int huLum) {
    eassert(abs(huLum) <= HundsfieldValue::max());
    _lum = huLum;
    updateInterval(CONTRAST);
/*
    int maxContrast = HundsfieldValue::max() - abs(huLum);
    if (_max - _min > maxContrast)
        setContrast(maxContrast);

    int currentLum = (_max + _min) / 2;
    int diff = huLum - currentLum;
    _max += diff;
    _min += diff;
*/
}

void
GrayViewWindow::setContrast(int huContr) {
    eassert(huContr < HundsfieldValue::max());
    eassert(huContr >= 0);
    _contrast = huContr;
/*
    int currentLum = (_max + _min) / 2;
    //int currentContrast = _max - _min;
    //int diff = (huContr - currentContrast) /2;
    _max = currentLum + huContr/2;
    _min = currentLum - huContr/2;*/
    updateInterval(CONTRAST);
}

void
GrayViewWindow::updateInterval(ContrastWindow mode) {
    if (mode == WINDOW) {
        _lum = .5 * (_max + _min);
        _contrast = HundsfieldValue::max() - (_max - _min);
    }

    if (mode == CONTRAST) {
        _min = _lum - (HundsfieldValue::max() - _contrast);
        if (_min < HundsfieldValue::min())
            _min = HundsfieldValue::min();
        _max = _lum + (HundsfieldValue::max() - _contrast);
        //cout << "_max : " << _max << endl;
        if (_max > HundsfieldValue::max())
            _max = HundsfieldValue::max();
        if (_max == _min) {
            if (_max != HundsfieldValue::max())
                ++_max;
            else
                --_min;
        }
    }
    eassert(_max > _min);

    #ifndef NDEBUG
        // debug display -> does not cover each pb : the aim is to show
        // when a value in particular is incoherent as it entered the object.
        /*if (mode == WINDOW) {
            if (_min < HundsfieldValue::min()) {
                cerr << "GrayViewWindow min is too little : " << _min << endl;
                eassert(false);
            }
            else if (_max > HundsfieldValue::max()) {
                cerr << "GrayViewWindow max is too big : " << _max << endl;
                eassert(false);
            }
        }
        else {
            int lum = (_max + _min) / 2;
            if (lum < HundsfieldValue::min() || lum > HundsfieldValue::max()) {
                cerr << "GrayViewWindow luminosity is anormal : " << lum << endl;
                eassert(false);
            }
            int contr = _max - _min;
            if (contr < 0 || contr > HundsfieldValue::max() - HundsfieldValue::min()) {
                cerr << "GrayViewWindow contrast is too big : " << contr << endl;
                eassert(false);
            }
        }*/
    #else
    (void) mode;
    #endif


    /*if (_max > HundsfieldValue::max())
        _max = HundsfieldValue::max();
    if (_min < HundsfieldValue::min())
        _max = HundsfieldValue::min();
    if (_max <= _min + 1) { // avoid 0 or negative contrast
        int mean = (_max + _min) / 2;
        _max = _min = mean;
        if (_max >= HundsfieldValue::max())
            --_min;
        else if (_min <= HundsfieldValue::min())
            ++_max;
        else
            ++_max;
    }*/
}
