#include <iostream>

#include "../GeoMap/GeoMap.h"
#include "../LectureDonnes/FluxLog.h"
#include "../Grandeur/Grandeur.h"
using namespace std;

int main(void) {
	//GeoMap_TEST gmt;
	//gmt.run();
	Grandeur tabgrande[10];
	FluxLog flux = FluxLog("donne.csv");
	int i=0;
	
	while(!flux.eof() && i<10){
		flux.lireDonneesGrandeur(tabgrande[i]);
		cout << "ca passe"<<endl;
		i++;
	}
	
}