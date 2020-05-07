/*************************************************************************
Mesure:
DESCRIPTIF : L'objet Mesure contiendra l'ensemble des trajets simples ou composés.
Il sera instancié dans le main. L'utilisateur peut y ajouter autant de trajet qu'il veut.
Les trajets sont contenus dans une liste chainée de trajets (cf. struct listeTrajet dans Mesure.h).

*************************************************************************/

//----- Réalisation de la classe <Mesure> (fichier Mesure.cpp) -----

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "Mesure.h"
//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

void Mesure::Afficher() const // Parcours de la liste avec un curseur et appel de la méthode Affichage pour chaque objet Trajet
{
    cout << "Date : " << Timestamp << " - Valeur : " << Valeur;
}

//-------------------------------------------- Constructeurs - destructeur

Mesure::Mesure ( std::time_t Timestamp, float Valeur, string Capteur )
{
#ifdef MAP
    cout << "Appel au constructeur de <Mesure>" << endl;
#endif
Timestamp = Timestamp;
Valeur = Valeur;
Capteur = Capteur;
}


Mesure::~Mesure ( )
{
#ifdef MAP
    cout << "Appel au destructeur de <Mesure>" << endl;
#endif
}


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées




