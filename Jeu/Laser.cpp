#include "Laser.hpp"

// CONSTRUCTEUR
Laser :: Laser(){
	
	nbMunMax = NB_MUN_MAX_LASER;
	nbMunitions=NB_MUN_MAX_LASER;
	zoneDeDmg=ZONE_DE_DMG_LASER;
	dmg=DMG_LASER;

	if(!text.loadFromFile("rob_girl_laser.png")){
		cout<<"Erreur du chargement de la rob laser"<<endl;
	}
}

Laser :: Laser(bool sex){

	nbMunMax = NB_MUN_MAX_LASER;	
	nbMunitions=NB_MUN_MAX_LASER;
	zoneDeDmg=ZONE_DE_DMG_LASER;
	dmg=DMG_LASER;

	if(sex){
		if(!text.loadFromFile("rob_girl_laser.png")){
			cout<<"Erreur du chargement de la rob laser"<<endl;
		}
	} else {
		if(!text.loadFromFile("rob_boy_laser.png")){
			cout<<"Erreur du chargement du rob laser"<<endl;
		}
	}
	
}

// Affichage
string Laser::toString(){
	return "Pistolet laser Infini\n";
}


Missile* Laser::tirer(Position p){
	return new MissileLaser(p);
}