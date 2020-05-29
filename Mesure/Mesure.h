/*************************************************************************
Mesure:
DESCRIPTIF : L'objet Mesure contiendra l'ensemble des trajets simples ou composés.
Il sera instancié dans le main. L'utilisateur peut y ajouter autant de trajet qu'il veut.
Les trajets sont contenus dans une liste chainée de trajets (cf. struct listeTrajet dans Mesure.h).

*************************************************************************/
using namespace std;
#include <ctime>
#include <string>
#include "../Capteur/Capteur.h"

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
    time_t GetTimestamp() const;
    float GetValeur() const;
    Capteur GetCapteur() const;
    void SetTimestamp(time_t timestamp);
    void SetValeur(float valeur);
    void SetCapteur(Capteur capteur);
    inline bool operator <(const Mesure& coord) const {
        return	Timestamp < coord.Timestamp;
    }

//-------------------------------------------- Constructeurs - destructeur
    Mesure ( std::time_t Timestamp, float Valeur, Capteur capteur );
    ~Mesure ( );

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
time_t Timestamp;
float Valeur;
Capteur capteur;
};

//-------------------------------- Autres définitions dépendantes de <Mesure>

#endif // Mesure_H
