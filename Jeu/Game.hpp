#ifndef GAME_HPP
#define GAME_HPP
#include <ctime>
#include <unistd.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Map.hpp"

class Game{
	
	private :
		sf::RenderWindow window;
		sf::Texture fond;
		sf::Sprite sprite_fond;

		sf::Texture gameOver;
		sf::Sprite sprite_gameOver;
		Map m;
		int taille_x;//Taille de la map
		int taille_y;
		
		
	public :
	
		Game(){			//CONSTRUCTEUR
			cout<<"2"<<endl;
			window.create(sf::VideoMode(TAILLE,TAILLE), "ROBS VS ROBOTS");
			window.setPosition(sf::Vector2i(10, 50));
			if (!gameOver.loadFromFile("Game_Over.png", sf::IntRect(0,0,TAILLE,TAILLE))){
				cout<<"Erreur de chargement du game over"<<endl;
			}
			sprite_gameOver.setTexture(gameOver);
		}	


		
		void lancement();
		void gestion();
		void tour();
		void actualise();
		void deplacement();

		

};
#endif
