//---------- Interface de la classe <Entreprise> (fichier Entreprise.h) ----------------
#ifndef ENTREPRISE_H
#define ENTREPRISE_H

//--------------------------------------------------- Interfaces utilisées
#include <iostream>
using namespace std;

#include "Utilisateur.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

class Entreprise : public Utilisateur
{
//----------------------------------------------------------------- PUBLIC
	
public:
//----------------------------------------------------- Méthodes publiques
	
//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
    Entreprise();
    virtual ~Entreprise();

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées
	
//----------------------------------------------------- Attributs protégés
	unsigned int numSIRET;
  

};

//----------------------- Autres définitions dépendantes de <UtilisateurPrive>

#endif // ENTREPRISE_H