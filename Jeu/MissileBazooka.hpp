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

        void move(int, int, int, int);
        sf::Sprite affiche(int, int);
        void explose(vector<Robot*>);

        void robotTouche(vector<Robot*>);
        



};
#endif