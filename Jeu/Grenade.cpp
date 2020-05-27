#include "Grenade.hpp"

// CONSTRUCTEUR
Grenade :: Grenade(){
			
	nbMunitions=NB_MUN_MAX_GRENADE;
	zoneDeDmg=ZONE_DE_DMG_GRENADE;
	dmg=DMG_GRENADE;

	if(!text.loadFromFile("rob_girl_grenade.png")){
		cout<<"Erreur du chargement de la rob grenade"<<endl;
	}
}

Grenade :: Grenade(bool sex){
			
	nbMunitions=NB_MUN_MAX_GRENADE;
	zoneDeDmg=ZONE_DE_DMG_GRENADE;
	dmg=DMG_GRENADE;

	if(sex){
		if(!text.loadFromFile("rob_girl_grenade.png")){
			cout<<"Erreur du chargement de la rob grenade"<<endl;
		}
	} else {
		if(!text.loadFromFile("rob_boy_grenade.png")){
			cout<<"Erreur du chargement du rob grenade"<<endl;
		}
	}
}


// Affichage
string Grenade::toString(){
	return "- Une grenade avec "+to_string(nbMunitions)+" munitions\n";
}


Missile* Grenade::tirer(Position p){
	return new MissileGrenade(p);
}