//---------- Interface de la classe <Utilisateur> (fichier Utilisateur.h) ----------------
#ifndef UTILISATEUR_H
#define UTILISATEUR_H

//--------------------------------------------------- Interfaces utilisées
#include <iostream>
#include <string.h>
using namespace std;

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

class Utilisateur
{
    //----------------------------------------------------------------- PUBLIC

public:


    //---------------------------------------------------------------- Getters
    string GetTelephone() const;

    string GetMail() const;

    string GetMotDePasse() const;

    //---------------------------------------------------------------- Setters
    void SetTelephone(string telephone);

    void SetMotDePasse(string motDePasse);

    void SetMail(string mail);

    //----------------------------------------------------- Méthodes publiques

    //------------------------------------------------- Surcharge d'opérateurs

    //-------------------------------------------- Constructeurs - destructeur

    Utilisateur(string mail = "mail par défaut", string motDePasse = "mdp par défaut", string telephone = " ");

    Utilisateur(const Utilisateur & utilisateur);

    virtual ~Utilisateur();

    //------------------------------------------------------------------ PRIVE

protected:
    //----------------------------------------------------- Méthodes protégées

    //----------------------------------------------------- Attributs protégés
    string motDePasse;
    string telephone;
    string mail;
};

//----------------------------- Autres définitions dépendantes de <Utilisateur>

#endif // UTILISATEUR_H
