#include <iostream>

#include "../GeoMap/GeoMap.h"
#include "../LectureDonnes/FluxLog.h"
#include "../Grandeur/Grandeur.h"
#include "../Mesure/Mesure.h"
#include "../Capteur/Capteur.h"
using namespace std;

int main(void) {
	//GeoMap_TEST gmt;
	//gmt.run();
	Grandeur tabgrande[4];
	Capteur cap[98];
	Mesure mes[1000];
	FluxLog flux = FluxLog("donne.csv");
	int i=0;
	
	while(!flux.eof() && i<4){
		tabgrande[i]=flux.lireDonneesGrandeur(tabgrande[i]);
		i++;
	}
	i=0;
	FluxLog capt = FluxLog("cap.csv");
	while(!capt.eof() && i<98){
		cap[i]=capt.lireDonneesCapteur(cap[i]);
		i++;
	}
	i=0;
	FluxLog me = FluxLog("mes.csv");
	while(!me.eof() && i<1000){
		mes[i]=me.lireDonneesMesure(mes[i],cap,tabgrande,98,4);
		i++;
	}
}