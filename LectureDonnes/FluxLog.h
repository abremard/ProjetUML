/*************************************************************************
						   FluxLog  -  G�re la lecture d'un fichier Log
							 -------------------
	d�but                : 17/01/2020
	copyright            : (C) 2020 par Antoine MANDIN - Iyad TOUT
	e-mail               : antoine.mandin@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <FluxLog> (fichier FluxLog.h) ----------------
#if ! defined ( FLUX_LOG_H )
#define FLUX_LOG_H

//--------------------------------------------------- Interfaces utilis�es
#include <iostream>
#include <fstream>
using namespace std;

#include "Ligne.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// R�le de la classe <FluxLog>
// Lit ligne par ligne le contenu d'un fichier .log
// Utilise la classe Ligne pour stocker (et retourner) ces informations
//------------------------------------------------------------------------

class FluxLog
{
	//----------------------------------------------------------------- PUBLIC

public:
	//----------------------------------------------------- M�thodes publiques
	
		Ligne& lire(Ligne & ligne);
		// Mode d'emploi :
		//	Retourne un objet Ligne avec les informations contenues dans la 
		//	ligne courant du fichier log ouvert
		// Contrat :
		//	le stream doit �tre correct (good)
		//  La ligne ne doit pas �tre null

		bool eof();
		// Mode d'emploi :
		//	Retourne si l'on a atteind la fin du fichier


//-------------------------------------------- Constructeurs - destructeur
	
	FluxLog(const string filename);
	// Mode d'emploi :
	//	ouvre le fichier [filename] en lecutre
	// Contrat :
	//	le fichier doit exister et �tre lisible
	//  Autrement une erreur est affich�e sur stderr

	virtual ~FluxLog();
	// Mode d'emploi :
	//	lib�re les espaces m�moires allou�s

//------------------------------------------------------------------ PRIVE

protected:
	//----------------------------------------------------- M�thodes prot�g�es

	//----------------------------------------------------- Attributs prot�g�s
	ifstream* stream;
};

//-------------------------------- Autres d�finitions d�pendantes de <FluxLog>

#endif // FLUX_LOG_H


