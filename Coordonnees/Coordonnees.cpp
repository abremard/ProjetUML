#include "Coordonnees.h"

double Coordonnees::distanceTo(const Coordonnees& coord) const {
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

double* Coordonnees::toXYZ() const {
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