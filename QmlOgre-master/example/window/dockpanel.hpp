#ifndef DOCKPANEL_HPP
#define DOCKPANEL_HPP

#include <QWidget>
#include <QtGui>
#include <QString>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QTabWidget>
#include <QGraphicsOpacityEffect>

#include "wprocessing.hpp"
#include "wedition.hpp"
#include "wmanipulation.hpp"
#include "widgetHisto.hpp"
#include "exampleapp.h"

/**
 * @class DockPanel
 * @brief The DockPanel represents the left dock, used to edit or manipulate images
 */
class DockPanel : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructs a DockPanel, widget is passed
     *        to QWidget'constructor.
     * @param parent    parent widget
     */
    explicit DockPanel(QWidget *parent = 0, ExampleApp*a = NULL);
    /**
     * @brief Destructs the DockPanel
     */
    virtual ~DockPanel();

    /**
     * @brief Change panel's opacity
     * @param opaque
     */
    void setOpaque(bool opaque);

    /**
     * @brief return panel opacity
     */
    bool isOpaque();

    /**
     * @brief Configure dock panel and each children panel.
     */
    void setup();

    /**
     * @brief Change the interface language to 'lang'.
     */
    void retranslateUi(const QString& lang);

private:

    /**
     * @brief enterEvent : call when mouse enters the DockPanel
     * @param evt
     */
    void enterEvent(QEvent *evt);

    /**
     * @brief leaveEvent : call when mouse leaves the DockPanel
     * @param evt
     */
    void leaveEvent(QEvent *evt);

    /**
     * @brief Configure the first tab widget.
     */
    void setupTabUp();

    /**
     * @brief Configure the second tab widget.
     */
    void setupTabDown();

    QTabWidget      *_tabUp;             /**< Tab widget to create histograms, contrasts and algorithms*/
    QTabWidget      *_tabDown;           /**< Tab widget to edit or manipulate*/
    WidgetHisto     *_histoWidget ;      /**< histogram panel*/
    QWidget         *_contrastWidget ;   /**< contrast panel*/
    //QWidget         *algoWidget ;       /**< algorithms panel*/
    //QWidget         *editorWidget;      /**< editor panel*/
    WProcessing     *_wProcessing;       /**< contains processing panel */
    WEdition        *_wEdition;          /**< contains edition panel */
    WManipulation   *_wManipulation;     /**< contains manipulation panel */
    QGridLayout     *_mainLayout;        /**< main layout*/
    bool            _opaque;             /**< panel opacity*/
    ExampleApp      *a;
};

#endif // DOCKPANEL_HPP
