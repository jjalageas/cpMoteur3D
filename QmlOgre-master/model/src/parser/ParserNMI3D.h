#ifndef PARSERNMI3D_H
#define PARSERNMI3D_H

#include <Parser.h>


class ParserNMi3D : public Parser
{
public:
    ParserNMi3D();


public:
    Examen* loadFile(std::string filename);

    /**
     * @brief Sauvegarde d'un examen
     *
     * Méthode permettant de sauvegarder toutes les données contenues
     * dans un examen (image, masque, informations, etc...).
     *
     * @param filename : nom du fichier  de sortie
     * @param examen : examen à enregistrer
     * @param options : tableau de booléens spécifiant les données à
     * enregistrer. Les correspondances entre options et données sont :
     * options[0] : image
     * options[1] : masque
     * options[2] : squelette
     * options[3] : informations
     *
     */
    bool saveFile(std::string filename, Examen* examen, MiList<bool> options);

};

#endif // PARSERNMI3D_H
