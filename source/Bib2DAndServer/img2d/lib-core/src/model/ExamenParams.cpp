#include <ExamenParams.h>
#include <Information.h>

using namespace std;


ExamenParams::ExamenParams(GrayTranslationFunction& gtf, string &path, Information* contentInfos) // -_- TODO : add parameters
    :
      width(0), height(0), depth(0),
      resolutionX(0.7), resolutionY(0.7), resolutionZ(1.),
      _contentInfos(contentInfos),
      _seed(Point3D_t<int>(-1, -1, -1)), _path(path),
      _gtf(gtf)
      // _windowingMin(new HundsfieldValue(gtf, -1024)), _windowingMax(new HundsfieldValue(gtf, 1024)),
{
    _grayWindowView = GrayViewWindow::createFromMinMax(_gtf,
                                                       HundsfieldValue::min(),
                                                       HundsfieldValue::max());
    if (_contentInfos == NULL)
        _contentInfos = new Information();
}

ExamenParams::ExamenParams(const ExamenParams& params)
    : width        (params.width       ),
      height       (params.height      ),
      depth        (params.depth       ),
      resolutionX  (params.resolutionX ),
      resolutionY  (params.resolutionY ),
      resolutionZ  (params.resolutionZ ),
      _contentInfos(params._contentInfos),
      _lstInfoCoupe(params._lstInfoCoupe),
      _seed        (params._seed        ),
      _path        (params._path        ),
      _gtf         (params._gtf         ),
      _grayWindowView(new GrayViewWindow(*params._grayWindowView))
{}

ExamenParams::~ExamenParams()
{
    delete _contentInfos;   _contentInfos = NULL;
    delete _grayWindowView; _grayWindowView = NULL;
}

/*void
ExamenParams::setResolution(float dx, float dy, float dz)
 {
    _dx = dx;
    _dy = dy;
    _dz = dz;
}*/

/*void
ExamenParams::setParametersSI(int slope, int intercept)
{
    _slope = slope;
    _intercept = intercept;
}*/

/*void
ExamenParams::setParametersSI(float Sthickness)
{
    //_Sthickness = Sthickness;
}*/


// GrayTranslationFunction : if you want to change it in the future
// you must change it in the GrayViewWindow member too.
