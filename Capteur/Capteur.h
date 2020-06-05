#pragma once
#include <stdlib.h>
#include <string>

#include "../Coordonnees/Coordonnees.h"



using namespace std;

class Capteur
{
	public:
		Capteur(const string& idCapteur = "", const Coordonnees& coordonneesCapteur = Coordonnees(), const string& descriptionCapteur = "") 
			: id(idCapteur), coordonnees(coordonneesCapteur), description(descriptionCapteur)
		{}

		inline string getId() const { return id; }
		inline Coordonnees getCoordonnes() const { return coordonnees; }
		inline string getDescription() const { return description; }

		inline Coordonnees& operator =(const Capteur& c) {
			id = c.id;
			coordonnees = c.coordonnees;
			description = c.description;
			return *this;
		}

	protected:
		string id;
		Coordonnees coordonnees;
		string description;
	friend class FluxLog; 
};
