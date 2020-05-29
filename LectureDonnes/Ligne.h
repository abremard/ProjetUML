/*************************************************************************
						   Ligne  -  Représentation d'une ligne contenue
								dans un fichier .log
							 -------------------
	début                : 17/01/2020
	copyright            : (C) 2020 par Antoine MANDIN - Iyad TOUT
	e-mail               : antoine.mandin@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <Ligne> (fichier Ligne.h) ----------------
#if ! defined ( LIGNE_H )
#define LIGNE_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
using namespace std;

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Ligne>
//
//
//------------------------------------------------------------------------

class Ligne
{
	//----------------------------------------------------------------- PUBLIC
friend class FluxLog;
friend class Stockage;

public:
	//----------------------------------------------------- Méthodes publiques
		// type Méthode ( liste des paramètres );
		// Mode d'emploi :
		//
		// Contrat :
		//


	//------------------------------------------------- Surcharge d'opérateurs

	bool estImage() const;
	// Mode d'emploi :
	// Contrat :
	//	Retourne si le document atteint est une image, un css ou un js

	int getHeure() const;
	// Mode d'emploi :
	// Contrat :
	//	Retourne l'heure (tronquée) d'occurence de la ligne

//-------------------------------------------- Constructeurs - destructeur
	Ligne(string ad="",string useLog="",string autUse="",string dat="",
		string stat="",string tail="",string refe="",string req="",
		string ur="",string htmlVer="",string nav="");
	// Mode d'emploi :
	//
	// Contrat :
	//

	virtual ~Ligne();
	// Mode d'emploi :
	//
	// Contrat :
	//

//------------------------------------------------------------------ PRIVE

protected:
	//----------------------------------------------------- Méthodes protégées

	//----------------------------------------------------- Attributs protégés
	string adressIP;
	string userLogname;
	string authenticatedUser;
	string date;
	string status;
	string taille;
	string referer;
	string requette;
	string url;
	string htmlVers;
	string navigateur;
};

//-------------------------------- Autres définitions dépendantes de <Ligne>

#endif // LIGNE_H

