//----- Réalisation de la classe <CoherenceMesure> (fichier CoherenceMesure.cpp) -----

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <algorithm>

//------------------------------------------------------ Include personnel
#include "CoherenceMesure.h"

//------------------------------------------------------------- Constantes
#define M_PI 3.14159265358979323846

//----------------------------------------------------- Fonction ordinaire
bool conditionTri(Mesure m1 , Mesure m2){
    return (m1.GetValeur() < m2.GetValeur());
} 

//----------------------------------------------------- Méthodes publiques
void CoherenceMesure::bornesCinqPourcents(list <Mesure> mesuresTemoinList, float & bInf, float & bSup){
    //trie la liste puis retourne par passage de parametre les valeurs inférieurs et superieurs à 95% des valeurs  
    
    int nbMesures = mesuresTemoinList.size();
    mesuresTemoinList.sort(conditionTri);//tri de la liste
    list <Mesure>::const_iterator it =  mesuresTemoinList.begin();

    //borne inferieur
    int kCinqPourcents = 5*nbMesures/100 ;
    for(int k=1 ; k < kCinqPourcents; k++) {++it;}         
    bInf = it->GetValeur();
    it++;  
    bInf+=it->GetValeur();
    bInf=bInf/((float)2);

    //borne superieur 
    it = mesuresTemoinList.end();
    for( int k = nbMesures ; k >  nbMesures-kCinqPourcents ; k--) {--it;}          
    bSup = it->GetValeur();
    it--; 
    bSup += it->GetValeur();
    bSup=bSup/((float)2);
} 

bool CoherenceMesure::calculTestChauvenet(const Mesure & mesureSuspecte,const int nbMesureTemoin,const float moyenneTemoin,const float ecartTyeTemoin){
//Test de Chevaunet
//le but est de déterminer pour une ValeurSuspecte si elle est abérante, conaissant la moyenne, la variance et la taille d'un echantillon temoin de données
    
    bool res = true;

    // si n * ercf(  |  valeurSuspecte - moyenne | / eType )  < 0.5  alors la valeur est abérante
    float na = nbMesureTemoin*erfc(abs(mesureSuspecte.GetValeur()-moyenneTemoin)/ecartTyeTemoin);  
    //cout<<"na: "<<na<<endl;
    if(na < 0.5){res = false;}
 
    return res;
}
float CoherenceMesure::moyenneMesures(const list<Mesure> & mesuresList){
//calcul de la moyenne d'une liste de mesures

    float moyenne = 0;
    list<Mesure>::const_iterator i;  
    for(i=mesuresList.begin() ; i != mesuresList.end(); ++i) 
    {
        moyenne += i -> GetValeur();
    }
    moyenne = moyenne / (float)(mesuresList.size());
    return moyenne;
}
float CoherenceMesure::eTypeMesures(const list<Mesure> & mesuresList,const float moyenne){
//calcul de l'ecart type d'une liste de mesures

    float eType = 0 ;
    list<Mesure>::const_iterator i;  
    for(i=mesuresList.begin() ; i != mesuresList.end(); ++i) 
    {  
      eType += (i->GetValeur() - moyenne) * (i->GetValeur() - moyenne );
    }

    eType=sqrt((eType)/(float)mesuresList.size()); 
    return eType;
}

bool CoherenceMesure::testMesureAcceptable(const list<Mesure> & mesuresTemoinList,const Mesure & mesure){
//pour une mesure, déterminer si elle est suspecte par rapport à un echantillon temoin

    float moyenne = moyenneMesures(mesuresTemoinList); 
    float eType =  eTypeMesures( mesuresTemoinList , moyenne); 
    int nbMesuresTemoin = mesuresTemoinList.size();
        
    if(!calculTestChauvenet(mesure, nbMesuresTemoin, moyenne, eType)){//Test de Chevaunet
        return false; 
    }

    return true;
} 

list<Mesure> CoherenceMesure::listeMesuresCritiques (const list<Mesure> & mesuresSuspectesList , list<Mesure> & mesuresTemoinList){
//pour un echantillon de valeurs suspectes, retourne la liste des valeurs critiques (inférieurs ou superieurs à 95% des valeurs témoins)

    //int nbCritiques = 0; 
    float bInf = 0;
    float bSup = 0;
    bornesCinqPourcents(mesuresTemoinList,bInf,bSup);
    list <Mesure> listeMesuresCritiques;
   
    list<Mesure>::const_iterator it;
    for(it = mesuresSuspectesList.begin() ; it!=mesuresSuspectesList.end() ; ++it){
        if(it -> GetValeur() <= bInf || it -> GetValeur() >= bSup){
            listeMesuresCritiques.push_back(*it); 
        }
    }

    return listeMesuresCritiques;
}

list <Mesure> CoherenceMesure::listeMesuresInnacceptables(const list<Mesure> & mesuresSuspectesList , list<Mesure> & mesuresTemoinList){
//liste des mesures innacceptables detectées par le test de chevaunet
    float moyenne = moyenneMesures(mesuresTemoinList); 
    float eType =  eTypeMesures( mesuresTemoinList , moyenne); 
    int nbMesuresTemoin = mesuresTemoinList.size();
    list <Mesure> listeMesuresInacceptables;

    list<Mesure>::const_iterator it;
    for(it = mesuresSuspectesList.begin() ; it!=mesuresSuspectesList.end() ; ++it){
        if(!calculTestChauvenet(*it, nbMesuresTemoin, moyenne, eType)){
            listeMesuresInacceptables.push_back(*it); 
        }
    }

    return listeMesuresInacceptables;
}


