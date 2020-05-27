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
        sf::Sprite affiche(int, int);
        void explose(vector<Robot*>);

        void robotTouche(vector<Robot*>);
        



};
#endif