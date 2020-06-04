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
		friend std::ostream& operator<<(std::ostream& os, const GeoMap& geo);

		static const unsigned int DEFAULT_MAX_VALUES = 10;

		GeoMap(double MinLongitude = -180.0, double MaxLongitude = +180.0, double MinLatitude = -90.0, double MaxLatitude = +90.0, unsigned int maxValPerSubMap = DEFAULT_MAX_VALUES)
		{
			bounds.minLongitude = MinLongitude;
			bounds.maxLongitude = MaxLongitude;
			bounds.minLatitude = MinLatitude;
			bounds.maxLatitude = MaxLatitude;
			mode = Mode::values;
			content.values.maxCount = maxValPerSubMap;
			content.values.values = new set<Mesure>[content.values.maxCount];
			content.values.count = 0;
		}

		size_t size() const {
			if (mode == Mode::values)
			{
				size_t size = 0;
				for (unsigned int i = 0; i < content.values.count; ++i)
				{
					size += content.values.values[i].size();
				}
			}
			else
			{
				return content.subMaps.topLeft->size() + content.subMaps.topRight->size() + content.subMaps.bottomLeft->size() + content.subMaps.bottomRight->size();
			}
		}

		inline bool inArea(const Coordonnees& c) const {
			return c.getLongitude() >= bounds.minLongitude && c.getLongitude() <= bounds.maxLongitude && c.getLatitude() >= bounds.minLatitude && c.getLatitude() <= bounds.maxLatitude;
		}

		// Retourne le point de la région le plus proche du point en paramètre
		inline Coordonnees projection(const Coordonnees& point) const {
			Coordonnees c(
				point.getLongitude() > bounds.maxLongitude ? bounds.maxLongitude : (point.getLongitude() <= bounds.minLongitude ? bounds.minLongitude : point.getLongitude()),
				point.getLatitude() > bounds.maxLatitude ? bounds.maxLatitude : (point.getLatitude() <= bounds.minLatitude ? bounds.minLatitude : point.getLatitude())
			);
			return c;
		}

		bool insert(const set<Mesure>& mesures) {
			Coordonnees c = (*mesures.begin()).GetCapteur().getCoordonnes();

			if (c.getLongitude() >= bounds.minLongitude && c.getLongitude() <= bounds.maxLongitude && c.getLatitude() >= bounds.minLatitude && c.getLatitude() <= bounds.maxLatitude)
			{
				// la valeur est dans la bonne plage

				if (mode == Mode::values)
				{
					// on est en mode valeur

					// recherche d'un set avec les bonnes coordonnées
					for (unsigned int i = 0; i < content.values.count; ++i)
					{
						if ((*content.values.values[i].begin()).GetCapteur().getCoordonnes() == c)
						{
							// set avec les bonnes coordonnées

							// on tente d'insérer
							bool out = true;
							for (Mesure m : mesures)
							{
								out = out || (content.values.values[i].insert(m)).second;
							}

							return out;
						}
					}

					// pas de set avec les bonnes coordonnées

					if (content.values.count < content.values.maxCount)
					{
						// on ajoute un set avec les bonnes coordonnées

						content.values.values[content.values.count] = set<Mesure>();

						// on tente d'insérer
						bool out = true;
						for (Mesure m : mesures)
						{
							out = out && (content.values.values[content.values.count].insert(m)).second;
						}

						if (out)
						{
							// on a pu insérer dans le nouveau set, on augmente le nombre de set dans le dispositif
							content.values.count++;
						}

						return out;
					}
					else
					{
						// tableau de set déjà plein, on divise en sous maps

						GeoMap* TopLeft = new GeoMap(bounds.minLongitude, (bounds.minLongitude + bounds.maxLongitude) / 2, bounds.minLatitude, (bounds.minLatitude + bounds.maxLatitude) / 2, content.values.count);
						GeoMap* TopRight = new GeoMap((bounds.minLongitude + bounds.maxLongitude) / 2, bounds.maxLongitude, bounds.minLatitude, (bounds.minLatitude + bounds.maxLatitude) / 2, content.values.count);
						GeoMap* BottomLeft = new GeoMap(bounds.minLongitude, (bounds.minLongitude + bounds.maxLongitude) / 2, (bounds.minLatitude + bounds.maxLatitude) / 2, bounds.maxLatitude, content.values.count);
						GeoMap* BottomRight = new GeoMap((bounds.minLongitude + bounds.maxLongitude) / 2, bounds.maxLongitude, (bounds.minLatitude + bounds.maxLatitude) / 2, bounds.maxLatitude, content.values.count);

						for (unsigned int i = 0; i < content.values.maxCount; ++i)
						{
							// on place chaque set dans les sous maps
							do {
								if (TopLeft->insert(content.values.values[i])) break;
								if (TopRight->insert(content.values.values[i])) break;
								if (BottomLeft->insert(content.values.values[i])) break;
								if (BottomRight->insert(content.values.values[i])) break;
							} while (false);
						}

						// on place la valeur à insérer dans une des sous maps
						for (Mesure m : mesures)
						{
							do {
								if (TopLeft->insert(m)) break;
								if (TopRight->insert(m)) break;
								if (BottomLeft->insert(m)) break;
								if (BottomRight->insert(m)) break;
							} while (false);
						}

						// on passe en mode sous maps
						delete[] content.values.values;
						content.subMaps.topLeft = TopLeft;
						content.subMaps.topRight = TopRight;
						content.subMaps.bottomLeft = BottomLeft;
						content.subMaps.bottomRight = BottomRight;
						mode = Mode::subMaps;

						return true;
					}
				}
			}

			return false;
		}

		bool insert(const Mesure& mesure) {
			Coordonnees c = mesure.GetCapteur().getCoordonnes();

			if (c.getLongitude() >= bounds.minLongitude && c.getLongitude() <= bounds.maxLongitude && c.getLatitude() >= bounds.minLatitude && c.getLatitude() <= bounds.maxLatitude)
			{
				// la valeur est dans la bonne plage

				if (mode == Mode::values)
				{
					// on est en mode valeur

					// recherche d'un set avec les bonnes coordonnées
					for (unsigned int i = 0; i < content.values.count; ++i)
					{
						if ( (*content.values.values[i].begin()).GetCapteur().getCoordonnes() == c )
						{
							// set avec les bonnes coordonnées

							// on tente d'insérer
							return ( content.values.values[i].insert(mesure) ).second;
						}
					}

					// pas de set avec les bonnes coordonnées

					if (content.values.count < content.values.maxCount)
					{
						// on ajoute un set avec les bonnes coordonnées

						content.values.values[content.values.count] = set<Mesure>();

						// on tente d'insérer
						bool out = (content.values.values[content.values.count].insert(mesure)).second;

						if (out)
						{
							// on a pu mettre une valeur dans le nouveau set, on augmente le nombre de set effectif

							content.values.count++;
						}
						return out;
					}
					else
					{
						// tableau de set déjà plein, on divise en sous maps

						GeoMap*     TopLeft = new GeoMap(bounds.minLongitude, (bounds.minLongitude + bounds.maxLongitude) / 2, bounds.minLatitude, (bounds.minLatitude + bounds.maxLatitude) / 2, content.values.count);
						GeoMap*    TopRight = new GeoMap((bounds.minLongitude + bounds.maxLongitude) / 2, bounds.maxLongitude, bounds.minLatitude, (bounds.minLatitude + bounds.maxLatitude) / 2, content.values.count);
						GeoMap*  BottomLeft = new GeoMap(bounds.minLongitude, (bounds.minLongitude + bounds.maxLongitude) / 2, (bounds.minLatitude + bounds.maxLatitude) / 2, bounds.maxLatitude, content.values.count);
						GeoMap* BottomRight = new GeoMap((bounds.minLongitude + bounds.maxLongitude) / 2, bounds.maxLongitude, (bounds.minLatitude + bounds.maxLatitude) / 2, bounds.maxLatitude, content.values.count);

						for (unsigned int i = 0; i < content.values.maxCount; ++i)
						{
							// on place chaque set dans les sous maps
							do {
								if (     TopLeft->insert(content.values.values[i]) ) break;
								if (    TopRight->insert(content.values.values[i]) ) break;
								if (  BottomLeft->insert(content.values.values[i]) ) break;
								if ( BottomRight->insert(content.values.values[i]) ) break;
							} while (false);
						}

						// on place la valeur à insérer dans une des sous maps
						bool out = false;
						do {
							if ( out =     TopLeft->insert(mesure) ) break;
							if ( out =    TopRight->insert(mesure) ) break;
							if ( out =  BottomLeft->insert(mesure) ) break;
							if ( out = BottomRight->insert(mesure) ) break;
						} while (false);

						// on passe en mode sous maps
						delete[] content.values.values;
						content.subMaps.topLeft = TopLeft;
						content.subMaps.topRight = TopRight;
						content.subMaps.bottomLeft = BottomLeft;
						content.subMaps.bottomRight = BottomRight;
						mode = Mode::subMaps;

						return out;
					}
				}
				else
				{
					// on est en mode sous maps

					// on place la valeur à insérer dans une des sous maps
					bool out = false;
					do {
						if ( out =     content.subMaps.topLeft->insert(mesure) ) break;
						if ( out =    content.subMaps.topRight->insert(mesure) ) break;
						if ( out =  content.subMaps.bottomLeft->insert(mesure) ) break;
						if ( out = content.subMaps.bottomRight->insert(mesure) ) break;
					} while (false);

					return out;
				}
			}
			else
			{
				// la valeur n'est pas dans la bonne plage

				return false;
			}
		}

		list<Mesure>& get(const Coordonnees& center = Coordonnees(), double rayon = 0, time_t debut = (time_t)0, time_t fin = (time_t)(~0u)) const {
			list<Mesure> lm;

			if (inArea(center) || center.distanceTo(projection(center)) <= rayon)
			{
				// la zone de recherche coincide avec la région couverte
				
				if (mode == Mode::values)
				{
					// parcours des sets
					for (unsigned int i = 0; i < content.values.count; ++i)
					{
						if ( center.distanceTo( (*content.values.values[i].begin()).GetCapteur().getCoordonnes() ) <= rayon )
						{
							// map avec les bonnes coordonnées

							for (Mesure m : content.values.values[i])
							{
								if (m.GetTimestamp() >= debut && m.GetTimestamp() <= fin)
								{
									// mesure avec la bonne date

									lm.push_back(m);
								}
							}
						}
					}
				}
				else
				{
					lm.merge((*content.subMaps.topLeft).get(center, rayon, debut, fin));
					lm.merge((*content.subMaps.topRight).get(center, rayon, debut, fin));
					lm.merge((*content.subMaps.bottomLeft).get(center, rayon, debut, fin));
					lm.merge((*content.subMaps.bottomRight).get(center, rayon, debut, fin));
				}
			}

			return lm;
		}

	protected:
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
};

