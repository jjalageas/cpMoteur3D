#include "Window.h"

Window::Window(int argc, char** argv)
{
    glWidgetVolume = new GLWidget;
    glWidgetCoupes = new GLWidget;
    image2D = new MyQlabel();

    next = new QPushButton("Next");
    previous = new QPushButton("Previous");

    QVBoxLayout *layout = new QVBoxLayout();
    QGridLayout *layout1 = new QGridLayout();
    QHBoxLayout *layout2 = new QHBoxLayout();

    layout1->addWidget(glWidgetCoupes, 0, 0, 4, 3);
    layout1->addWidget(glWidgetVolume, 0, 3, 2, 2);
    layout1->addWidget(image2D, 2, 3, 2, 2);

    layout2->addWidget(previous);
    layout2->addWidget(next);

    layout->addLayout(layout1);
    layout->addLayout(layout2);

    setLayout(layout);

    QObject::connect(next, SIGNAL(clicked()), this, SLOT(on_Next_clicked()));
    QObject::connect(previous, SIGNAL(clicked()), this, SLOT(on_Previous_clicked()));

    QObject::connect(image2D, SIGNAL(click(int,int)), this, SLOT(on_Press(int, int)));

    setMinimumSize(1200,800);
    setMaximumSize(1200,800);

    setWindowTitle(tr("Moteur 3D OpenGL"));
}

void Window::refreshImage()
{
    Image3d<float> *tmp = examen->getImage2D(index,0);
    ImageData<float> *img = tmp->toImagedata();
    img->normalizeHfield(255,examen->getWcenter(),examen->getWwidth());
    parsMan->save2DFile("tmp.ppm",img,"ppm");
    delete img;
    delete tmp;

    QPixmap pixMap("tmp.ppm");
    image2D->setPixmap(pixMap);
}

void Window::clearList()
{
    pointsListTrans->empty();
    pointsListFront->empty();
    pointsListSagit->empty();
    pointsListCoupes->empty();
    pointsListVolume->empty();
}

void Window::on_Previous_clicked()
{
    if(index > 0)
    {
        index = index-10;

        examen->setDefaultWindow();
        AlgoVolume::biseuillage3D(examen);

        clearList();

        pointsListTrans = ImageTranscriber::FromVolumeToImage2D(examen, index, 0);
        pointsListFront = ImageTranscriber::FromVolumeToImage2D(examen, index, 1);
        pointsListSagit = ImageTranscriber::FromVolumeToImage2D(examen, index, 2);

        pointsListCoupes->append(*pointsListTrans);
        pointsListCoupes->append(*pointsListFront);
        pointsListCoupes->append(*pointsListSagit);

        glWidgetCoupes->setListPoints(pointsListCoupes);

        refreshImage();
    }
}

void Window::on_Next_clicked()
{
    if(index < examen->getSize()-1)
    {
        index = index+10;

        examen->setDefaultWindow();
        AlgoVolume::biseuillage3D(examen);

        clearList();

        pointsListTrans = ImageTranscriber::FromVolumeToImage2D(examen, index, 0);
        pointsListFront = ImageTranscriber::FromVolumeToImage2D(examen, index, 1);
        pointsListSagit = ImageTranscriber::FromVolumeToImage2D(examen, index, 2);

        pointsListCoupes->append(*pointsListTrans);
        pointsListCoupes->append(*pointsListFront);
        pointsListCoupes->append(*pointsListSagit);

        glWidgetCoupes->setListPoints(pointsListCoupes);

        refreshImage();
    }
}

void Window::on_Press(int x, int y)
{
    examen->setSeed(x,y,index);
    float val = examen->getPixel(x, y, index);
    examen->setWindowingRange(val-18,val+18);

    AlgoVolume::biseuillage3D(examen);
    AlgoVolume::CTRG2(examen);

    clearList();

    pointsListVolume = ImageTranscriber::FromVolume(examen);
    glWidgetVolume->setListPoints(pointsListVolume);
}

GLWidget * Window::getWidgetVolume()
{
    return glWidgetVolume;
}

GLWidget * Window::getWidgetCoupes()
{
    return glWidgetCoupes;
}

Examen * Window::getExamen()
{
    return examen;
}

void * Window::setExamen(Examen *exam)
{
    examen = exam;
}

int Window::getIndex()
{
    return index;
}

void Window::setIndex(int i)
{
    index = i;
}
