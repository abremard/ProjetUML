//---------- Interface de la classe <Agence> (fichier Agence.h) ----------------
#ifndef AGENCE_H
#define AGENCE_H

//--------------------------------------------------- Interfaces utilisées
#include <iostream>
using namespace std;

#include "Utilisateur.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

class Agence : public Utilisateur
{
//----------------------------------------------------------------- PUBLIC
	
public:
//----------------------------------------------------- Méthodes publiques
	
//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
    Agence();
    virtual ~Agence();

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées
	
//----------------------------------------------------- Attributs protégés

};

//----------------------- Autres définitions dépendantes de <Agence>

#endif // AGENCE_H