//---------- Interface de la classe <Utilisateur> (fichier Utilisateur.h) ----------------
#ifndef UTILISATEUR_H
#define UTILISATEUR_H

//--------------------------------------------------- Interfaces utilisées
#include <iostream>
using namespace std;


//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

class Trajet
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

    
//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
    utilisateur();
    virtual ~utilisateur();

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    Sring mail; 
    Sring motDePasse;
    String Telephone;
};

//----------------------------- Autres définitions dépendantes de <Utilisateur>


#endif // UTILISATEUR_H
