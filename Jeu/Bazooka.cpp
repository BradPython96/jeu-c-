#include "Bazooka.hpp"

// CONSTRUCTEUR
Bazooka :: Bazooka(){
			
	nbMunitions=NB_MUN_MAX_BAZOOKA;
	portee=PORTEE_BAZOOKA;
	zoneDeDmg=ZONE_DE_DMG_BAZOOKA;
	dmg=DMG_BAZOOKA;
}

// Affichage
string Bazooka::toString(){
	return "- Un bazooka avec "+to_string(nbMunitions)+" munitions\n";
}
