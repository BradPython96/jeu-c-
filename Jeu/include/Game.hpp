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
		sf::Font font;
		
	public :
	
		Game(){			//CONSTRUCTEUR
			//Création de la fenetre
			window.create(sf::VideoMode(TAILLE,TAILLE), "ROBS VS ROBOTS");
			window.setPosition(sf::Vector2i(10, 50));

			//Gestion du Game Over
			if (!gameOver.loadFromFile("Game_Over.png", sf::IntRect(0,0,TAILLE,TAILLE))){
				cout<<"Erreur de chargement du game over"<<endl;
			}
			gameOver.setSmooth(true);
			sprite_gameOver.setTexture(gameOver);
			
			//Text -> Affichage du numéro de la vague
			if(!font.loadFromFile("Robot_Font_2.otf")){
				cout<<"Erreur chargement de la font"<<endl;
			}			
			txtVag.setFont(font);
			txtVag.setCharacterSize(25);
			txtVag.setFillColor(sf::Color::Magenta);

			m=nullptr;
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
