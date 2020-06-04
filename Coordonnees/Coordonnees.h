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

		// longitude entre -180° et 180°, latitude entre -90° et 90°, rayon positif
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
		double distanceTo(const Coordonnees& coord) const {
			double* pointA = toXYZ();
			double* pointB = coord.toXYZ();

			pointA[0] -= pointB[0];
			pointA[1] -= pointB[1];
			pointA[2] -= pointB[2];

			delete[] pointB;

			double squaredDistance = pointA[0] * pointA[0] + pointA[1] * pointA[1] + pointA[2] * pointA[2];

			delete[] pointA;

			return sqrt(squaredDistance);
		}
		static inline double distance(const Coordonnees& coordA, const Coordonnees& coordB) {
			return coordA.distanceTo(coordB);
		}

	protected:
		double longitude;
		double latitude;
		double radius;

		double* toXYZ() const {
			/*
			         x
					 |
			         |_____ z
					 /
					/
				   y
			*/

			const double longitueRadian = longitude * M_PI / 180.0;
			const double latitudeRadian = latitude * M_PI / 180.0;
			const double cosLatitudeRadius = cos(latitudeRadian) * radius;

			double* xyz = new double[3];
			xyz[0] = sin(latitudeRadian) * radius;
			xyz[1] = cos(longitueRadian) * cosLatitudeRadius;
			xyz[2] = sin(longitueRadian) * cosLatitudeRadius;
			return xyz;
		}
};

inline std::ostream& operator<<(std::ostream& os, const Coordonnees& co) {
	return os << "[" << co.getLongitude() << ", " << co.getLatitude() << "]";
}