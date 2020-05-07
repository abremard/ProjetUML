/*************************************************************************
Mesure:
DESCRIPTIF : L'objet Mesure contiendra l'ensemble des trajets simples ou composés.
Il sera instancié dans le main. L'utilisateur peut y ajouter autant de trajet qu'il veut.
Les trajets sont contenus dans une liste chainée de trajets (cf. struct listeTrajet dans Mesure.h).

*************************************************************************/
using namespace std;
#include <ctime>
#include <string>

//---------- Interface de la classe <Mesure> (fichier Mesure.h) ----------------
#if ! defined ( Mesure_H )
#define Mesure_H
//--------------------------------------------------- Interfaces utilisées
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
//------------------------------------------------------------------------

class Mesure
{
//----------------------------------------------------------------- PUBLIC

public:

//----------------------------------------------------- Méthodes publiques
    void Afficher() const;

//-------------------------------------------- Constructeurs - destructeur
    Mesure ( std::time_t Timestamp, float Valeur, string Capteur );
    ~Mesure ( );

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
time_t Timestamp;
float Valeur;
string Capteur;
};

//-------------------------------- Autres définitions dépendantes de <Mesure>

#endif // Mesure_H