inline std::ostream& operator<<(std::ostream& os, const GeoMap& geo) {
	return os << "[" << geo.bounds.minLongitude << ", " << geo.bounds.maxLongitude << "] x [" << geo.bounds.minLatitude << ", " << geo.bounds.maxLatitude << "]";
}




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
			insert_size_TEST();
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

		void insert_size_TEST() {
			GeoMap geo(-50, 50, -50, 50);
			for (int i = -10; i <= 10; i++)
			{
				for (int j = -10; j <= 10; j++)
				{
					Mesure m(0, 0, Capteur("", Coordonnees(i, j)));
					geo.insert(m);
					cout << geo.size() << " ";
				}
			}
		}
};




/*
class GeoMap
{
	public :
		static const unsigned int DEFAULT_MAX_VALUES = 10;

		GeoMap(double MinLongitude = -180.0, double MaxLongitude = +180.0, double MinLatitude = -90.0, double MaxLatitude = +90.0, unsigned int maxValPerSubMap = DEFAULT_MAX_VALUES)
		{
			bounds.minLongitude = MinLongitude;
			bounds.maxLongitude = MaxLongitude;
			bounds.minLatitude = MinLatitude;
			bounds.maxLatitude = MaxLatitude;
			mode = values;
			content.values.maxCount = maxValPerSubMap;
			content.values.coords = new Coordonnees[content.values.maxCount];
			content.values.values = new D[content.values.maxCount];
			content.values.count = 0;
		}
		
		bool insert(const Mesure& mesure) {
			Coordonnees c = mesure.GetCapteur().getCoordonnes();

			if (c.getLongitude() >= bounds.minLongitude && c.getLongitude() <= bounds.maxLongitude && c.getLatitude() >= bounds.minLatitude && c.getLatitude() <= bounds.maxLatitude)
			{
				// la valeur est dans la bonne plage

				if (mode == values)
				{
					// on est en mode valeur

					// recherche d'une map avec les bonnes coordonnées
					for (int i = 0; i < content.values.count; ++i)
					{
						if (content.values.coords[i] == Coord)
						{
							// map avec les bonnes coordonnées

							// on tente d'insérer
							return content.values.values[i].insert(std::pair<T, D>(Time, Data)).second;
						}
					}
					
					// pas de map avec les bonnes coordonnées
					if (content.values.count < content.values.maxCount) ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					{
						// on ajoute une map avec les bonnes coordonnées
						content.values.coords[content.values.count] = Coord;
						content.values.values[content.values.count] = std::map<T, D>();

						// on tente d'insérer
						return content.values.values[content.values.count++].insert(std::pair<T, D>(Time, Data)).second;
					}
					else //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					{
						// tableau de map déjà plein, on divise en sous maps

						GeoMap*     TopLeft = new GeoMap(bounds.minLongitude, (bounds.minLongitude + bounds.maxLongitude) / 2, bounds.minLatitude, (bounds.minLatitude + bounds.maxLatitude) / 2, content.values.count);
						GeoMap*    TopRight = new GeoMap((bounds.minLongitude + bounds.maxLongitude) / 2, bounds.maxLongitude, bounds.minLatitude, (bounds.minLatitude + bounds.maxLatitude) / 2, content.values.count);
						GeoMap*  BottomLeft = new GeoMap(bounds.minLongitude, (bounds.minLongitude + bounds.maxLongitude) / 2, (bounds.minLatitude + bounds.maxLatitude) / 2, bounds.maxLatitude, content.values.count);
						GeoMap* BottomRight = new GeoMap((bounds.minLongitude + bounds.maxLongitude) / 2, bounds.maxLongitude, (bounds.minLatitude + bounds.maxLatitude) / 2, bounds.maxLatitude, content.values.count);

						for (unsigned int i = 0; i < content.values.maxCount; ++i)
						{
							// on place chaque map dans les sous maps
							do {
								if (     TopLeft->insert(content.values.coords[i], content.values.values[i]) ) break;
								if (    TopRight->insert(content.values.coords[i], content.values.values[i]) ) break;
								if (  BottomLeft->insert(content.values.coords[i], content.values.values[i]) ) break;
								if ( BottomRight->insert(content.values.coords[i], content.values.values[i]) ) break;
							} while (false);
						}

						// on place la valeur à insérer dans une des sous maps
						do {
							if (     TopLeft->insert(Coord, Time, Data) ) break;
							if (    TopRight->insert(Coord, Time, Data) ) break;
							if (  BottomLeft->insert(Coord, Time, Data) ) break;
							if ( BottomRight->insert(Coord, Time, Data) ) break;
						} while (false);

						delete[] content.values.coords;
						delete[] content.values.values;

						// on passe en mode sous maps
						content.subMaps.topLeft = TopLeft;
						content.subMaps.topRight = TopRight;
						content.subMaps.bottomLeft = BottomLeft;
						content.subMaps.bottomRight = BottomRight;
						mode = subMaps;

						return true;
					}
				}
				else //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				{
					// on est en mode sous maps

					// on place la valeur à insérer dans une des sous maps
					do {
						if (     content.subMaps.topLeft->insert(Coord, Time, Data) ) break;
						if (    content.subMaps.topRight->insert(Coord, Time, Data) ) break;
						if (  content.subMaps.bottomLeft->insert(Coord, Time, Data) ) break;
						if ( content.subMaps.bottomRight->insert(Coord, Time, Data) ) break;
					} while (false);

					return true;
				}
			}
			else //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			{
				// la valeur n'est pas dans la bonne plage

				return false;
			}
		}
		
		unsigned int size() const {
			if (mode == values)
			{
				return content.values.count;
			}
			else
			{
				return content.subMaps.topLeft->size() + content.subMaps.topRight->size() + content.subMaps.bottomLeft->size() + content.subMaps.bottomRight->size();
			}
		}

	protected:
		struct {
			double minLongitude;
			double maxLongitude;
			double minLatitude;
			double maxLatitude;
		} bounds;
		enum {
			values,
			subMaps
		} mode;
		union {
			struct {
				GeoMap* topLeft;
				GeoMap* topRight;
				GeoMap* bottomLeft;
				GeoMap* bottomRight;
			} subMaps;
			struct {
				Coordonnees* coords;
				std::map<T, D>* values;
				unsigned int count;
				unsigned int maxCount;
			} values;
		} content;
};
*/
