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
		int vit; //la vitesse de déplacement du joueur

		int min_taille_x;	//Zone de déplacement du joueur
		int max_taille_x;
		int min_taille_y; 
		int max_taille_y;

		sf::Texture dead;	//Affichage du perso
		sf::Texture perso;

		sf::Sprite sprite_perso;
		sf::Vector2i anim;
	
	public :
	
		Player(int i, int j, bool s, int min_taille_x_,int max_taille_x_,int min_taille_y_, int max_taille_y_); //CONSTRUCTEUR Avec Coordonnées
		
		bool vivant() const; //Renvoie true si le joueur est en vie et false sinon
		
		string toString();	// Affichage de la composition du joueur
		sf::Sprite affiche(int xa, int ya, int tailleX, int tailleY);	// Affichage SFML du joueur
		
		//Déplacement
		void moveLeft(int x_fen);	
		void moveUp(int y_fen);
		void moveRight(int x_fen);
		void moveDown(int y_fen);
		void moveUpRight(int x_fen,int y_fen);
		void moveDownRight(int x_fen,int y_fen);
		void moveDownLeft(int x_fen,int y_fen);
		void moveUpLeft(int x_fen,int y_fen);
		
		void addArme(Arme* a);	//Ajoute une arme à la liste
		void swapArme();	//Change d'arme
		
		const int& getPV() const;	//Accesseur PV
		void setPV(const int p);	//Mutateur PV
		const bool& getSex() const;	//Accesseur Sex

		void setMarche();	//Gère l'animation de déplacement du joueur
		
		
		const Position& getPos() const;	//Accesseur Position
		
}; 
#endif
