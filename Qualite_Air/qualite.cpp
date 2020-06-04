using namespace std;
#include <iostream>

#include "qualite.h"
#include "math.h"


resultat qualiteMoyenne(const GeoMap geomap, const Coordonnees centre, const float rayon, const std::time_t dateDebut, const std::time_t dateFin) {

    list<Mesure> listeMesure = geomap.get(centre, rayon, dateDebut, dateFin);

    // Moyenne pour chaque concentration
    float moyO3, moyNO2, moySO2, moyPM10;
    moyO3 = moyNO2 = moySO2 = moyPM10 = 0.0;
    // Ecart-Type pour chaque concentration
    float etO3, etNO2, etSO2, etPM10;
    etO3 = etNO2 = etSO2 = etPM10 = 0.0;
    // Minimum pour chaque concentration
    float minO3, minNO2, minSO2, minPM10;
    minO3 = minNO2 = minSO2 = minPM10 = 999999.9;
    // Maximum pour chaque concentration
    float maxO3, maxNO2, maxSO2, maxPM10;
    maxO3 = maxNO2 = maxSO2 = maxPM10 = 0.0;
    // Nombre de mesures pour chaque concentration
    int nbO3, nbNO2, nbSO2, nbPM10;
    nbO3 = nbNO2 = nbSO2 = nbPM10 = 0;

    std::list<Mesure>::iterator it;

    // Première boucle de calcul de moyenne, min et max
    for (it = listeMesure.begin(); it != listeMesure.end(); ++it)
    {
        Mesure mesure = *it;
  
        float valeur = mesure.GetValeur(); // Valeur de mesure
        string grandeur = mesure.GetGrandeur().GetIdentifiant();

        if (!grandeur.compare("O3")){
            moyO3 = moyO3 + valeur;
            if (valeur > maxO3)
                maxO3 = valeur;
            if (valeur < minO3)
                minO3 = valeur;
            nbO3++;
        }
        else if (!grandeur.compare("NO2")) {
            moyNO2 = moyNO2 + valeur;
            if (valeur > maxNO2)
                maxNO2 = valeur;
            if (valeur < minNO2)
                minNO2 = valeur;                
            nbNO2++;
        }
        else if (!grandeur.compare("SO2")) {
            moySO2 = moySO2 + valeur;
            if (valeur > maxSO2)
                maxSO2 = valeur;
            if (valeur < minSO2)
                minSO2 = valeur;
            nbSO2++;
        }
        else if (!grandeur.compare("PM10"))
        {
            moyPM10 = moyPM10 + valeur;
            if (valeur > maxPM10)
                maxPM10 = valeur;
            if (valeur < minPM10)
                minPM10 = valeur;
            nbPM10++;
        }
    }

    moyO3 = moyO3/nbO3;
    moyNO2 = moyNO2/nbNO2;
    moySO2 = moySO2/nbSO2;
    moyPM10 = moyPM10/nbPM10;

    // Deuxième boucle de calcul d'écart-type
    for (it = listeMesure.begin(); it != listeMesure.end(); ++it)
    {
        Mesure mesure = *it;

        float valeur = mesure.GetValeur(); // Valeur de mesure
        string grandeur = mesure.GetGrandeur().GetIdentifiant();
        if (!grandeur.compare("O3"))
            etO3 = etO3 + (valeur - moyO3)*(valeur - moyO3);
        else if (!grandeur.compare("NO2"))
            etNO2 = etNO2 + (valeur - moyNO2)*(valeur - moyNO2);              
        else if (!grandeur.compare("SO2"))
            etSO2 = etSO2 + (valeur - moySO2)*(valeur - moySO2);
        else if (!grandeur.compare("PM10"))
            etPM10 = etPM10 + (valeur - moyPM10)*(valeur - moyPM10); 
    }

    etO3 = sqrt(etO3/nbO3);
    etNO2 = sqrt(etNO2/nbNO2);
    etSO2 = sqrt(etSO2/nbSO2);
    etPM10 = sqrt(etPM10/nbPM10);

    resultat res;

    // Transcrire les moyennes
    res.O3.moy = moyO3;
    res.NO2.moy = moyNO2;
    res.SO2.moy = moySO2;
    res.PM10.moy = moyPM10;

    // Transcrire les ecarts-type
    res.O3.ET = etO3;
    res.NO2.ET = etNO2;
    res.SO2.ET = etSO2;
    res.PM10.ET = etPM10;

    // Transcrire les mins
    res.O3.min = minO3;
    res.NO2.min = minNO2;
    res.SO2.min = minSO2;
    res.PM10.min = minPM10;

    // Transcrire les maxs
    res.O3.max = maxO3;
    res.NO2.max = maxNO2;
    res.SO2.max = maxSO2;
    res.PM10.max = maxPM10;

    return res;
}





