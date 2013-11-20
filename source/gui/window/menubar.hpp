#ifndef MENUBAR_HPP
#define MENUBAR_HPP

#include <QDir>
#include <QMenuBar>
#include <QFileDialog>
#include <QMainWindow>

/**
 * @class MenuBar
 * @brief This class represents the menu bar.
 */
class MenuBar : public QMenuBar
{
    Q_OBJECT
public:
    /**
     * \brief Constructs a MenuBar, widget is passed
     *        to QMenuBar'constructor.
     * \param parent    parent widget
     */
    MenuBar(QMenuBar *parent = 0);

    /**
     * @brief Destructs the MainWindow.
     */
    virtual ~MenuBar() {}

    /**
     * @brief Create menus for the menu bar.
     */
    void createMenus();

    /**
     * @brief Create actions for each option in the menu bar.
     */
    void createActions();

    /**
     * @brief Change to view 1
     */
    QAction *getView1();

    /**
     * @brief Change to view 2
     */
    QAction *getView2();

    /**
     * @brief Change the interface language to 'lang'.
     */
    void retranslateUi(const QString& lang);

private slots:

    /**
     * @brief Change the interface by its styleDefault
     */
    void slotStyleDefault();

    /**
     * @brief Change the interface by its StyleGlobal
     */
    void slotStyleGlobal();

    /**
     * @brief Change the interface by its StyleWindows8
     */
    void slotStyleWindows8();

    /**
     * @brief Translate the application To French
     */
    void slotChangeLanguageToFrench();

    /**
     * @brief Translate the application To English
     */
    void slotChangeLanguageToEnglish();

    /**
     * @brief Translate the application To Spanish
     */
    void slotChangeLanguageToSpanish();

    /**
     * @brief Called when the 'Open' action is invoked.
     */
    void slotOpen();

    /**
     * @brief Called when the 'Save' action is invoked.
     */
    void slotSave();

    /**
     * @brief Called when the 'Dual Screen' action is invoked.
     */
    void slotDualScreen();

private:
    QMenu *fileMenu;            /**< Menu File */
    QMenu *optionMenu;          /**< Menu Option */
    QMenu *viewMenu;            /**< Menu View */
    QMenu *language;            /**< SubMenu Language */
    QMenu *skin;                /**< SubMenu Skin */

    QAction *actionOpen;        /**< Action Open */
    QAction *actionSave;        /**< Action Save */
    QAction *actionExit;        /**< Action Exit */
    QAction *actionDualScreen;  /**< Action Dual Screen */
    QAction *actionView1;             /**< Action display mode #1 */
    QAction *actionView2;             /**< Action display mode #2 */
    QAction *actionFrench;      /**< Action French */
    QAction *actionEnglish;     /**< Action English */
    QAction *actionSpanish;     /**< Action Spanish */
    QAction *actionStyleDefault;      /**< Action Default Style */
    QAction *actionStyle1;            /**< Action style1 */
    QAction *actionStyle2;            /**< Action style2 */

    QString m_projectFile;      /**< Filename of the project*/
};

#endif // MENUBAR_HPP
