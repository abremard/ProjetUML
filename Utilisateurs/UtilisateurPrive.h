//---------- Interface de la classe <UtilisateurPrive> (fichier UtilisateurPrive.h) ----------------
#ifndef UTILISATEURPRIVE_H
#define UTILISATEURPRIVE_H

//--------------------------------------------------- Interfaces utilisées
#include <iostream>
using namespace std;

#include "Utilisateur.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

class UtilisateurPrive : public Utilisateur
{
//----------------------------------------------------------------- PUBLIC
	
public:
//----------------------------------------------------- Méthodes publiques
	
//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
    UtilisateurPrive();
    virtual ~UtilisateurPrive();

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées
	
//----------------------------------------------------- Attributs protégés
	string nom;
    string prenom;
    string score;

};

//----------------------- Autres définitions dépendantes de <UtilisateurPrive>

#endif // UTILISATEURPRIVE_H