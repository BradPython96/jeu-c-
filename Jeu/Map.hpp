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
		Player* p1;
		Player* p2;
		vector <Robot*> robs;	//liste de robots dans le jeu
		vector <Accessoire*> accs;	//liste d'accessoires
		vector <Position*> spawn;	//liste des positions d'apparition

		int min_taille_x;	//imension de la map
		int max_taille_x;	 
		int min_taille_y;	 
		int max_taille_y;

		int cptRob;	//cpt de robot par vague
		int cptVague;	//nombre de robot qui doivent apparaitre par vague
		clock_t wait;	//temps d'attente entre chaque vague
		bool isVague;	//true si on est dans une vague false sinon
		bool enAttente;
		clock_t apparAcc;	//apparition des accessoires

	public :
		Map(bool sexP1, bool sexP2, int map); //CONSTRUCTEUR
		Map(){}	//Constructeur par défault
		~Map(){	//Destructeur
			delete p1;
			delete p2;
			int const tailleR(robs.size());	//Libération de la mémoire pour les robots
			for(int i=0; i<tailleR; i++){
				free(robs[i]);
			}

			int const tailleA(accs.size());	//Libération de la mémoire pour les accessoires
			for(int i=0; i<tailleA; i++){
				free(accs[i]);
			}

			int const tailleS(spawn.size());	//Libération de la mémoire des position de spawn
			for(int i=0; i<tailleS; i++){
				free(spawn[i]);
			}

		}
		string toString();	// Affiche la composition de la map
		
		vector<sf::Sprite> listeSprite(int tailleX, int tailleY, int x, int y); //Donne l'affichage de tous les éléments de la map
		void actualise(sf::RenderWindow* window); // Dessine la map en sfml
		vector<sf::Text> infoPlayer(int tailleX, int tailleY);
		
		void addRobot(); // Ajoute un robot à la map
		void addAccs(); // Ajoute un accessoire à la map
		
		void recuperationAcc();		//récupération des accessoire dans un tour


		void addRobot(int, int, int, int);
		void spawnRobot();
		bool emplacementLibre(Robot *rob, Position pos);
		void deplacementRobot(Robot *r, Player *p);
		void tourRobot();	//les actions du robot dans un tour
		void gestionMissile();
		bool gameOver();

		Player* getP1();
		Player* getP2();

		int getMinTailleX();

		int getMaxTailleX();

		int getMinTailleY();

		int getMaxTailleY();

		const int& getCptVague() const;
        /*			
		~Map(){
			int i;
			int const tailleA(accs.size());
			for(i =0; i<tailleA; i++){
				delete accs[i];
			}
			int const tailleP(plys.size());
			for(i =0; i<tailleP; i++){
				delete plys[i];
			}
			int const tailleR(robs.size());
			for(i =0; i<tailleR; i++){
				delete robs[i];
			}
			int const tailleS(spawn.size());
			for(i =0; i<tailleS; i++){
				delete spawn[i];
			}
		}*/
};
#endif
