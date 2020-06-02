#ifndef GAME_HPP
#define GAME_HPP
#include <ctime>
#include <unistd.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Map.hpp"

class Game{
	
	private :
		sf::RenderWindow window;// Fenetre du jeu
		sf::Texture fond;	//Affichage du fond
		sf::Sprite sprite_fond;

		sf::Texture gameOver;	//Affichage du Game Over
		sf::Sprite sprite_gameOver;

		Map *m;	//Map de déplacemeent

		int taille_x;//Taille de la map
		int taille_y;
		int x_fen;
		int y_fen;

		sf::Text txtVag;
		sf::Font font_3;
		
	public :
	
		Game(){			//CONSTRUCTEUR
			window.create(sf::VideoMode(TAILLE,TAILLE), "ROBS VS ROBOTS");
			window.setPosition(sf::Vector2i(10, 50));
			if (!gameOver.loadFromFile("Game_Over.png", sf::IntRect(0,0,TAILLE,TAILLE))){
				cout<<"Erreur de chargement du game over"<<endl;
			}

			if(!font_3.loadFromFile("Robot_Font_2.otf")){
				cout<<"Erreur chargement de la font"<<endl;
			}
			
			txtVag.setFont(font_3);
			//txtVag.setString("Essai 2");
			txtVag.setCharacterSize(25);
			txtVag.setFillColor(sf::Color::Magenta);
		}	

		~Game(){
			delete m;
		}
		
		void lancement();
		void gestion();
		void tour(sf::Event event);
		void actualise();

		void deplacement();	//Déplace le joueur en fonction des événements
		void action(sf::Event event);	//Réalise les actions du joueur en fonction des événements

		

};
#endif
