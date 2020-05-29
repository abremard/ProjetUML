#pragma once
#include <set>
#include "../Coordonnees/Coordonnees.h"
#include "../Mesure/Mesure.h"

using namespace std;

/**
 *	@author Eric TESTU
 */
class GeoMap
{
	public:
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

		inline bool inArea(const Coordonnees& c) {
			return c.getLongitude() >= bounds.minLongitude && c.getLongitude() <= bounds.maxLongitude && c.getLatitude() >= bounds.minLatitude && c.getLatitude() <= bounds.maxLatitude;
		}

		bool insert(const set<Mesure>& mesures) {
			Coordonnees c = (*mesures.begin()).GetCapteur().getCoordonnes();

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
							// map avec les bonnes coordonnées

							// on tente d'insérer
							return ( content.values.values[i].insert(mesure) ).second;
						}
					}

					// pas de set avec les bonnes coordonnées

					if (content.values.count < content.values.maxCount)
					{
						// on ajoute une map avec les bonnes coordonnées
						content.values.values[content.values.count] = set<Mesure>();

						// on tente d'insérer
						return ( content.values.values[content.values.count++].insert(mesure) ).second;
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
						do {
							if (     TopLeft->insert(mesure) ) break;
							if (    TopRight->insert(mesure) ) break;
							if (  BottomLeft->insert(mesure) ) break;
							if ( BottomRight->insert(mesure) ) break;
						} while (false);

						delete[] content.values.values;

						// on passe en mode sous maps
						content.subMaps.topLeft = TopLeft;
						content.subMaps.topRight = TopRight;
						content.subMaps.bottomLeft = BottomLeft;
						content.subMaps.bottomRight = BottomRight;
						mode = Mode::subMaps;

						return true;
					}

				}
			}
			else
			{
				// la valeur n'est pas dans la bonne plage

				return false;
			}
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
