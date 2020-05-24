#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "Define.hpp"
#include "Arme.hpp"
#include "Laser.hpp"
#include "Position.hpp"

using namespace std;

class Player{
	private :
		Position pos;
		bool sex; //boy == false, girl==true
		vector<Arme*> arms;	//liste des armes du joueur
		int armCur;	//position dans la liste de l'arme courrante
		int pv;	//points de vie du joueur
		int min_taille_x;
		int max_taille_x;
		int min_taille_y; 
		int max_taille_y;
		sf::Texture perso;
		sf::Sprite sprite_perso;
		sf::Vector2i anim;
	
	public :
	
		Player(int i, int j, bool s, int min_taille_x_,int max_taille_x_,int min_taille_y_, int max_taille_y_); //CONSTRUCTEUR Avec Coordonnées
		
		bool vivant() const; //Renvoie true si le joueur est en vie et false sinon
		
		string toString();	// Affichage de la composition du joueur
		sf::Sprite affiche(int xa, int ya, int tailleX, int tailleY);	// Affichage SFML du joueur
		
		//Déplacement
		void moveLeft();	
		void moveUp();
		void moveRight();
		void moveDown();
		void moveUpRight();
		void moveDownRight();
		void moveDownLeft();
		void moveUpLeft();
		
		void addArme(Arme* a);
		
		const int& getPV() const;	//Accesseur PV
		void setPV(const int p);	//Mutateur PV
		void setMarche();
		
		
		const Position& getPos() const;	//Accesseur Position
		
}; 
#endif
