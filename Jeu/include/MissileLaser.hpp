#ifndef MISSILELASER_HPP
#define MISSILELASER_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Position.hpp"
#include "Missile.hpp"

using namespace std;

class MissileLaser : public Missile {

    public :
        MissileLaser(Position p);   //CONSTRUCTEUR

        void move(int, int, int, int);
        sf::Sprite affiche(int, int);   //Affiche le missile avant ET pendant l'explosion
        void explose(vector<Robot*>);   //Applique les DMG dans la zone d'explosion
        void robotTouche(vector<Robot*> robots);


};
#endif