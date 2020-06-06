#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <ctime>
#include <SFML/Graphics.hpp>
#include "Define.hpp"
#include "Arme.hpp"
#include "Laser.hpp"
#include "Bazooka.hpp"
#include "Grenade.hpp"
#include "Position.hpp"
#include "Robot.hpp"

using namespace std;

class Player{
	private :
		Position pos;
		bool sex; //boy == false, girl==true
		Arme* arms[NB_ARME];	//liste des armes du joueur
		vector<Missile*> miss;
		int armCur;	//position dans la liste de l'arme courrante
		int pv;	//points de vie du joueur
		int vit; //la vitesse de déplacement du joueur

		int min_taille_x;	//Zone de déplacement du joueur
		int max_taille_x;
		int min_taille_y; 
		int max_taille_y;

		sf::Texture dead;	//Affichage du perso
		sf::Texture perso;
		sf::Text txt;
		sf::Font font;

		sf::Sprite sprite_perso;
		sf::Vector2i anim;

		clock_t recharge;	//constante de temps pour la recharge de l'arme
	
	public :
	
		Player(int i, int j, bool s, int min_taille_x_,int max_taille_x_,int min_taille_y_, int max_taille_y_); //CONSTRUCTEUR Avec Coordonnées
				
		string toString();	// Affichage de la composition du joueur
		vector<sf::Sprite> affiche(int xa, int ya, int tailleX, int tailleY, int xi, int yi);	// Affichage SFML du joueur
		sf::Text info(int xa, int ya, int tailleX, int tailleY);

		//Déplacement
		void moveLeft(int x_fen);	
		void moveUp(int y_fen);
		void moveRight(int x_fen);
		void moveDown(int y_fen);
		void moveUpRight(int x_fen,int y_fen);
		void moveDownRight(int x_fen,int y_fen);
		void moveDownLeft(int x_fen,int y_fen);
		void moveUpLeft(int x_fen,int y_fen);
		void setMarche();	//Gère l'animation de déplacement du joueur

		void addBazooka();	//Ajoute une arme à la liste
		void addGrenade();

		void swapArme();	//Change d'arme
		void tir();
		void tourMissile(vector<Robot*>);

		
		bool vivant() const; //Renvoie true si le joueur est en vie et false sinon
		const int& getArmCur() const;	//Accesseur la valeur de ArmCur
		const int& getPV() const;	//Accesseur PV
		const bool& getSex() const;	//Accesseur Sex
		const Position& getPos() const;	//Accesseur Position
		const vector<Missile*>& getListMiss() const;
		void setPV(const int p);	//Mutateur PV
		//Fonction pour test
		void setPos(int x, int y){
			pos.setX(x);
			pos.setY(y);
		}
		const Arme* getLaser() const{
			return arms[0];
		}
		const Arme* getBazooka() const{
			return arms[1];
		}
		const Arme* getGrenade() const{
			return arms[2];
		}
		
		~Player(){

			for(int i =0; i<NB_ARME; i++){
				free(arms[i]);
			}
			int const tailleM(miss.size());
			for(int i =0; i<tailleM; i++){
				free(miss[i]);
			}
		}
		
}; 
#endif
