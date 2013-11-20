#include "coral.hpp"

Coral * Coral::m_instance = 0;

Coral::Coral(int argc, char **argv)
    : QApplication(argc, argv)
{
    m_window = NULL;
}

Coral::~Coral()
{
    delete m_window;
}

Coral * Coral::instance(int argc, char **argv)
{
    if (!m_instance)
        m_instance = new Coral(argc, argv);

    return m_instance;
}

void Coral::drop()
{
    delete m_instance;
    m_instance = 0;
}

int Coral::run()
{
    m_window = new MainWindow();
    qPrintable(m_window->objectName());
    m_window->show();
    return exec();
}
