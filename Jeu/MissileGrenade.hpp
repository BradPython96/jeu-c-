#ifndef MISSILEGRENADE_HPP
#define MISSILEGRENADE_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Position.hpp"
#include "Missile.hpp"

using namespace std;

class MissileGrenade : public Missile {
    private :
        Position init;  //position initiale de la grenade
        int cptG;
    public :
        MissileGrenade(Position p);   //CONSTRUCTEUR

        void move(int, int, int, int);  //Déplacement du missile
        sf::Sprite affiche(int, int);
        void explose(vector<Robot*>);
        void robotTouche(vector<Robot*> robots);



};
#endif