#ifndef GRENADE_HPP
#define GRENADE_HPP

#include <iostream>
#include "Define.hpp"
#include "Arme.hpp"
#include "MissileGrenade.hpp"

using namespace std;

class Grenade : public Arme{
	
	public :
	
		Grenade(); // CONSTRUCTEUR par défaut
		Grenade(bool sex);
		string toString(); // Affichage de la composition d'une grenade
		Missile* tirer(Position p);
		
};
#endif
