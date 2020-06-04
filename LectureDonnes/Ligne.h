/*************************************************************************
						   Ligne  -  Repr�sentation d'une ligne contenue
								dans un fichier .log
							 -------------------
	d�but                : 17/01/2020
	copyright            : (C) 2020 par Antoine MANDIN - Iyad TOUT
	e-mail               : antoine.mandin@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <Ligne> (fichier Ligne.h) ----------------
#if ! defined ( LIGNE_H )
#define LIGNE_H

//--------------------------------------------------- Interfaces utilis�es
#include <string>
#include <iostream>
using namespace std;

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// R�le de la classe <Ligne>
//
//
//------------------------------------------------------------------------

class Ligne
{
	//----------------------------------------------------------------- PUBLIC
friend class FluxLog;
friend class Stockage;

public:
	//----------------------------------------------------- M�thodes publiques
		// type M�thode ( liste des param�tres );
		// Mode d'emploi :
		//
		// Contrat :
		//


	//------------------------------------------------- Surcharge d'op�rateurs

	bool estImage() const;
	// Mode d'emploi :
	// Contrat :
	//	Retourne si le document atteint est une image, un css ou un js

	int getHeure() const;
	// Mode d'emploi :
	// Contrat :
	//	Retourne l'heure (tronqu�e) d'occurence de la ligne

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
	//----------------------------------------------------- M�thodes prot�g�es

	//----------------------------------------------------- Attributs prot�g�s
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

//-------------------------------- Autres d�finitions d�pendantes de <Ligne>

#endif // LIGNE_H

