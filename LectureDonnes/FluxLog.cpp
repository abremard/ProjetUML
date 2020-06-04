/*************************************************************************
						   FluxLog  -  G�re la lecture d'un fichier Log
							 -------------------
	d�but                : 17/01/2020
	copyright            : (C) 2020 par Antoine MANDIN - Iyad TOUT
	e-mail               : antoine.mandin@insa-lyon.fr
*************************************************************************/

//---------- R�alisation de la classe <FluxLog> (fichier FluxLog.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include syst�me
#include <iostream>
#include <fstream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "FluxLog.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- M�thodes publiques
Mesure& FluxLog::lireDonneesMesure(Mesure& mesure, Capteur tabCapteur[], Grandeur tabGrandeur[], int tailleTabCapteur,int tailleTabGrandeur){
	time_t TimestampParsed;
	string TimestampNotParsed;
	float Valeur;
	string valeurNotParsed;
	string capteurNotParsed;
	string grandeurNotParsed;

	getline(*stream, TimestampNotParsed, ';');
	getline(*stream, capteurNotParsed, ';');
	getline(*stream, grandeurNotParsed, ';');
	getline(*stream, valeurNotParsed, ';');

	if (!eof())
		stream->ignore(999, '\n');
	
	mesure.SetValeur(stof(valeurNotParsed)); //set la valeur de la mesure
	for(int i=0;i<tailleTabCapteur;++i){	 //set le capteur de la mesure
		if(tabCapteur[i].getId()==capteurNotParsed)
			mesure.SetCapteur(tabCapteur[i]);
	}
	for(int i=0;i<tailleTabGrandeur;++i){	 //set la grandeur de la mesure
		if(tabGrandeur[i].GetIdentifiant()==grandeurNotParsed)
			mesure.SetGrandeur(tabGrandeur[i]);
	}
	struct tm tm;
	strptime(TimestampNotParsed,"%Y-%m-%d %H:%M:%S",&tm);
	TimestampParsed=mktime(&tm);
	return mesure;
}

Capteur& FluxLog::lireDonneesCapteur(Capteur& capteur){
	string longitudeNotParsed;
	string capteurNotParsed;
	string latitudeNotParsed;

	getline(*stream, capteurNotParsed, ';');
	getline(*stream, latitudeNotParsed, ';');
	getline(*stream, longitudeNotParsed, ';');

	if (!eof())
		stream->ignore(999, '\n');
	
	capteur.id=capteurNotParsed;
	capteur.coordonnees=Coordonnees(stof(longitudeNotParsed),stof(latitudeNotParsed));

	return capteur;
}

Grandeur& FluxLog::lireDonneesGrandeur(Grandeur& grandeur){
	string descripNotParsed;
	string grandeurNotParsed;
	string uniteNotParsed;
	
	getline(*stream, grandeurNotParsed, ';');
	getline(*stream, uniteNotParsed, ';');
	getline(*stream, descripNotParsed, ';');

	if (!eof())
		stream->ignore(999, '\n');
	
	grandeur.Identifiant=grandeurNotParsed;
	grandeur.Unite=uniteNotParsed;
	grandeur.Description=descripNotParsed;

	return grandeur;
}

bool FluxLog::eof()
// Algorithme : 
// utilise la fonction eof() de l'objet istream
{
	return stream->eof() || !stream->good();
} //----- Fin de eof


//------------------------------------------------- Surcharge d'op�rateurs
//Ensemble& Ensemble::operator = (const Ensemble& unEnsemble)
// Algorithme :
//
//{
//} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur

FluxLog::FluxLog(const string filename)
// Algorithme :
// instantie l'objet (istream*) stream
// G�n�re une erreur si le fichier est illisible (inexistant par exemple)
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
// lib�re l'espace m�moire li� � l'objet stream
{
#ifdef MAP
	cout << "Appel au destructeur de <FluxLog>" << endl;
#endif
	delete stream;
} //----- Fin de ~FluxLog


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- M�thodes prot�g�es

