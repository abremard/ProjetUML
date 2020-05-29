//---------- Réalisation de la classe <Utilisateur> (fichier Utilisateur.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Utilisateur.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//------------------------------------------------------- Getter - setters
void Utilisateur::SetMotDePasse(string motDePasse) {
motDePasse = motDePasse;
}
void Utilisateur::SetMail(string mail) {
mail = mail;
}
void Utilisateur::SetTelephone(string telephone) {
telephone = telephone;
}
string Utilisateur::GetTelephone() const {
return telephone;
}
string Utilisateur::GetMotDePasse() const {
return motDePasse;
}
string Utilisateur::GetMail() const {
return mail;
}

//----------------------------------------------------- Méthodes publiques

//------------------------------------------------- Surcharge d'opérateurs


//-------------------------------------------- Constructeurs - destructeur

Utilisateur::Utilisateur(string mail, string motDePasse, string telephone)
    :mail(mail) 
    ,motDePasse(motDePasse) 
    ,telephone(telephone) {
}

Utilisateur::Utilisateur(const Utilisateur & utilisateur)
    :mail(utilisateur.GetMail())
    ,telephone(utilisateur.GetTelephone())
    ,motDePasse(utilisateur.GetMotDePasse())
    {
}

Utilisateur::~Utilisateur () {}

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

//----------------------------- Autres définitions dépendantes de <Utilisateur>

