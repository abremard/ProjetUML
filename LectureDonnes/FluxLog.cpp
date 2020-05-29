/*************************************************************************
						   FluxLog  -  Gère la lecture d'un fichier Log
							 -------------------
	début                : 17/01/2020
	copyright            : (C) 2020 par Antoine MANDIN - Iyad TOUT
	e-mail               : antoine.mandin@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la classe <FluxLog> (fichier FluxLog.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <fstream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "FluxLog.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

Ligne& FluxLog::lire(Ligne& ligne)
// Algorithme : 
// Lit information par information le contenue d'une ligne d'un fichier 
// log (ouvert avec stream)
{
	string adresseIP;
	string userLogname;
	string authenticatedUser;
	string date;
	string htmlType;	//GET , POST 
	string url;			//document
	string htmlVersion;	//HTTP/1.1
	string statut;
	string taille;
	string referer;
	string navigateur;

	getline(*stream, adresseIP, ' ');
	getline(*stream, userLogname, ' ');
	getline(*stream, authenticatedUser, ' ');
	stream->ignore(1);//[
	getline(*stream, date, ']');
	stream->ignore(2);// "
	getline(*stream, htmlType, ' ');
	getline(*stream, url, ' ');
	getline(*stream, htmlVersion, '"');
	stream->ignore(1);//"
	getline(*stream, statut, ' ');
	getline(*stream, taille, ' ');
	stream->ignore(1);//"
	getline(*stream, referer, '"');
	stream->ignore(2);// "
	getline(*stream, navigateur, '"');

	//Passe à la ligne suivante, si le fichier n'est pas fini
	if (!eof())
		stream->ignore(999, '\n');

	// remplit les valeurs de la ligne en paramètre
	ligne.adressIP = adresseIP;
	ligne.userLogname = userLogname;
	ligne.date = date;
	ligne.requette = htmlType;
	ligne.url = url;
	ligne.htmlVers = htmlVersion;
	ligne.status = statut;
	ligne.taille = taille;
	ligne.referer = referer;
	ligne.navigateur = navigateur;

	return ligne;
} //----- Fin de lire

bool FluxLog::eof()
// Algorithme : 
// utilise la fonction eof() de l'objet istream
{
	return stream->eof() || !stream->good();
} //----- Fin de eof



//------------------------------------------------- Surcharge d'opérateurs
//Ensemble& Ensemble::operator = (const Ensemble& unEnsemble)
// Algorithme :
//
//{
//} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur

FluxLog::FluxLog(const string filename)
// Algorithme :
// instantie l'objet (istream*) stream
// Génère une erreur si le fichier est illisible (inexistant par exemple)
{
#ifdef MAP
	cout << "Appel au constructeur de <FluxLog>" << endl;
#endif
	stream = new ifstream(filename.c_str());

	if (!stream->good()) {
		//Erreur 
		cerr << "(Error) : the ifstream object opened with the name '" + filename + "' is not good. (may not exist)" <<endl;
	}

} //----- Fin de FluxLog

FluxLog::~FluxLog()
// Algorithme :
// libère l'espace mémoire lié à l'objet stream
{
#ifdef MAP
	cout << "Appel au destructeur de <FluxLog>" << endl;
#endif
	delete stream;
} //----- Fin de ~FluxLog


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

