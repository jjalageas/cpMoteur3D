#ifndef INFORMATION_H
#define INFORMATION_H

#include "Struct.hpp"

#include <string>


/**
  * @class Information
  * @brief Classe permettant le stockage d'une liste d'information.
  *
  * Les informations sont stockées sous forme de couples
  * (titre, description) de type string.
  */
class Information
{
public:
    /**
         * @brief Destructeur
         *
         * Destructeur de la classe Information.
         */
    ~Information();

    /**
         * @brief Ajout d'information
         *
         * Méthode permettant d'ajouter un couple
         *(title ,description) passé en paramètre à l'objet.
         *
         * @param title : titre de l'information
         * @param description : description de l'information
         */
    void addInformation(std::string title, std::string description);

    /**
         * @brief Accès à un titre d'une information
         *
         * Retourne le titre d'une information contenu dans la liste.
         *
         * @return titre de la n-ième information de l'objet.
         */
    std::string getTitle(int n);

    /**
         * @brief Accès à une description d'une information
         *
         * Retourne la description d'une information contenu dans
         * la liste.
         *
         * @return description de la n-ième information de l'objet
         */
    std::string getDescription(int n);

    /**
         * @brief Accès au nombre d'information
         *
         * Retourne le nombre d'information contenu dans la liste.
         *
         * @return la longueur de la liste d'information
         */
    int getSize();


private:
    MiList <Pair_t<std::string, std::string> > _informations;

};

#endif // INFORMATION_H
