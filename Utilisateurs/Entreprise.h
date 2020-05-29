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
//---------------------------------------------------------------- Getters
    int GetNumSIRET() const;

//---------------------------------------------------------------- Setters
    void SetNumSIRET(int numSIRET);

//----------------------------------------------------- Méthodes publiques
	
//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
    Entreprise(string mail = "mail par defaut entreprise", string motDePasse = "mdpEntreprise", string telephone = " ", int numSIRET = 1);
    
    virtual ~Entreprise();

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées
	
//----------------------------------------------------- Attributs protégés
     int numSIRET;
  

};

//----------------------- Autres définitions dépendantes de <UtilisateurPrive>

#endif // ENTREPRISE_H