#pragma once
#include <iostream>
#include <set>
#include <list>
#include "../Coordonnees/Coordonnees.h"
#include "../Mesure/Mesure.h"

/**
 *	@author Eric TESTU
 */
class GeoMap
{
	public:
		// AMITIE ///////////////////////////////////////////////////////////////////////////////////////////
		friend std::ostream& operator<<(std::ostream& os, const GeoMap& geo);

		// CONSTANTES ///////////////////////////////////////////////////////////////////////////////////////
		static const unsigned int DEFAULT_MAX_VALUES = 10;

		// CONSTRUCTEURS ET DESTRUCTEURS ////////////////////////////////////////////////////////////////////
		GeoMap(double MinLongitude = -180.0, double MaxLongitude = +180.0, double MinLatitude = -90.0, double MaxLatitude = +90.0, unsigned int maxValPerSubMap = DEFAULT_MAX_VALUES);

		// METHODES PUBLIQUES ///////////////////////////////////////////////////////////////////////////////
		size_t size() const;

		inline bool inArea(const Coordonnees& c) const {
			return c.getLongitude() >= bounds.minLongitude && c.getLongitude() <= bounds.maxLongitude && c.getLatitude() >= bounds.minLatitude && c.getLatitude() <= bounds.maxLatitude;
		}

		inline Coordonnees projection(const Coordonnees& point) const {
			return Coordonnees(
				point.getLongitude() > bounds.maxLongitude ? bounds.maxLongitude : (point.getLongitude() <= bounds.minLongitude ? bounds.minLongitude : point.getLongitude()),
				point.getLatitude() > bounds.maxLatitude ? bounds.maxLatitude : (point.getLatitude() <= bounds.minLatitude ? bounds.minLatitude : point.getLatitude())
			);
		}

		bool insert(const Mesure& mesure);

		list<Mesure> get(const Coordonnees& center = Coordonnees(), double rayon = 0, time_t debut = (time_t)0, time_t fin = (time_t)(~0u)) const;

	protected:
		// ATTRIBUTS ////////////////////////////////////////////////////////////////////////////////////////
		struct {
			double minLongitude;
			double maxLongitude;
			double minLatitude;
			double maxLatitude;
		} bounds;
		enum class Mode {
			values = 1,
			subMaps = 2
		} mode;
		union {
			struct {
				GeoMap* topLeft;
				GeoMap* topRight;
				GeoMap* bottomLeft;
				GeoMap* bottomRight;
			} subMaps;
			struct {
				set<Mesure>* values;
				unsigned int count;
				unsigned int maxCount;
			} values;
		} content;

		// METHODES PROTEGEES ///////////////////////////////////////////////////////////////////////////////
		bool insert(const set<Mesure>& mesures);
};

inline std::ostream& operator<<(std::ostream& os, const GeoMap& geo) {
	return os << "[" << geo.bounds.minLongitude << ", " << geo.bounds.maxLongitude << "] x [" << geo.bounds.minLatitude << ", " << geo.bounds.maxLatitude << "]";
}




#ifdef MAP

#include "../Capteur/Capteur.h"
#include "../Grandeur/Grandeur.h"
// TEST
using namespace std;
class GeoMap_TEST
{
	public:
		void run() {
			inArea_TEST();
			projection_TEST();
			insert_size_get_TEST();
		}

		void inArea_TEST() {
			cout << endl << "inArea_TEST" << endl;

			GeoMap geo = GeoMap(-2, 2, -1, 1);
			for (int i = -3; i <= 3; i++)
			{
				for (int j = -2; j <= 2; j++)
				{
					Coordonnees c(i, j);
					bool ia = geo.inArea(c);
					cout << (ia ? "^" : "v");
				}
				cout << endl;
			}
		}

		void projection_TEST() {
			cout << endl << "projection_TEST" << endl;

			GeoMap geo = GeoMap(-2, 2, -1, 1);
			for (int i = -4; i <= 4; i++)
			{
				for (int j = -3; j <= 3; j++)
				{
					Coordonnees c(i, j);
					cout << c << " ->\t" << geo.projection(c) << endl;
				}
			}
		}

		void insert_size_get_TEST() {
			GeoMap geo(-50, 50, -50, 50);
			for (int i = -10; i <= 10; i++)
			{
				for (int j = -10; j <= 10; j++)
				{
					Coordonnees co = Coordonnees(i, j);
					Capteur ca = Capteur("", co);
					Mesure m((i+j)*(i+j), i + j, ca);
					bool b = geo.insert(m);
					cout << geo.size() << (b ? "^" : "v") << " ";
				}
			}

			cout << endl;

			for (int i = 1; i <= 10000000; i*=10)
			{
				list<Mesure> lm = geo.get(Coordonnees(3, 2), i);
				for (Mesure m : lm)
				{
					m.Afficher();
				}
				cout << endl;
			}
			
		}
};

#endif
