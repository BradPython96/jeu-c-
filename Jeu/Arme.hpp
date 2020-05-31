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
        ~Arme(){}

		const int& getMunitions() const {   //Accesseur nbr de munitions
            return nbMunitions;
        }
        
        const int& getZoneDeDmg() const {   //Accesseur zone de dmg
            return zoneDeDmg;
        }
        const int& getDmg() const { //Accesseur dommage
            return dmg;
        }
        void decrementMun(){    //Décrémente le nombre de munitions
            nbMunitions --;
        }
        
        const sf::Texture texture() const{  //Texture du peronnage lié à l'arme qu'il porte
            return text;
        }

        virtual Missile* tirer(Position p)=0;   //Apelle décrémente mun et retourne le missile associé à l'arme
        virtual string toString()=0;    //Décrit l'arme et le nombre de munitions

        
};
#endif
