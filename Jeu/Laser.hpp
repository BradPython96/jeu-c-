#ifndef LASER_HPP
#define LASER_HPP

#include <iostream>
#include "Define.hpp"
#include "Arme.hpp"

using namespace std;

class Laser : public Arme{
	
	public :
	
		Laser(); // CONSTRUCTEUR par défaut
		string toString(); // Affichage de la composition d'un pistolet laser
		
};
#endif
