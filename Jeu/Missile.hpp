#ifndef MISSILE_HPP
#define MISSILE_HPP

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Position.hpp"
#include "Robot.hpp"

using namespace std;

class Missile{
    protected :
        Position pos;
        bool boom;  //false si le missile n'a pas encore explosé true 
        int cpt;    //compteur de l'explosion
        sf::Texture miss;
        sf::Sprite sprite_miss;

    public :
        Missile(){}

        const sf::Sprite& getSprite() const{    //Accesseur sprite_miss
            return sprite_miss;
        }
        const bool& getBoom() const{    //Accesseur boom
            return boom;
        }
        const int& getCpt() const{    //Accesseur boom
            return cpt;
        }

        virtual void explose(vector<Robot*>)=0;
        virtual sf::Sprite affiche(int, int)=0;
        virtual void move(int, int, int, int)=0;
        virtual void robotTouche(vector<Robot*> robots)=0;



};
#endif