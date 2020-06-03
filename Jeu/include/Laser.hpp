#ifndef LASER_HPP
#define LASER_HPP

#include <iostream>
#include "Define.hpp"
#include "Arme.hpp"
#include "MissileLaser.hpp"

using namespace std;

class Laser : public Arme{
	
	public :
	
		Laser(); // CONSTRUCTEUR par défaut
		Laser(bool sex);
		string toString(); // Affichage de la composition d'un pistolet laser
		Missile* tirer(Position p);
		
};
#endif
