/*************************************************************************
						   FluxLog  -  Gère la lecture d'un fichier Log
							 -------------------
	début                : 17/01/2020
	copyright            : (C) 2020 par Antoine MANDIN - Iyad TOUT
	e-mail               : antoine.mandin@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <FluxLog> (fichier FluxLog.h) ----------------
#if ! defined ( FLUX_LOG_H )
#define FLUX_LOG_H

//--------------------------------------------------- Interfaces utilisées
#include <iostream>
#include <fstream>
using namespace std;

#include "Ligne.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <FluxLog>
// Lit ligne par ligne le contenu d'un fichier .log
// Utilise la classe Ligne pour stocker (et retourner) ces informations
//------------------------------------------------------------------------

class FluxLog
{
	//----------------------------------------------------------------- PUBLIC

public:
	//----------------------------------------------------- Méthodes publiques
	
		Ligne& lire(Ligne & ligne);
		// Mode d'emploi :
		//	Retourne un objet Ligne avec les informations contenues dans la 
		//	ligne courant du fichier log ouvert
		// Contrat :
		//	le stream doit être correct (good)
		//  La ligne ne doit pas être null

		bool eof();
		// Mode d'emploi :
		//	Retourne si l'on a atteind la fin du fichier


//-------------------------------------------- Constructeurs - destructeur
	
	FluxLog(const string filename);
	// Mode d'emploi :
	//	ouvre le fichier [filename] en lecutre
	// Contrat :
	//	le fichier doit exister et être lisible
	//  Autrement une erreur est affichée sur stderr

	virtual ~FluxLog();
	// Mode d'emploi :
	//	libère les espaces mémoires alloués

//------------------------------------------------------------------ PRIVE

protected:
	//----------------------------------------------------- Méthodes protégées

	//----------------------------------------------------- Attributs protégés
	ifstream* stream;
};

//-------------------------------- Autres définitions dépendantes de <FluxLog>

#endif // FLUX_LOG_H


