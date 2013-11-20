#ifndef CORAL_HPP
#define CORAL_HPP

#include <QApplication>

#include "window/mainwindow.hpp"

/**
 * \class Coral
 * \brief This singleton class represents the application.
 */
class Coral : public QApplication
{
public:
    /**
     * \brief Gets an instance of the application.
     *
     * \param argc      number of line arguments
     * \param argv      array of line arguments
     */
    static Coral *instance(int argc = 0, char **argv = NULL);

    /**
     * \brief Deletes the instance.
     */
    static void drop();

    /**
     * \brief Runs the application.
     */
    int run();

    /**
     * \brief Gets the window.
     */
    MainWindow *window() {
        return m_window;
    }

private:
    /**
     * Disabled these following methods for singleton pattern.
     */
    Coral(int argc, char ** argv);
    virtual ~Coral();
    Coral(const Coral &);
    Coral & operator=(const Coral &);

    static Coral *m_instance;           /**< instance of application */
    MainWindow *m_window;               /**< window of application */
};

#endif // CORAL_HPP
