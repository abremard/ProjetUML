/*************************************************************************
Qualite:
DESCRIPTIF : L'objet Qualite contiendra l'ensemble des trajets simples ou composés.
Il sera instancié dans le main. L'utilisateur peut y ajouter autant de trajet qu'il veut.
Les trajets sont contenus dans une liste chainée de trajets (cf. struct listeTrajet dans Qualite.h).

*************************************************************************/
using namespace std;
#include <ctime>
#include <string>
#include "../Coordonnees/Coordonnees.h"
#include "../GeoMap/GeoMap.h"

//---------- Interface de la classe <Qualite> (fichier Qualite.h) ----------------
#if ! defined ( Qualite_H )
#define Qualite_H

// Paramètre d'analyse
typedef struct synthese
{
    float moy;
    float min;
    float max;
    float ET;
} synthese;

// Resultat d'analyse
typedef struct resultat
{
    synthese O3;
    synthese NO2;
    synthese SO2;
    synthese PM10;
} resultat;


// Fonction de synthèse la qualité d'air
resultat qualiteMoyenne(const GeoMap geomap, const Coordonnees centre, const float rayon, const std::time_t dateDebut, const std::time_t dateFin);


#endif // Qualite_H

