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

time_t Mesure::GetTimestamp() {
    return Timestamp;
}

float Mesure::GetValeur() {
    return Valeur;
}

string Mesure::GetCapteur() {
    return Capteur;
}

void Mesure::SetTimestamp( time_t timestamp ) {
    Timestamp = timestamp;
}

void Mesure::SetValeur( float valeur ) {
    Valeur = valeur;
}

void Mesure::SetCapteur( string capteur ) {
    Capteur = capteur;
}

void Mesure::Afficher() const // Parcours de la liste avec un curseur et appel de la méthode Affichage pour chaque objet Trajet
{
    cout << "Date : " << Timestamp << " - Valeur : " << Valeur;
}

//-------------------------------------------- Constructeurs - destructeur

Mesure::Mesure ( std::time_t timestamp, float valeur, string capteur )
{
#ifdef MAP
    cout << "Appel au constructeur de <Mesure>" << endl;
#endif
Timestamp = timestamp;
Valeur = valeur;
Capteur = capteur;
}


Mesure::~Mesure ( )
{
#ifdef MAP
    cout << "Appel au destructeur de <Mesure>" << endl;
#endif
}


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées




