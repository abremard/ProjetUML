//---------- Interface de la classe <CoherenceMesure> (fichier CoherenceMesure.h) ----------------
#ifndef COHERENCEMESURE_H
#define COHERENCEMESURE_H

//--------------------------------------------------- Interfaces utilisées
#include <iostream>
#include <list>
using namespace std;

//------------------------------------------------------ Include personnel
#include "../Mesure/Mesure.h"

class CoherenceMesure
{
public:

    //----------------------------------------------------- Méthodes publiques
    
        float moyenneMesures(const list<Mesure> & mesuresList);

        float eTypeMesures(const list<Mesure> & mesuresList,const float moyenne);

        //revoie 1 si mesure est cohérente par rapport à l'échantillon témoin (test de Chevaunet)
        bool testMesureAcceptable(const list<Mesure> & mesuresTemoinList,const Mesure & mesure);
        
        //liste des mesures innacceptables detectées par le test de chevaunet
        list <Mesure> listeMesuresInnacceptables(const list<Mesure> & mesuresSuspectesList , list<Mesure> & mesuresTemoinList);

        //renvoie les valeurs de la liste suspectes inferieurs ou superieurs à 95 % des valeurs de la list témoin
        list <Mesure> listeMesuresCritiques (const list<Mesure> & mesuresSuspectesList , list<Mesure> & mesuresTemoinList); 
    //-------------------------------------------- Constructeurs - destructeur
    
        CoherenceMesure(){};

        virtual ~CoherenceMesure(){};

protected:
    //----------------------------------------------------- Méthodes privees
        bool calculTestChauvenet(const Mesure & mesureSuspecte,const int nbMesureTemoin,const float moyenneTemoin,const float ecartTyeTemoin);
        
        //trie la liste puis retourne par passage de parametre les premieres valeurs inférieurs et superieurs à 95% des valeurs  
        void bornesCinqPourcents(list <Mesure> mesuresList, float & bInf, float & bSup); 

};

#endif // COHERENCEMESURE_H
