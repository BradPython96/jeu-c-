#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include <vector>
#include <string>
#include <cstddef>
#include <ctime>
#include <unistd.h>
#include <SFML/Graphics.hpp>
#include "Define.hpp"
#include "Player.hpp"
#include "Robot.hpp"
#include "Accessoire.hpp"

using namespace std;

class Map {

	private :
		vector <Player*> plys;	//liste de joueurs dans le jeu
		vector <Robot*> robs;	//liste de robots dans le jeu
		vector <Accessoire*> accs;	//liste d'accessoires
		vector <Position*> spawn;	//liste des positions d'apparition

		int min_taille_x;	//imension de la map
		int max_taille_x;	 
		int min_taille_y;	 
		int max_taille_y;
		
	public :
		Map(bool sexP1, bool sexP2, int map); //CONSTRUCTEUR
		Map();
		
		string toString();	// Affiche la composition de la map
		
		vector<sf::Sprite> listeSprite(int tailleX, int tailleY, int x, int y); //Donne l'affichage de tous les éléments de la map
		void actualise(sf::RenderWindow* window); // Dessine la map en sfml
		
		void addRobot(); // Ajoute un robot à la map
		void addAccs(); // Ajoute un accessoire à la map
		
		void recuperationAcc();		//récupération des accessoire dans un tour
		void tourRobot();	//les actions du robot dans un tour
		bool gameOver();

		Player* getP1();
		Player* getP2();

		int getMinTailleX();

		int getMaxTailleX();

		int getMinTailleY();

		int getMaxTailleY();
            			
};
#endif
