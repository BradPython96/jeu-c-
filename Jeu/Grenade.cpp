#include "Grenade.hpp"

// CONSTRUCTEUR
Grenade :: Grenade(){
			
	nbMunitions=NB_MUN_MAX_GRENADE;
	portee=PORTEE_GRENADE;
	zoneDeDmg=ZONE_DE_DMG_GRENADE;
	dmg=DMG_GRENADE;
}

// Affichage
string Grenade::toString(){
	return "- Une grenade avec "+to_string(nbMunitions)+" munitions\n";
}
