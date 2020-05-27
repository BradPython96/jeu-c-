#ifndef ARME_HPP
#define ARME_HPP

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "Missile.hpp"

using namespace std;

class Arme{
	protected :
		int nbMunitions;
        int zoneDeDmg;
        int dmg;
        sf::Texture text;
        
	public :
		Arme(){}
		const int& getMunitions() const {
            return nbMunitions;
        }
        
        int& getMunitions(){
            return nbMunitions;
        }
        
        const int& getZoneDeDmg() const {
            return zoneDeDmg;
        }
        const int& getDmg() const {
            return dmg;
        }
        void decrementMun(){
            nbMunitions --;
        }
        
        const sf::Texture texture() const{
            return text;
        }

        virtual Missile* tirer(Position p)=0;
        virtual string toString()=0;
	
};
#endif
