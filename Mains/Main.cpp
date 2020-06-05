#include <iostream>

#include "../GeoMap/GeoMap.h"
#include "../LectureDonnes/FluxLog.h"
#include "../Grandeur/Grandeur.h"
#include "../Mesure/Mesure.h"
#include "../Capteur/Capteur.h"
#include "../Qualite_Air/Qualite.h"
using namespace std;

int main(void) {
	//GeoMap_TEST gmt;
	//gmt.run();
	GeoMap gm = GeoMap();
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
		gm.insert(mes[i]);
		i++;
	}
	Coordonnees centre = Coordonnees(40.0, 0.0);

	time_t dateDebut;
	time_t dateFin;

	string deb = "2019-01-01 12:00:00";
	string fin = "2019-12-30 12:00:00";

	struct tm tm;
	strptime(deb.c_str(),"%Y-%m-%d %H:%M:%S",&tm);
	dateDebut=mktime(&tm);

	strptime(fin.c_str(),"%Y-%m-%d %H:%M:%S",&tm);
	dateFin=mktime(&tm);

	resultat res = qualiteMoyenne(gm, centre, 2.0, dateDebut, dateFin);

	cout << res.NO2.ET;
}