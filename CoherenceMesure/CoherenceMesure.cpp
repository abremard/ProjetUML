//----- Réalisation de la classe <CoherenceMesure> (fichier CoherenceMesure.cpp) -----

//---------------------------------------------------------------- INCLUDE
#include "../Mesure/Mesure.h"

//-------------------------------------------------------- Include système
# define M_PI 3.14159265358979323846
using namespace std;
#include <iostream>
#include <list>
#include <algorithm>
 /*
// Main de tests:
    //dans le repertoire Mesure:
    //g++ -c Mesure.cpp
    //dans le repertoire Coherence Mesure:
    //g++ -o exeCoherence CoherenceMesure.cpp ../Mesure/Mesure.o 
list<Mesure> obtenirMesureAberantes(const Mesure* mesuresArray,const int nbMesure);
float moyenneMesures(const list<Mesure> & mesuresList);
float eTypeMesures(const list<Mesure> & mesuresList,const float moyenne);
bool testMesureAcceptable(const list<Mesure> & mesuresTemoinList,const Mesure & mesure);
bool conditionTri(Mesure m1 , Mesure m2);
void bornesCinqPourcents(list <Mesure> mesuresList , float & bInf, float & bSup);

int main()
{
    int nbMesures = 27;
    list<Mesure>::iterator i;

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
    Mesure m14 = Mesure();
    Mesure m15 = Mesure();
    Mesure m16 = Mesure();
    Mesure m17 = Mesure();
    Mesure m18 = Mesure();
    Mesure m19 = Mesure();
    Mesure m20 = Mesure();
    Mesure m21 = Mesure();
    Mesure m22 = Mesure();
    Mesure m23 = Mesure();
    Mesure m24 = Mesure();
    Mesure m25 = Mesure();
    Mesure m26 = Mesure();
    Mesure m27 = Mesure();

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
    m13.SetValeur(-28);
    m14.SetValeur(13);
    m15.SetValeur(5);
    m16.SetValeur(13);
    m17.SetValeur(13);
    m18.SetValeur(13);
    m19.SetValeur(13);
    m20.SetValeur(13);
    m21.SetValeur(13);
    m22.SetValeur(13);
    m23.SetValeur(13);
    m24.SetValeur(13);
    m25.SetValeur(13);
    m26.SetValeur(69);
    m27.SetValeur(55);

    //avec un tableau
        //declaration
        Mesure mesuresArray [nbMesures] = {m1,m2,m3,m4,m5,m6,m7,m8,m9,m10,m11,m12,m13,m14,m15,m16,m17,m18,m19,m20,m21,m22,m23,m24,m25,m26,m27};
        int tailleArray = sizeof(mesuresArray)/sizeof(*mesuresArray);
       // for(int i=0 ; i<tailleArray; i++){cout<<"tableau: "<<mesuresArray[i].GetValeur()<<endl;}

    //avec une liste
        //declaration + affichage
        list<Mesure> mesuresList; 
        for(int k=0 ; k<nbMesures ; k++){mesuresList.push_back(mesuresArray[k]);} 
        

        //moyenne liste
        float moyenneList = moyenneMesures(mesuresList);
        cout<<"list: moyenne: "<<moyenneList<<endl;

        //eType liste
        float eTypeList = eTypeMesures(mesuresList,moyenneList);
        cout<<"list: eType: "<<eTypeList<<endl; 

        //tri
        mesuresList.sort(conditionTri); 

        //mesure accptable 
        int cpt = 0;
        for(i=mesuresList.begin(); i != mesuresList.end(); ++i) 
        {
            cpt++;
            cout<<"list["<<cpt<<"]: "<<i->GetValeur();
            if(!testMesureAcceptable(mesuresList,*i)){cout<<"  -> mesure douteuse";}
            cout<<endl;
        }

        //detection des bornes
        float bInf = -1;
        float bSup = -1;
        bornesCinqPourcents(mesuresList,bInf,bSup);
        cout<<"bInf 5%: "<<bInf<<endl<<"bSup 95%: "<<bSup<<endl;
    
    return 0; 
}
*/
bool conditionTri(Mesure m1 , Mesure m2){
    return (m1.GetValeur() < m2.GetValeur());
} 

void bornesCinqPourcents(list <Mesure> mesuresList , float & bInf, float & bSup){
//trie la liste puis retourne par passage de parametre les premieres valeurs inférieurs et superieurs à 95% des valeurs  
    
    int nbMesures = mesuresList.size();
    mesuresList.sort(conditionTri);//tri de la liste
    list <Mesure>::const_iterator it =  mesuresList.begin();

    //borne inferieur
    int kCinqPourcents = 5*nbMesures/100 ;
    for(int k=1 ; k < kCinqPourcents; k++) {++it;}         
    bInf = it->GetValeur(); 

    //borne superieur
    it = mesuresList.end();
    for( int k = nbMesures ; k >  nbMesures-kCinqPourcents ; k--) {--it;}          
    bSup = it->GetValeur(); 

}

bool calculTestChauvenet(const Mesure & mesureSuspecte,const int nbMesureTemoin,const float moyenneTemoin,const float ecartTyeTemoin){
//Test de Chevaunet
//le but est de déterminer pour une ValeurSuspecte si elle est abérante, conaissant la moyenne, la variance et la taille d'un echantillon temoin de données
    
    bool res = true;

    // si n * ercf(  |  valeurSuspecte - moyenne | / eType )  < 0.5  alors la valeur est abérante
    float na = nbMesureTemoin*erfc(abs(mesureSuspecte.GetValeur()-moyenneTemoin)/ecartTyeTemoin);  
    //cout<<"na: "<<na<<endl;
    if(na < 0.5){res = false;}
 
    return res;
}
float moyenneMesures(const list<Mesure> & mesuresList){
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
float eTypeMesures(const list<Mesure> & mesuresList,const float moyenne){
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

//pour une mesure, déterminer si elle est suspecte par rapport à un echantillon temoin
bool testMesureAcceptable(const list<Mesure> & mesuresTemoinList,const Mesure & mesure){
    
    float moyenne = moyenneMesures(mesuresTemoinList); 
    float eType =  eTypeMesures( mesuresTemoinList , moyenne); 
    int nbMesuresTemoin = mesuresTemoinList.size();
        
    if(mesure.GetValeur() < 0){//Test si la valeur est négative
        return false;
    }
    else if(!calculTestChauvenet(mesure, nbMesuresTemoin, moyenne, eType)){//Test de Chevaunet
        return false; 
    }

    return true;
} 

//lorsque l'on reçoit un tableau de mesures d'un même capteur -> repérer les valeurs suspectes au sein même de l'echantillon et les retourner dans une liste 
/*list<Mesure> obtenirMesureAberantes(const Mesure* mesuresArray,const int nbMesure){
  
    float moyenne = moyenneMesures(mesuresArray, nbMesure); //calcul moyenne
    float eType =  eTypeMesures( mesuresArray, nbMesure, moyenne); //calcul ecart type
     
    //creation de la liste fausse donnees
    list<Mesure> donneesFaussees;
    for(int k=0 ; k<nbMesure ; k++)
    {
        //Test si la valeur est négative 
        if(mesuresArray[k].GetValeur() < 0)
        {
            donneesFaussees.push_back(mesuresArray[k]);
        }
        //Test de Chevaunet
        else if(!calculTestChauvenet(mesuresArray[k], nbMesure, moyenne, eType)){
            donneesFaussees.push_back(mesuresArray[k]);
        }
    }
    return donneesFaussees;
} */
