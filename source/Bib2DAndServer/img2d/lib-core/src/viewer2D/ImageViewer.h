#ifndef IMAGE_VIEWER_H
#define IMAGE_VIEWER_H

#include <QtGui>
#include <Struct.hpp>
#include <Image3d.hpp>

template<typename T> class Image;


enum CursorType {
       NORMAL = 0,
       SQUARE = 1,
       CIRCLE = 2
};

class ImageViewer : public QLabel
{
       Q_OBJECT

public:

       ImageViewer(QWidget *parent = 0);
       ~ImageViewer();

       void setImage(Image<int> *image);
       QPixmap getPixmap();
       void clear();

       void setMouseCursor(CursorType, int);
       void setMouseAxesEnabled(bool);

       void scaled(float zoomFactor);
       void defaultSize();

protected:

       void keyPressEvent(QKeyEvent *);
       void keyReleaseEvent(QKeyEvent *);
       void enterEvent(QEvent *);
       void leaveEvent(QEvent *);
       void mousePressEvent(QMouseEvent *);
       void mouseDoubleClickEvent(QMouseEvent *);
       void mouseReleaseEvent(QMouseEvent *);
       void mouseMoveEvent(QMouseEvent *);
       void wheelEvent(QWheelEvent *);

signals:

       void mouseEnter();
       void mouseLeave();
       void mousePress(int x, int y, int globalX, int globalY, int button);
       void mouseRelease(int x, int y, int globalX, int globalY, int button);
       void mouseDoubleClick(int x, int y, int globalX, int globalY, int button);
       void mouseMove(int x, int y);
       void mouseMovePress(int x, int y);
       void mouseWheelUp();
       void mouseWheelDown();

private:

       void drawMouseAxes(int x, int y);

       QImage *_defaultImage;
       CursorType _cursorType;
       int _cursorSize;
       bool _mouseAxesFlag;
       float _zoom;
       bool _mousePressFlag;
       int _key;
};

#endif
