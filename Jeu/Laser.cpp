#include "Laser.hpp"

// CONSTRUCTEUR
Laser :: Laser(){
			
	nbMunitions=NB_MUN_MAX_LASER;
	portee=PORTEE_LASER;
	zoneDeDmg=ZONE_DE_DMG_LASER;
	dmg=DMG_LASER;
}

// Affichage
string Laser::toString(){
	return "- Un pistolet laser avec "+to_string(nbMunitions)+" munitions\n";
}
