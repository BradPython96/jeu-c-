#ifndef BAZOOKA_HPP
#define BAZOOKA_HPP

#include <iostream>
#include "Define.hpp"
#include "Arme.hpp"

using namespace std;

class Bazooka : public Arme{

	public :
	
		Bazooka(); // CONSTRUCTEUR par défaut
		Bazooka(bool sex);
		string toString(); // Affichage de la composition d'un bazooka
		
};
#endif
