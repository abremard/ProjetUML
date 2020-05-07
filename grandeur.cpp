/*************************************************************************
Grandeur:
DESCRIPTIF : L'objet Grandeur contiendra l'ensemble des trajets simples ou composés.
Il sera instancié dans le main. L'utilisateur peut y ajouter autant de trajet qu'il veut.
Les trajets sont contenus dans une liste chainée de trajets (cf. struct listeTrajet dans Grandeur.h).

*************************************************************************/

//----- Réalisation de la classe <Grandeur> (fichier Grandeur.cpp) -----

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "Grandeur.h"
//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

void Grandeur::Afficher() const // Parcours de la liste avec un curseur et appel de la méthode Affichage pour chaque objet Trajet
{
    cout << "Identifiant : " << Identifiant << " - Description : " << Description << " - Unité de mesure : " << Unite;
}

//-------------------------------------------- Constructeurs - destructeur

Grandeur::Grandeur ( string Identifiant, string Description, string Unite )
{
#ifdef MAP
    cout << "Appel au constructeur de <Grandeur>" << endl;
#endif
Identifiant = Identifiant;
Description = Description;
Unite = Unite;
}


Grandeur::~Grandeur ( )
{
#ifdef MAP
    cout << "Appel au destructeur de <Grandeur>" << endl;
#endif
}


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées




