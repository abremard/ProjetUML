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
#include <string>
//------------------------------------------------------ Include personnel
#include "Grandeur.h"
//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

void Grandeur::Afficher() const
{
    cout << "Identifiant : " << Identifiant << " - Description : " << Description << " - Unité de mesure : " << Unite << endl;
}

void Grandeur::SetIdentifiant( const string identifiant ) {
    Identifiant = identifiant;
}

void Grandeur::SetDescription( const string description ) {
    Description = description;
}

void Grandeur::SetUnite( const string unite ) {
    Unite = unite;
}

string Grandeur::GetIdentifiant() {
    cout << "Identifiant : " << Identifiant << endl;
    return Identifiant;
}

string Grandeur::GetDescription() {
    return Description;
}

string Grandeur::GetUnite() {
    return Unite;
}

//-------------------------------------------- Constructeurs - destructeur

Grandeur::Grandeur ( string identifiant, string description, string unite )
{
#ifdef MAP
    cout << "Appel au constructeur de <Grandeur>" << endl;
#endif
Identifiant = identifiant;
Description = description;
Unite = unite;
}


Grandeur::~Grandeur ( )
{
#ifdef MAP
    cout << "Appel au destructeur de <Grandeur>" << endl;
#endif
}


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées




