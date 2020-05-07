// ProjetGL.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "../Coordonnees/Coordonnees.h"
#include "../GeoMap/GeoMap.h"

using namespace std;

int main()
{
    Coordonnees paris(48.8534, 2.3488);
    Coordonnees lyon(45.75, 4.85);
    Coordonnees grenoble(45.166672, 5.71667);
    Coordonnees newyork(40.7808, -73.9772);

    cout << "Distance Paris-Lyon : " << lyon.distanceTo(paris) << endl;
    cout << "Distance Grenoble-Lyon : " << lyon.distanceTo(grenoble) << endl;
    cout << "Distance Paris-New York : " << Coordonnees::distance(paris, newyork) << endl;

    GeoMap<int> g;
    for (int i = -89; i <= 89; ++i)
    {
        g.insert(i, Coordonnees((double)i, (double)i));
        cout << "taille : " << g.size() << endl;
    }
}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
