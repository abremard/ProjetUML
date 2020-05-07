#pragma once
#include "Coordonnees.h"

template <typename T>
class GeoMap
{
	public :
		static const unsigned int DEFAULT_MAX_VALUES = 10;

		GeoMap(double MinLongitude = -180.0, double MaxLongitude = +180.0, double MinLatitude = -90.0, double MaxLatitude = +90.0) 
		{
			bounds.minLongitude = MinLongitude;
			bounds.maxLongitude = MaxLongitude;
			bounds.minLatitude = MinLatitude;
			bounds.maxLatitude = MaxLatitude;
			mode = values;
			content.values.coords = new Coordonnees[DEFAULT_MAX_VALUES];
			content.values.values = new T[DEFAULT_MAX_VALUES];
			content.values.count = 0;
			content.values.maxCount = DEFAULT_MAX_VALUES;
		}
		
		bool insert(T Data, const Coordonnees& Coord) {
			if (Coord.getLongitude() >= bounds.minLongitude && Coord.getLongitude() <= bounds.maxLongitude && Coord.getLatitude() >= bounds.minLatitude && Coord.getLatitude() <= bounds.maxLatitude)
			{
				if (mode == values)
				{
					if (content.values.count < content.values.maxCount) ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					{
						content.values.coords[content.values.count] = Coord;
						content.values.values[content.values.count] = Data;
						++content.values.count;

						return true;
					}
					else //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					{
						GeoMap* TopLeft = new GeoMap(bounds.minLongitude, (bounds.minLongitude + bounds.maxLongitude) / 2, bounds.minLatitude, (bounds.minLatitude + bounds.maxLatitude) / 2);
						GeoMap* TopRight = new GeoMap((bounds.minLongitude + bounds.maxLongitude) / 2, bounds.maxLongitude, bounds.minLatitude, (bounds.minLatitude + bounds.maxLatitude) / 2);
						GeoMap* BottomLeft = new GeoMap(bounds.minLongitude, (bounds.minLongitude + bounds.maxLongitude) / 2, (bounds.minLatitude + bounds.maxLatitude) / 2, bounds.maxLatitude);
						GeoMap* BottomRight = new GeoMap((bounds.minLongitude + bounds.maxLongitude) / 2, bounds.maxLongitude, (bounds.minLatitude + bounds.maxLatitude) / 2, bounds.maxLatitude);

						for (unsigned int i = 0; i < content.values.maxCount; ++i)
						{
							do {
								if (     TopLeft->insert(content.values.values[i], content.values.coords[i]) ) break;
								if (    TopRight->insert(content.values.values[i], content.values.coords[i]) ) break;
								if (  BottomLeft->insert(content.values.values[i], content.values.coords[i]) ) break;
								if ( BottomRight->insert(content.values.values[i], content.values.coords[i]) ) break;
							} while (false);
						}

						do {
							if (     TopLeft->insert(Data, Coord) ) break;
							if (    TopRight->insert(Data, Coord) ) break;
							if (  BottomLeft->insert(Data, Coord) ) break;
							if ( BottomRight->insert(Data, Coord) ) break;
						} while (false);

						delete[] content.values.coords;
						delete[] content.values.values;

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
					do {
						if (     content.subMaps.topLeft->insert(Data, Coord) ) break;
						if (    content.subMaps.topRight->insert(Data, Coord) ) break;
						if (  content.subMaps.bottomLeft->insert(Data, Coord) ) break;
						if ( content.subMaps.bottomRight->insert(Data, Coord) ) break;
					} while (false);

					return true;
				}
			}
			else //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			{
				return false;
			}
		}
		
		inline unsigned int size() const {
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
				T* values;
				unsigned int count;
				unsigned int maxCount;
			} values;
		} content;
};

