#include "wprocessing.hpp"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Main window
    QWidget widget;
    widget.setFixedSize(600, 800);

    // Display our widget
    WProcessing wp(&widget);
    widget.show();
    return app.exec();
}
