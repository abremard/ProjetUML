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
#include <stdlib.h>
#include <time.h>
using namespace std;


#include "../Mesure/Mesure.h"

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
	
		Mesure& lireDonneesMesure(Mesure & mesure, Capteur tabCapteur[], Grandeur tabGrandeur[],int tailleTabCapteur,int tailleTabGrandeur);
		bool eof();
		Capteur& lireDonneesCapteur(Capteur& capteur);
		Grandeur& lireDonneesGrandeur(Grandeur& grandeur);
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


