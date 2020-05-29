/*************************************************************************
						   AirCleaner  -  Représentation d'un air cleaner
							 -------------------
	début                : 07/05/2020
	copyright            : (C) 2020 par Iyad TOUT
	e-mail               : iyad.tout@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <AirCleaner> (fichier AirCleaner.h) ----------------
#if !defined(AIRCLEANER_H)
#define AIRCLEANER_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
#include<list>
#include<utility>
#include <ctime>
using namespace std;

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <AirCleaner>
//
//
//------------------------------------------------------------------------

class AirCleaner
{
    //----------------------------------------------------------------- PUBLIC
    // si besoin friend class XXX;

public:
    //----------------------------------------------------- Méthodes publiques
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //

    //------------------------------------------------- Surcharge d'opérateurs

    string getLatitude() const;
    
    void setLatitude(string latitude);

    string getLongitude() const;

    void setLongitude(string longitude);

    string getIdentifiant() const;
 
    void setIdentifiant(string identifiant);

    string getModele() const;

    void setModele(string modele);

    time_t getDateMiseEnService() const;

    void setDateMiseEnService(time_t dateMiseEnService);

    string getNumeroDeSerie() const;

    void setNumeroDeSerie(string numeroDeSerie);

    string getEtat() const;

    void setEtat(string etat);

    list <pair<time_t,double>> getHistoriqueAcitivte() const;

    void setHistoriqueAcitivte(list <pair<time_t,double>> historiqueAcitivte);
    //-------------------------------------------- Constructeurs - destructeur
    AirCleaner(string latitude, string longitude, string identifiant, string modele, string numeroDeSerie, string etat, time_t dateMiseEnService);
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~AirCleaner();
    // Mode d'emploi :
    //
    // Contrat :
    //

    //------------------------------------------------------------------ PRIVE

protected:
    //----------------------------------------------------- Méthodes protégées

    //----------------------------------------------------- Attributs protégés
    string latitude;
    string longitude;
    string identifiant;
    string modele;
    string numeroDeSerie;
    string etat;
    time_t dateMiseEnService;
    list <pair<time_t,double>> historiqueAcitivte;
};

//-------------------------------- Autres définitions dépendantes de <AirCleaner>

#endif // AIR_CLEANER
