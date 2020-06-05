// date de derni�re modif : 05/06/2020, 12h20

#include "GeoMap.h"

// METHODES PUBLIQUES ///////////////////////////////////////////////////////////////////////////////

GeoMap::GeoMap(double MinLongitude, double MaxLongitude, double MinLatitude, double MaxLatitude, unsigned int maxValPerSubMap)
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

size_t GeoMap::size() const {
	if (mode == Mode::values)
	{
		size_t size = 0;
		for (unsigned int i = 0; i < content.values.count; ++i)
		{
			size += content.values.values[i].size();
		}
		return size;
	}
	else
	{
		return content.subMaps.topLeft->size() + content.subMaps.topRight->size() + content.subMaps.bottomLeft->size() + content.subMaps.bottomRight->size();
	}
}

bool GeoMap::insert(const Mesure& mesure) {
	Coordonnees c = mesure.GetCapteur().getCoordonnes();

	if (c.getLongitude() >= bounds.minLongitude && c.getLongitude() <= bounds.maxLongitude && c.getLatitude() >= bounds.minLatitude && c.getLatitude() <= bounds.maxLatitude)
	{
		// la valeur est dans la bonne plage

		if (mode == Mode::values)
		{
			// on est en mode valeur

			// recherche d'un set avec les bonnes coordonn�es
			for (unsigned int i = 0; i < content.values.count; ++i)
			{
				if ((*content.values.values[i].begin()).GetCapteur().getCoordonnes() == c)
				{
					// set avec les bonnes coordonn�es

					// on tente d'ins�rer
					return (content.values.values[i].insert(mesure)).second;
				}
			}

			// pas de set avec les bonnes coordonn�es

			if (content.values.count < content.values.maxCount)
			{
				// on ajoute un set avec les bonnes coordonn�es

				content.values.values[content.values.count] = set<Mesure>();

				// on tente d'ins�rer
				
				//bool out = (content.values.values[content.values.count].insert(mesure)).second;
				//////////////////////////////////////////
				auto pair = content.values.values[content.values.count].insert(mesure);
				bool out = pair.second;
				cout << "t:" << (*(pair.first)).GetTimestamp() << " v:" << (*(pair.first)).GetValeur() << " g:" << (*(pair.first)).GetGrandeur().GetIdentifiant() << endl;
				/////////////////////////////////////////

				if (out)
				{
					// on a pu mettre une valeur dans le nouveau set, on augmente le nombre de set effectif

					content.values.count++;
				}
				return out;
			}
			else
			{
				// tableau de set d�j� plein, on divise en sous maps

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

				// on place la valeur � ins�rer dans une des sous maps
				bool out = false;
				do {
					if (out = TopLeft->insert(mesure)) break;
					if (out = TopRight->insert(mesure)) break;
					if (out = BottomLeft->insert(mesure)) break;
					if (out = BottomRight->insert(mesure)) break;
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

			// on place la valeur � ins�rer dans une des sous maps
			bool out = false;
			do {
				if (out = content.subMaps.topLeft->insert(mesure)) break;
				if (out = content.subMaps.topRight->insert(mesure)) break;
				if (out = content.subMaps.bottomLeft->insert(mesure)) break;
				if (out = content.subMaps.bottomRight->insert(mesure)) break;
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

list<Mesure> GeoMap::get(const Coordonnees& center, double rayon, time_t debut, time_t fin) const {
	list<Mesure> lm;

	if (inArea(center) || center.distanceTo(projection(center)) <= rayon)
	{
		// la zone de recherche coincide avec la r�gion couverte

		if (mode == Mode::values)
		{
			// parcours des sets
			for (unsigned int i = 0; i < content.values.count; ++i)
			{
				if (center.distanceTo((*content.values.values[i].begin()).GetCapteur().getCoordonnes()) <= rayon)
				{
					// map avec les bonnes coordonn�es

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
			for (Mesure m : (*content.subMaps.topLeft).get(center, rayon, debut, fin)) { lm.push_back(m); }
			for (Mesure m : (*content.subMaps.topRight).get(center, rayon, debut, fin)) { lm.push_back(m); }
			for (Mesure m : (*content.subMaps.bottomLeft).get(center, rayon, debut, fin)) { lm.push_back(m); }
			for (Mesure m : (*content.subMaps.bottomRight).get(center, rayon, debut, fin)) { lm.push_back(m); }
		}
	}

	return lm;
}

void GeoMap::affi() const {
	if (mode == Mode::values)
	{
		for (unsigned int i = 0; i < content.values.count; ++i)
		{
			for (Mesure m : content.values.values[i])
			{
				cout << "t:" << m.GetTimestamp() << " v:" << m.GetValeur() << " g:" << m.GetGrandeur().GetIdentifiant() << endl;
			}
		}
	}
	else
	{
		(*content.subMaps.topLeft).affi();
		(*content.subMaps.topRight).affi();
		(*content.subMaps.bottomLeft).affi();
		(*content.subMaps.bottomRight).affi();
	}
}

// METHODES PROTEGEES ///////////////////////////////////////////////////////////////////////////////

bool GeoMap::insert(const set<Mesure>& mesures) {
	Coordonnees c = (*mesures.begin()).GetCapteur().getCoordonnes();

	if (c.getLongitude() >= bounds.minLongitude && c.getLongitude() <= bounds.maxLongitude && c.getLatitude() >= bounds.minLatitude && c.getLatitude() <= bounds.maxLatitude)
	{
		// la valeur est dans la bonne plage

		if (mode == Mode::values)
		{
			// on est en mode valeur

			// recherche d'un set avec les bonnes coordonn�es
			for (unsigned int i = 0; i < content.values.count; ++i)
			{
				if ((*content.values.values[i].begin()).GetCapteur().getCoordonnes() == c)
				{
					// set avec les bonnes coordonn�es

					// on tente d'ins�rer
					bool out = true;
					for (Mesure m : mesures)
					{
						out = out || (content.values.values[i].insert(m)).second;
					}

					return out;
				}
			}

			// pas de set avec les bonnes coordonn�es

			if (content.values.count < content.values.maxCount)
			{
				// on ajoute un set avec les bonnes coordonn�es

				content.values.values[content.values.count] = set<Mesure>();

				// on tente d'ins�rer
				bool out = true;
				for (Mesure m : mesures)
				{
					out = out && (content.values.values[content.values.count].insert(m)).second;
				}

				if (out)
				{
					// on a pu ins�rer dans le nouveau set, on augmente le nombre de set dans le dispositif
					content.values.count++;
				}

				return out;
			}
			else
			{
				// tableau de set d�j� plein, on divise en sous maps

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

				// on place la valeur � ins�rer dans une des sous maps
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