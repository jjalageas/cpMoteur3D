#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QSplitter>
#include <QFrame>
#include <QMenuBar>
#include <QKeySequence>
#include <QGridLayout>

#include "dockpanel.hpp"
#include "view4boxes.hpp"
#include "menubar.hpp"


/**
 * @class MainWindow
 * @brief This class represents the main window.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Constructs a MainWindow, widget is passed
     *        to QMainWindow'constructor.
     * @param parent    parent widget
     */
    MainWindow(QWidget *parent = 0);

    /**
     * @brief Destructs the MainWindow.
     */
    virtual ~MainWindow();

    View4Boxes  *getView4Boxes();

    /**
     * @brief Change style interface to style No 1.
     */
    void putStyle1();

    /**
     * @brief Change style interface to style No 2.
     */
    void putStyle2();

public slots:
    /**
     * @brief Change interface view mode to View No 1.
     */
    void viewN1();

    /**
     * @brief Change interface view mode to View No 2.
     */
    void viewN2();

    /**
     * @brief Change interface language.
     */
    void changeLanguage(const QString & lang);

    /**
     * @brief createSecondWindow
     */
    void createSecondWindow();

    /**
     * @brief closeSecondWindow
     */
    void closeSecondWindow();

protected:
    /**
     * @brief This event is called, when a new translator is loaded or the system language is changed.
     */
    void changeEvent(QEvent*);

private:
    /**
     * @brief Loads a language by the given language shortcur (e.g. de, en, ...).
          */
    void loadLanguage(const QString& lang);

    /**
     * @brief switchTranslator
     * @param translator
     * @param filename
     */
    void switchTranslator(QTranslator &translator, const QString &filename);

    /**
     * @brief mouseMoveEvent : call when mouse moves.
     */
    void mouseMoveEvent(QMouseEvent *);

    /**
     * @brief Configure the DockControle (Left dock).
     */
    void setupLeftDock();

    /**
     * @brief Setup central widget.
     */
    void setupCentralWidget();

    /**
     * @brief Change the interface language to 'lang'.
     */
    void retranslateUi(const QString& lang);

private:

    QDockWidget     *_leftDock;              /**< Represents the left panel */
    DockPanel       *_leftPanel;             /**< Left dock to edit and manipulate images */
    View4Boxes      *_view4Boxes;            /**< Contains each widget put in the workspace */
    View4Boxes      *_secondWindow;          /**< Represents the second window when dual screen option is activated and no 2 screen avalaible */
    QGridLayout     *_centralWidgetLayout;   /**< Contains the central widget */
    QWidget         *_centralWidget;         /**< Represents the workspace */
    MenuBar         *_menuBar;             /**< Represents the Menu bar */

    QTranslator     *_translator;          /**< contains the translations for this application */
    QString         _currLang;             /**< contains the currently loaded language */
    bool            _view;                  /**< true if view n°1 is active, false otherwise */
};

#endif // MAINWINDOW_HPP
