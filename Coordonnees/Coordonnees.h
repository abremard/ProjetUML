#pragma once
#include <stdlib.h>

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

		Coordonnees& operator =(const Coordonnees& coord) {
			longitude = coord.getLongitude();
			latitude = coord.latitude;
			radius = coord.radius;
			return *this;
		}

		inline double getLongitude() const { return longitude; }
		inline double getLatitude() const { return latitude; }
		inline double getRadius() const { return radius; }

		// distance non géodésique
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

			double longitueRadian = longitude * M_PI / 180.0;
			double latitudeRadian = latitude * M_PI / 180.0;
			double cosLatitue = cos(latitudeRadian);

			double x = sin(latitudeRadian);
			double y = cos(longitueRadian) * cosLatitue;
			double z = sin(longitueRadian) * cosLatitue;

			double* xyz = new double[3];
			xyz[0] = x * radius;
			xyz[1] = y * radius;
			xyz[2] = z * radius;
			return xyz;
		}
};
