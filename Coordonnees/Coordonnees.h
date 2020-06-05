#pragma once
#include <stdlib.h>
#include <iostream>

#define _USE_MATH_DEFINES
#include <math.h>

class Coordonnees
{
	public:
		// en metres, rayon moyen de la Terre (https://fr.wikipedia.org/wiki/Terre)
		static constexpr double DEFAULT_RADIUS = 6371008.0;

		// longitude entre -180ï¿½ et 180ï¿½, latitude entre -90ï¿½ et 90ï¿½, rayon positif
		Coordonnees(double Longitute = 0.0, double Latitude = 0.0, double Radius = DEFAULT_RADIUS)
			: longitude(Longitute), latitude(Latitude), radius(Radius)
		{}
		Coordonnees(const Coordonnees& coord)
			: Coordonnees(coord.longitude, coord.latitude, coord.radius)
		{}

		inline Coordonnees& operator =(const Coordonnees& coord) {
			longitude = coord.longitude;
			latitude = coord.latitude;
			radius = coord.radius;
			return *this;
		}

		inline bool operator ==(const Coordonnees& coord) const {
			return	( longitude == coord.longitude ) &&
					( latitude == coord.latitude ) &&
					( radius == coord.radius );
		}

		inline double getLongitude() const { return longitude; }
		inline double getLatitude() const { return latitude; }
		inline double getRadius() const { return radius; }

		// distance non géodésique, en metres
		double distanceTo(const Coordonnees& coord) const;
		static inline double distance(const Coordonnees& coordA, const Coordonnees& coordB) {
			return coordA.distanceTo(coordB);
		}

	protected:
		double longitude;
		double latitude;
		double radius;

		double* toXYZ() const;

	friend class FluxLog; 
};

inline std::ostream& operator<<(std::ostream& os, const Coordonnees& co) {
	return os << "[" << co.getLongitude() << ", " << co.getLatitude() << "]";
}