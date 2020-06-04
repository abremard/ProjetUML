/*************************************************************************
						   AirCleaner  -  Représentation d'un air cleaner
							 -------------------
	début                : 07/05/2020
	copyright            : (C) 2020 par Iyad TOUT
	e-mail               : iyad.tout@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la classe <AirCleaner> (fichier AirCleaner.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
//------------------------------------------------------ Include personnel
#include "AirCleaner.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

string AirCleaner::getLatitude() const
{
    return this->latitude;
}

void AirCleaner::setLatitude(string latitude)
{
    this->latitude = latitude;
}

string AirCleaner::getLongitude() const
{
    return this->longitude;
}

void AirCleaner::setLongitude(string longitude)
{
    this->longitude = longitude;
}

string AirCleaner::getIdentifiant() const
{
    return this->identifiant;
}

void AirCleaner::setIdentifiant(string identifiant)
{
    this->identifiant = identifiant;
}

string AirCleaner::getModele() const
{
    return this->modele;
}

void AirCleaner::setModele(string modele)
{
    this->modele = modele;
}

time_t AirCleaner::getDateMiseEnService() const
{
    return this->dateMiseEnService;
}

void AirCleaner::setDateMiseEnService(time_t dateMiseEnService)
{
    this->dateMiseEnService = dateMiseEnService;
}

string AirCleaner::getNumeroDeSerie() const
{
    return this->numeroDeSerie;
}

void AirCleaner::setNumeroDeSerie(string numeroDeSerie)
{
    this->numeroDeSerie = numeroDeSerie;
}

string AirCleaner::getEtat() const
{
    return this->etat;
}

void AirCleaner::setEtat(string etat)
{
    this->etat = etat;
}

list<pair<time_t, double>> AirCleaner::getHistoriqueAcitivte() const
{
    return this->historiqueAcitivte;
}

void AirCleaner::setHistoriqueAcitivte(list<pair<time_t, double>> historiqueAcitivte)
{
    this->historiqueAcitivte = historiqueAcitivte;
}
//------------------------------------------------- Surcharge d'opérateurs
//Ensemble& Ensemble::operator = (const Ensemble& unEnsemble)
// Algorithme :
//
//{
//} //----- Fin de operator =

//-------------------------------------------- Constructeurs - destructeur

AirCleaner::AirCleaner(string latitude, string longitude, string identifiant, string modele, string numeroDeSerie, string etat, time_t dateMiseEnService)
{
this->latitude=latitude;
this->longitude=longitude;
this->identifiant=identifiant;
this->modele=modele;
this->numeroDeSerie=numeroDeSerie;
this->etat=etat;
this->dateMiseEnService=dateMiseEnService;
}

AirCleaner::~AirCleaner()
// Algorithme :
// libère l'espace mémoire lié à l'objet stream
{
#ifdef MAP
    cout << "Appel au destructeur de <AirCleaner>" << endl;
#endif
}

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
