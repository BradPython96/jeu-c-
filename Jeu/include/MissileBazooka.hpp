#ifndef MISSILEBAZOOKA_HPP
#define MISSILEBAZOOKA_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Position.hpp"
#include "Missile.hpp"

using namespace std;

class MissileBazooka : public Missile {

    public :
        MissileBazooka(Position p);   //CONSTRUCTEUR
        
        void move(int, int, int, int);  //Déplacement du missile
        sf::Sprite affiche(int, int);   //Affiche le missile avant ET pendant l'explosion
        void explose(vector<Robot*>);   //Applique les DMG dans la zone d'explosion
        void robotTouche(vector<Robot*> robots);



};
#endif