#ifndef ARME_HPP
#define ARME_HPP

#include <iostream>
#include <string>

using namespace std;

class Arme{
	protected :
		int nbMunitions;
		int portee;
        int zoneDeDmg;
        int dmg;
        
	public :
		Arme(){}
		const int& getMunitions() const {
            return nbMunitions;
        }
        
        int& getMunitions(){
            return nbMunitions;
        }
        
        const int& getPortee() const {
            return portee;
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
        
        virtual string toString()=0;
	
};
#endif
