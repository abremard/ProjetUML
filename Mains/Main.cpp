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

	// while(true) {
	// cout << "Action a effectuer ?" << endl << "1:\tlire les donnees" << endl << "2:\tcentre + rayon" << endl;
	// int action;
	// cin >> action;
	// switch(action) {
	// 	case 1: {
	// 		break;
	// 	}
	// 	case 2: {
	// 		break;
	// 	}
	// }
	// }

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
	Coordonnees centre = Coordonnees(0.0, 0.0);

	time_t dateDebut;
	time_t dateFin;

	string deb = "2019-01-01 12:00:00";
	string fin = "2019-12-30 12:00:00";

	struct tm tm;
	strptime(deb.c_str(),"%Y-%m-%d %H:%M:%S",&tm);
	dateDebut=mktime(&tm);

	strptime(fin.c_str(),"%Y-%m-%d %H:%M:%S",&tm);
	dateFin=mktime(&tm);

	resultat res = qualiteMoyenne(gm, centre, 10000.0, dateDebut, dateFin);

	cout << "------NO2-----" << endl;
	cout << "Ecart-type " << res.NO2.ET << endl;
	cout << "Max " << res.NO2.max << endl;
	cout << "Min " << res.NO2.min << endl;
	cout << "Moyenne " << res.NO2.moy << endl;

	cout << "------O3-----" << endl;
	cout << "Ecart-type " << res.O3.ET << endl;
	cout << "Max " << res.O3.max << endl;
	cout << "Min " << res.O3.min << endl;
	cout << "Moyenne " << res.O3.moy << endl;

	cout << "------PM10-----" << endl;
	cout << "Ecart-type " << res.PM10.ET << endl;
	cout << "Max " << res.PM10.max << endl;
	cout << "Min " << res.PM10.min << endl;
	cout << "Moyenne " << res.PM10.moy << endl;

	cout << "------SO2-----" << endl;
	cout << "Ecart-type " << res.SO2.ET << endl;
	cout << "Max " << res.SO2.max << endl;
	cout << "Min " << res.SO2.min << endl;
	cout << "Moyenne " << res.SO2.moy << endl;
}