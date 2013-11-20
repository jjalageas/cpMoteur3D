#include <QApplication>
#include <QtGui>
#include "MainWindow.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QTranslator translator;
    qDebug() << translator.load("WidgetManipulation2D3D_en");
    app.installTranslator(&translator);

    /* * *
     *  Pour n'importe quels langues
     * * *

        QString locale = QLocale::system().name().section('_', 0, 0);

        QTranslator translator;
        translator.load(QString("WidgetManipulation2D3D_") + locale);
        app.installTranslator(&translator);
    */

    MainWindow mw;
    mw.show();

    return app.exec();
}
