#ifndef GRENADE_HPP
#define GRENADE_HPP

#include <iostream>
#include "Define.hpp"
#include "Arme.hpp"

using namespace std;

class Grenade : public Arme{
	
	public :
	
		Grenade(); // CONSTRUCTEUR par défaut
		string toString(); // Affichage de la composition d'une grenade
		
};
#endif
