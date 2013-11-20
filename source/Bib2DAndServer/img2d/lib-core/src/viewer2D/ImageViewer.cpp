#include <ImageViewer.h>
#include <Image.hpp>
#include <iostream>
using namespace std;

/* -------------------------------------------------------------------------------------------------
     CONSTRUCT & DESTRUCT
   -------------------------------------------------------------------------------------------------*/

ImageViewer::ImageViewer(QWidget *parent) : QLabel(parent)
{
    //RessourceManager::GetInstance()->addRessource("ImageViewer");

    setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    setScaledContents(true);
    setAlignment(Qt::AlignCenter);
    setMouseTracking(true);
    setFocusPolicy(Qt::WheelFocus);

    _defaultImage = NULL;
    _mouseAxesFlag = false;
    _zoom = 1.0;
    _mousePressFlag = false;
    _cursorType = NORMAL;
    _cursorSize = 1;
    _key = 0;
}

ImageViewer::~ImageViewer()
{
    //RessourceManager::GetInstance()->deleteRessource("ImageViewer");
    clear();
}

/* ----------------------------------------------------------------------------------------------------------------
      PUBLIC METHODS
  ----------------------------------------------------------------------------------------------------------------*/

void ImageViewer::setImage(Image<int> *data)
{
    int width = data->getWidth();
    int height = data->getHeight();

    QImage *image = new QImage(width, height, QImage::Format_ARGB32);

    for (int j=0 ; j < height ; j++)
    {
        for (int i=0 ; i < width ; i++)
        {
            int val = data->get(i, j);

            if (val == -1)
                image->setPixel(i, j, qRgb(255, 0, 0));
            else if (val == -2)
                image->setPixel(i, j, qRgb(0, 255, 0));
            else if (val == -3)
                image->setPixel(i, j, qRgb(0, 0, 255));
            else
                image->setPixel(i, j, qRgb(val, val, val));
        }
    }

    delete _defaultImage;
    _defaultImage = image;
    setPixmap(QPixmap::fromImage(*image));
    setScaledContents(true);
    scaled(1.0);
}

void ImageViewer::clear()
{
    QLabel::clear();
    resize(0, 0);
    _zoom = 1.0;
    _defaultImage= NULL;
}

QPixmap ImageViewer::getPixmap()
{
    return QPixmap(*pixmap());
}

void ImageViewer::setMouseAxesEnabled(bool flag)
{
    _mouseAxesFlag = flag;
}

void ImageViewer::scaled(float zoomFactor)
{
    if (pixmap())
    {
        float tmp = _zoom * zoomFactor;
        if ( (tmp < 6.0) && (tmp > 0.2) )
            _zoom = tmp;
        resize(_zoom * pixmap()->size());

    }
}

void ImageViewer::defaultSize()
{
    _zoom = 1.0;
    adjustSize();
}

void ImageViewer::setMouseCursor(CursorType type, int size)
{
    _cursorType = type;
    _cursorSize = size;
}

/* ----------------------------------------------------------------------------------------------------------------
      PRIVATE METHODS
  ------------------------------------------------------------------------------------------------------------------ */

void ImageViewer::drawMouseAxes(int x, int y)
{
    QImage tmp (*_defaultImage);
    if ( (y >=0) && (y < tmp.height()) )
    {
        for (int i=0 ; i <  tmp.width() ; i++)
        {
            tmp.setPixel(i, y, qRgb(255, 0, 0));
        }
    }
    if ( (x >= 0) && (x < tmp.width()) )
    {
        for (int j=0 ; j <  tmp.height() ; j++)
        {
            tmp.setPixel(x, j, qRgb(255, 0, 0));
        }
    }
    setPixmap(QPixmap::fromImage(tmp));
    scaled(1.0);
}

/* ----------------------------------------------------------------------------------------------------------------
      PROTECTED
  ------------------------------------------------------------------------------------------------------------------ */

void ImageViewer::keyPressEvent(QKeyEvent *event)
{
    _key = event->key();
    event->accept();
}

void ImageViewer::keyReleaseEvent(QKeyEvent *event)
{
    _key = 0;
    event->accept();
}

void ImageViewer::enterEvent(QEvent *event)
{
    if (pixmap())
        emit mouseEnter();

    if (_cursorType == NORMAL)
        setCursor(Qt::ArrowCursor);
    else
    {
        int size = _cursorSize * _zoom;
        QPixmap cursor(size+1, size+1);
        cursor.fill(Qt::transparent);
        QPainter paint(&cursor);
        paint.setPen(QColor(127, 127, 127));

        if (_cursorType == SQUARE)
            paint.drawRect(0, 0, size, size);
        else if (_cursorType == CIRCLE)
            paint.drawEllipse(0, 0, size, size);

        paint.end();
        setCursor(QCursor(cursor));
    }
    event->accept();
}

void ImageViewer::leaveEvent(QEvent *event)
{
    if (pixmap())
    {
        setPixmap(QPixmap::fromImage(*_defaultImage));
        emit mouseLeave();
    }
    event->accept();
}

void ImageViewer::mousePressEvent(QMouseEvent *event)
{
    if (pixmap())
    {
        int button = 0;
        int x = event->x() / _zoom;
        int y = event->y() / _zoom;
        int globalX = event->globalX();
        int globalY = event->globalY();
        _mousePressFlag = true;
        if (event->button() == Qt::RightButton)
        {
            _mousePressFlag = false;
            button = 1;
        }
        emit mousePress(x, y, globalX, globalY, button);
    }
    event->accept();
}

void ImageViewer::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (pixmap())
    {
        int button = 0;
        if (event->button() == Qt::RightButton)
        {
            button = 1;
        }
        emit mouseDoubleClick(event->x() / _zoom,
                     event->y() / _zoom, event->globalX(),
                     event->globalY(), button);
    }
    event->accept();
}

void ImageViewer::mouseReleaseEvent(QMouseEvent *event)
{
    if (pixmap())
    {
        int button = 0;
        _mousePressFlag = false;
        if (event->button() == Qt::RightButton)
        {
            button = 1;
        }
        emit mouseRelease(event->x() / _zoom,
                    event->y() / _zoom, event->globalX(),
                    event->globalY(), button);
    }
    event->accept();
}

void ImageViewer::mouseMoveEvent(QMouseEvent *event)
{
    if (pixmap())
    {
        int x = event->x() / _zoom;
        int y = event->y() / _zoom;

        if (_mouseAxesFlag)
            drawMouseAxes(x, y);

        emit mouseMove(x, y);

        if (_mousePressFlag)
            emit mouseMovePress(x, y);
    }
    event->accept();
}

void ImageViewer::wheelEvent(QWheelEvent *event)
{
    if (pixmap())
    {
        if (event->delta() > 0)
        {
            if (_key == Qt::Key_Control)
                scaled(1.25);
            else {
                //cout << "plopyop" << endl;
                emit mouseWheelUp();

            }
        }
        else
        {
            if (_key == Qt::Key_Control)
                scaled(0.8);
            else
                emit mouseWheelDown();
        }
        enterEvent(event);
    }
    event->accept();
}

