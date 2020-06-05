/*************************************************************************
Grandeur:
DESCRIPTIF : L'objet Grandeur contiendra l'ensemble des trajets simples ou composés.
Il sera instancié dans le main. L'utilisateur peut y ajouter autant de trajet qu'il veut.
Les trajets sont contenus dans une liste chainée de trajets (cf. struct listeTrajet dans Grandeur.h).

*************************************************************************/
using namespace std;
#include <ctime>
#include <string>

//---------- Interface de la classe <Grandeur> (fichier Grandeur.h) ----------------
#if ! defined ( Grandeur_H )
#define Grandeur_H

//--------------------------------------------------- Interfaces utilisées
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
//------------------------------------------------------------------------

class Grandeur
{
//----------------------------------------------------------------- PUBLIC

public:

//----------------------------------------------------- Méthodes publiques
    void Afficher() const;
    string GetIdentifiant(), GetDescription(), GetUnite();
    void SetIdentifiant( string identifiant ), SetDescription( string description ), SetUnite( string unite );
    inline Grandeur& operator =(const Grandeur& m) {
        Identifiant = m.Identifiant;
        Description = m.Description;
        Unite = m.Unite;
        return *this;
    }

//-------------------------------------------- Constructeurs - destructeur
    Grandeur ( string Identifiant = "", string Description = "", string Unite = "");
    ~Grandeur ( );

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
string Identifiant;
string Description;
string Unite;

friend class FluxLog; 
};

//-------------------------------- Autres définitions dépendantes de <Grandeur>

#endif // Grandeur_H

