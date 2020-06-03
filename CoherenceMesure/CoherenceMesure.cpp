//----- Réalisation de la classe <CoherenceMesure> (fichier CoherenceMesure.cpp) -----

//---------------------------------------------------------------- INCLUDE
#include "../Mesure/Mesure.h"

//-------------------------------------------------------- Include système
# define M_PI 3.14159265358979323846
using namespace std;
#include <iostream>

/*
// Main de tests:
    //dans le repertoire Mesure:
    //g++ -c Mesure.cpp
    //dans le repertoire Coherence Mesure:
    //g++ -o exeCoherence CoherenceMesure.cpp ../Mesure/Mesure.o 
void identificationMesureAberantes(const Mesure* mesuresArray,const int nbMesure);
int main()
{
    Mesure m1 = Mesure();
    Mesure m2 = Mesure();
    Mesure m3 = Mesure();
    Mesure m4 = Mesure();
    Mesure m5 = Mesure();
    Mesure m7 = Mesure();
    Mesure m6 = Mesure();
    Mesure m8 = Mesure();
    Mesure m9 = Mesure();
    Mesure m10 = Mesure();
    Mesure m11 = Mesure();
    Mesure m12 = Mesure();
    Mesure m13 = Mesure();

    m1.SetValeur(105);
    m2.SetValeur(28);
    m3.SetValeur(75);
    m4.SetValeur(14);
    m5.SetValeur(38);
    m6.SetValeur(21);
    m7.SetValeur(12);
    m8.SetValeur(23);
    m9.SetValeur(55);
    m10.SetValeur(25);
    m11.SetValeur(11);
    m12.SetValeur(12);
    m13.SetValeur(13);

    Mesure mesuresArray [13] = {m1,m2,m3,m4,m5,m6,m7,m8,m9,m10,m11,m12,m13};
    for(int i=0 ; i<sizeof(mesuresArray)/sizeof(*mesuresArray); i++){cout<<mesuresArray[i].GetValeur()<<endl;}

    identificationMesureAberantes(mesuresArray,sizeof(mesuresArray)/sizeof(*mesuresArray));

    return 0;
}*/


//Test de Chevaunet
//le but est de déterminer pour une ValeurSuspecte si elle abérante, conaissant la moyenne, la variance et la taille de l'echantillon de données
float calculTestChauvenet(const Mesure & mesureSuspecte,const int nbMesure,const float moyenne,const float ecartTye){

    bool res = true;

    // si n * ercf(  |  valeurSuspecte - moyenne | / eType )  < 0.5  alors la valeur est abérante
    float na = nbMesure*erfc(abs(mesureSuspecte.GetValeur()-moyenne)/ecartTye); 
    //cout<<"na: "<<na<<endl;
    if(na < 0.5){res = false;}

    return res;
}

//calcul de la moyenne d'un tableau de mesures
float moyenneMesures(const Mesure* mesuresArray,const int nbMesure)
{
    float moyenne = 0;
    for(int i = 0; i < nbMesure; i++){
        moyenne += mesuresArray[i].GetValeur();
    }
    moyenne = moyenne / (float)nbMesure;
    return moyenne;
}

//calcul de l'ecart type d'un tableau de mesures
float eTypeMesures(const Mesure* mesuresArray,const int nbMesure,const float moyenne)
{
    float eType = 0 ;
     for(int j = 0; j < nbMesure; j++){
        eType += (mesuresArray[j].GetValeur() - moyenne) * (mesuresArray[j].GetValeur() - moyenne );
    }

    eType=sqrt((eType)/(float)nbMesure);
    return eType;
}



//lorsque l'on reçoit un tableau de mesures d'un même capteur -> repérer les valeurs suspectes
void identificationMesureAberantes(const Mesure* mesuresArray,const int nbMesure){

    //calcul moyenne
    float moyenne = moyenneMesures(mesuresArray, nbMesure);
    //calcul ecart type
    float eType =  eTypeMesures( mesuresArray, nbMesure, moyenne);

    cout<<"nbMesure: "<<nbMesure<<endl;
    cout<<"moyenne: "<<moyenne<<endl;
    cout<<"eType: "<<eType<<endl;
    
    //Test de Chevaunet
    bool res [nbMesure];
    for(int k=0 ; k<nbMesure ; k++)
    {
        res[k]=calculTestChauvenet(mesuresArray[k], nbMesure, moyenne, eType);
    }
    for(int k=0 ; k<nbMesure ; k++){
        cout<<"res[k]: "<<res[k];
        if(!res[k]){cout<<"  valueur suspecte: "<<mesuresArray[k].GetValeur()<<endl;}
        else{cout<<endl;}
        }
}