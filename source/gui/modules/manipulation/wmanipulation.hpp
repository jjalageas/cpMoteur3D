#ifndef WMANIPULATION_H
#define WMANIPULATION_H

#include <QTabWidget>
#include <QWidget>
#include <QSpinBox>
#include <QComboBox>
#include <QCheckBox>
#include <QLabel>

/**
 * @class WManipulation
 * @brief Classe créant le widget pour la Manipulation 2D, 3D.
 */
class WManipulation : public QTabWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructeur de la classe WManipulation.
     * Créé le widget pour la Manipulation 2D, 3D, c-à-d, les deux onglets
     * contenant tous les objets nécessaires.
     * @param pas de paramètres.
     * @return .
    */
    WManipulation(QTabWidget* widget);
    /**
     * @brief Destructeur de la classe WManipulation.
     * Supprime les 2 onglets.
     * @param pas de paramètres.
     * @return .
     */
    ~WManipulation();
    /**
     * @brief Change the interface language to 'lang'.
     */
    void retranslateUi(const QString &lang);

private:
    /** Partie 2D */
    QWidget *manip2D;               /**< l'onglet de notre widget qui concerne la manipulation 2D */
    QSpinBox *spinx;                /**< Spinbox qui gère les translation en x */
    QSpinBox *spiny;                /**< Spinbox qui gère les translation en y */
    QSpinBox *spinz;                /**< Spinbox qui gère les translation en z (zoom) */
    QComboBox *viewType2D;          /**< Combobox qui gère le choix du type de vue (4box, 8box) */

    /** Partie 3D */
    QWidget *manip3D;               /**< l'onglet de notre widget qui concerne la manipulation 3D */
    QSpinBox *spinTextureX;         /**< Spinbox qui gère la texture en x */
    QSpinBox *spinTextureY;         /**< Spinbox qui gère la texture en y */
    QSpinBox *spinTextureZ;         /**< Spinbox qui gère la texture en z */
    QLabel *labelTextureX;          /**< Label du spinbox qui gère la texture en x */
    QLabel *labelTextureY;          /**< Label du spinbox qui gère la texture en y */
    QLabel *labelTextureZ;          /**< Label du spinbox qui gère la texture en z */
    QCheckBox *picture;             /**< Checkbox permettant d'afficher ou non l'image */
    QCheckBox *mask;                /**< Checkbox permettant d'afficher un masque prédéfinit ou non */
    QComboBox *viewType3D;          /**< Combobox qui gère le choix du type de vue (4box, 8box) */
    QComboBox *transformationType;  /**< Combobox qui gère le choix du type de transformation (Volume, Maillage ...) */

public slots:
    /**
     * @brief Fonction appelé par le SIGNAL de la combobox,
     * permettant de choisir le type de vue qu'on veut (4 box, 8 box).
     * @param int index : correspond au numéro de l'index correspondant.
     * @return .
    */
    void displayViewType(int index);
    /**
     * @brief Fonction appelé par le SIGNAL de la combobox,
     * permettant de choisir le type de transformation que l'on veut effectuer
     * (mask, maillage ...).
     * @param int index : correspond au numéro de l'index correspondant.
     * @return .
    */
    void displayTransformationType(int index);
    /**
     * @brief Fonction appelé par le SIGNAL de la checkbox,
     * permettant de choisir si on affiche l'image ou non.
     * @param bool active : booleen permettant de savoir si la checkbox est active ou non.
     * @return .
    */
    void displayPictureOrNot(bool active);
    /**
     * @brief Fonction appelé par le SIGNAL de la checkbox,
     * permettant de choisir si on affiche le masque ou non.
     * @param bool active : booleen permettant de savoir si la checkbox est active ou non.
     * @return .
    */
    void displayMaskOrNot(bool active);
};

#endif // WMANIPULATION_H

