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
#include <string>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Ligne.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- M�thodes publiques

bool Ligne::estImage() const
// Algrorithme :
// Teste l'extension du fichier 
// Extensions consid�r�es : jpg, png, jpeg, gif, css, js
//	(extension .ico (icone) non consid�r�es comme image)
//	Si le fichier n'a pas d'extension, il n'est pas consid�r� comme image
{
    int position;
    position=url.find(".");
	if (position == url.npos) {
		return false;
	}

    string resultat = url.substr(position+1);
    if(resultat=="jpg" ||resultat=="png"||resultat=="jpeg"||resultat=="gif"||resultat=="css"||resultat=="js")
        return true;
    else
        return false;
} //----- Fin de estImage

int Ligne::getHeure() const
// Algorithme :
// Extrait l'heure (tronqu�e) du champs "date"
{
	//08/Sep/2012:11:43:51 +0200
    int start = date.find(":");
	string resultat = date.substr(start + 1);
	int end = resultat.find(":");
    resultat = resultat.substr(0, end);

    return std::stoi(resultat);
} //----- Fin de getHeure


//------------------------------------------------- Surcharge d'op�rateurs
//Ensemble& Ensemble::operator = (const Ensemble& unEnsemble)
// Algorithme :
//
//{
//} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur

Ligne::Ligne(string ad, string useLog, string autUse, string dat, 
	string stat, string tail, string refe, string req, string ur, 
	string htmlVer,string nav):
	adressIP( ad),userLogname( useLog),authenticatedUser( autUse),
	date( dat),status( stat),taille( tail), referer( refe), requette( req),
	url( ur), htmlVers( htmlVer), navigateur( nav)
// Algorithme :
// instantie chaque variable
{
#ifdef MAP
	cout << "Appel au constructeur de <Ligne>" << endl;
#endif

} //----- Fin de Ligne

Ligne::~Ligne()
// Algorithme :
{
#ifdef MAP
	cout << "Appel au destructeur de <Ligne>" << endl;
#endif
} //----- Fin de ~Ligne


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- M�thodes prot�g�es

