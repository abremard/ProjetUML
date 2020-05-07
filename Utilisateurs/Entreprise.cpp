//---------- Réalisation de la classe <Entreprise> (fichier Entreprise.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Utilisateur.h"
#include "Entreprise.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//------------------------------------------------------- Getter - setters
int Entreprise::GetNumSIRET() const {
return numSIRET;
}

void Entreprise::SetNumSIRET(int numSIRET) {
numSIRET = numSIRET;
}

//----------------------------------------------------- Méthodes publiques
Entreprise::Entreprise(string mail, string motDePasse, string telephone, int numSIRET)
    :Utilisateur(mail,motDePasse,telephone)
    ,numSIRET(numSIRET){
}

Entreprise:: ~Entreprise() {}

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

//----------------------- Autres définitions dépendantes de <Entreprise>