#ifndef ROBOT_HPP
#define ROBOT_HPP

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
#include "Define.hpp"
#include "Position.hpp"

using namespace std;

class Robot{
	private :
		Position pos;
		int pv;	//points de vie du joueur
		int vit;	//vitesse du robot

		sf::Texture robot;
		sf::Sprite sprite_robot;
		sf::Vector2i anim;
		
	public :
		Robot(int i, int j); //CONSTRUCTEUR Avec Coordonnées
		Robot(Position* p); //CONSTRUCTEUR Aléatoire
		
		string toString();	//Affichage de la composition du robot
		sf::Sprite affiche(int x, int y); // Affichage SFML du robot
		void setMarche();
		
		bool emplacementLibre(Position pos, vector<Robot*> robs);
		void moveLeft();	//Déplacement
		void moveUp();
		void moveRight();
		void moveDown();
		
		const int& getPV() const;	//Accesseur PV
		void setPV(const int p);	//Mutateur PV
		
		const Position& getPos() const;	//Accesseur Position
		
}; 
#endif
