#ifndef ACCESSOIRE_HPP
#define ACCESSOIRE_HPP

#include <iostream>
#include <string>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "Define.hpp"
#include "Position.hpp"
#include "Player.hpp"
#include "Bazooka.hpp"
#include "Laser.hpp"
#include "Grenade.hpp"

using namespace std;

class Accessoire{
	private :
		Position pos;
		sf::Texture acc;
		sf::Sprite sprite_acc;
		
	public :
	
		Accessoire(int i, int j); //CONSTRUCTEUR Avec Coordonnées
		Accessoire(int xmin, int xmax, int ymin, int ymax); //CONSTRUCTEUR en fonction da la map
		
		string toString();	//affichage de l'emplacement de l'accessoire
		sf::Sprite affiche(); // Affichage SFML de l'accessoire
		
		void win(Player* p);
		
		const Position& getPos() const;	//Accesseur Position
}; 
#endif
