#pragma once
#include <stdlib.h>
#include <string>

#define _USE_MATH_DEFINES
#include <math.h>

#include "Coordonnees.h"



using namespace std;

class Capteur
{
	public:
		Capteur(const string& idCapteur, const Coordonnees& coordonneesCapteur, const string& descriptionCapteur = "") 
			: id(idCapteur), coordonnees(coordonneesCapteur), description(descriptionCapteur)
		{}

		inline string getId() const { return id; }
		inline Coordonnees getCoordonnes() const { return coordonnees; }
		inline string getDescription() const { return description; }

	protected:
		string id;
		Coordonnees coordonnees;
		string description;
};
