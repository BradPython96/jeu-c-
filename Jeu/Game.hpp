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
		Map m;
		int taille_x;//Taille de la map
		int taille_y;
		int x_fen;
		int y_fen;
		
	public :
	
		Game(){			//CONSTRUCTEUR
			cout<<"2"<<endl;
			window.create(sf::VideoMode(TAILLE,TAILLE), "ROBS VS ROBOTS");
			window.setPosition(sf::Vector2i(10, 50));	
		}	


		
		void lancement();
		void gestion();
		void tour();
		void actualise();
		void deplacement();

		

};
#endif
