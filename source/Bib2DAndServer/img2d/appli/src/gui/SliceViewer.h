#ifndef SLICEVIEWER_H
#define SLICEVIEWER_H

#include <QWidget>
#include <Examen.h>
#include <ImageMask2d.h>
#include <GrayViewWindow.h>

namespace Ui {
class SliceViewer;
}

class SliceViewer : public QWidget
{
    Q_OBJECT
    
public:
    explicit SliceViewer(QWidget *parent = 0);
    ~SliceViewer();
    void setExamen(Examen*);

protected:
    void updateIHM(bool loosePredefinedInterval);
    void addPredefinedWindowCW(std::string name, int center, int width);
    void addPredefinedWindow(std::string name, int min, int max);

private:
    Ui::SliceViewer *ui;
    Examen *_exam;
    ImageMask2d* _imgMask;
    int _sliceIndex; // currently displayed slice index
    GrayViewWindow *_window;
    SliceType _type;



    class PredefinedWindow {
    public:
        PredefinedWindow(int min, int max) :
            min(min), max(max)
        {}

        int min, max;
    };

    std::vector<PredefinedWindow> _predefinedWindows;

private slots:
    void mouseWheelUp();
    void mouseWheelDown();
    void updateImage();
    void selectMode();
    void selectSliceType(int);
    void luminositySlideValueChanged(int);
    void contrastSlideValueChanged(int);
};


#endif // SLICEVIEWER_H
