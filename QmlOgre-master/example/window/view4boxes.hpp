#ifndef VIEW4BOXES_HPP
#define VIEW4BOXES_HPP

#include <QWidget>
#include <QQueue>
#include <QGridLayout>
#include <QDockWidget>

/**
 * @class View4Boxes
 * @brief This class represents the workspace.
 */
class View4Boxes : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructs a View4Boxes, parent is passed
     *        to QWidget'constructor.
     * @param parent    parent widget
     */
    View4Boxes(QWidget *parent = 0);

    /**
     * @brief Copy contructor
     */
    View4Boxes(const View4Boxes& other, QWidget *parent=0);

    /**
     * @brief Reimplemented operator=
     */
    View4Boxes &operator=(const View4Boxes &other);

    /**
     * @brief setVues
     * @param widget
     */
    void setVues(QWidget*widget);

    /**
     * @brief setVues
     * @param queuWidget
     */
    void setVues(QQueue<QWidget *> queuWidget);

    /**
     * @brief clearLayout
     */
    void clearLayout();

    /**
     * @brief Clear layout at position 'index'
     */
    void clearLayoutAtPosition(int index);

    /**
     * @brief setup8Boxes
     */
    void setup8Boxes();

    /**
     * @brief remove8Boxes
     */
    void remove8Boxes();

    /**
     * @brief getMainLayout
     */
    QGridLayout * getMainLayout();

private :
    /**
     * @brief setupInterface
     */
    void setupInterface();

    QGridLayout *_mainLayout;    /**< Contains left workspace widgets */
    QDockWidget *_wrdock;        /**< Contains right workspace widgets*/
};

#endif // VIEW4BOXES_HPP
