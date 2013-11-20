ENGLISH
-------

To compile the project under QtCreator :
Open the two projects (lib-core and appli). Go to the "Project" tab.
For "lib-core", add a third compilation step of type "make" with the parameter "install"
For "appli", go to the Dependencies tab and check "lib-core".

Please think to add a path to a dicom directory in argument of appli. 

Fix the QtCreator bugs under linux : 
Goto Tools -> Options -> environnement -> Terminal
Set command : "xterm -e"

Debug the project : Goto the "appli" project configuration and uncheck "Run in a terminal".
Now you can debug the project.

Trick : To speed up the compilation process, you should add "-j8" in parameter of the make step of the two projects.




FRANCAIS
--------

Pour compiler le projet sous qtCreator :
Ouvrir les deux projets (actuellement la lib s'appelle projet_cp_initial et l'exécutable lib_test). Aller dans l'onglet "Projet".

    Pour la lib (projet_cp_initial), ajouter une troisième étape de type "make" avec le paramêtre "install".
    Pour l'exécutable (lib_test), aller dans l'onglet dependencies et ajouter la lib (projet_cp_initial)
    Exécuter correctement dans Qt : Sous linux, il faut suivre ce qui est indiqué à la page : http://www.developpez.net/forums/d1249618/c-cpp/c/debuter/probleme-daffichage-console-qt-creator-sous-linux/
    Pensez à rajouter un chemin vers un fichier DICOM en paramêtre. 

Astuce : pour accélérer la compilation, vous pouvez ajouter "-j8" en paramêtre des étapes make des deux projets.


QtCreator et gdb

En fait, c'est pas compliqué, il suffit d'ouvrir le projet lib_test, puis d'aller dans les options du projet et de décocher l'option "Exécuter dans un terminal". Un fois fait ça, la sortie du programme s'affiche dans Qt et non dans une fenêtre à part, et le débuggueur fonctionne.



