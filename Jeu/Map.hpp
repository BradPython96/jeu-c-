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
		Player* p1;	//Joueur 1
		Player* p2;	//Joueur 2
		vector <Robot*> robs;	//liste de robots dans le jeu
		vector <Accessoire*> accs;	//liste d'accessoires
		vector <Position*> spawn;	//liste des positions d'apparition

		int min_taille_x;	//Dimension de la map
		int max_taille_x;	 
		int min_taille_y;	 
		int max_taille_y;

		int cptRob;		//cpt de robot créé par vague
		int cptVague;	//cpt de vague (plus il est élevé plus il y a de robots)
		bool isVague;	//true si on est dans une vague false sinon
		bool enAttente;	//true si on esr dans une période d'attente entre 2 vagues false sinon
		clock_t wait;	//Chronomètre le temps d'attente entre chaque vague

		clock_t apparAcc;	//Chronomètre l'apparition des accessoires
		clock_t marcheRobot;	//Chronomètre la marche des robots

	public :
		Map(bool sexP1, bool sexP2, int map); //CONSTRUCTEUR
		Map();
		~Map(){	//DESTRUCTEUR
			delete p1;
			delete p2;
			int i;
			int const tailleR(robs.size());
			for(i=0;i<tailleR; i++){
				delete robs[i];
			}

			int const tailleA(accs.size());
			for(i=0;i<tailleA; i++){
				delete accs[i];
			}

			int const tailleS(spawn.size());
			for(i=0;i<tailleS; i++){
				delete spawn[i];
			}
		}

		//Affichage
		string toString();	// Affiche la composition de la map
		//SFML
		vector<sf::Sprite> listeSprite(int tailleX, int tailleY, int x, int y); //Donne l'affichage de tous les éléments de la map
		void actualise(sf::RenderWindow* window); // Dessine la map en sfml
		vector<sf::Text> infoPlayer(int tailleX, int tailleY);	//Info sur les têtes des joueurs SFML
		
		//Gestion des accessoires
		void addAccs(); // Ajoute un accessoire à la map
		void recuperationAcc();		//récupération des accessoire dans un tour

		//Gestion des robots
		void addRobot(int, int, int, int);
		bool emplacementLibre(Robot *rob, Position pos);
		void spawnRobot();		
		void deplacementRobot(Robot *r, Player *p);
		void tourRobot();	//les actions du robot dans un tour

		//Missiles
		void gestionMissile();

		//Game Over
		bool gameOver();

		//Getteur des joueurs
		Player* getP1();
		Player* getP2();
		//Accesseurs
		const int& getMinTailleX() const;
		const int& getMaxTailleX() const;
		const int& getMinTailleY() const;
		const int& getMaxTailleY() const;
		const int& getCptVague() const;
        
};
#endif
