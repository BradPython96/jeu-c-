#include "Bazooka.hpp"

// CONSTRUCTEUR
Bazooka :: Bazooka(){

	nbMunitions=NB_MUN_MAX_BAZOOKA;
	zoneDeDmg=ZONE_DE_DMG_BAZOOKA;
	dmg=DMG_BAZOOKA;

	if(!text.loadFromFile("rob_girl_bazooka.png")){
		cout<<"Erreur du chargement de la rob bazooka"<<endl;
	}
}

Bazooka :: Bazooka(bool sex){

	nbMunitions=NB_MUN_MAX_BAZOOKA;
	zoneDeDmg=ZONE_DE_DMG_BAZOOKA;
	dmg=DMG_BAZOOKA;

	if(sex){
		if(!text.loadFromFile("rob_girl_bazooka.png")){
			cout<<"Erreur du chargement de la rob bazooka"<<endl;
		}
	} else {
		if(!text.loadFromFile("rob_boy_bazooka.png")){
			cout<<"Erreur du chargement du rob bazooka"<<endl;
		}
	}
	
}
// Affichage
string Bazooka::toString(){
	return "- Un bazooka avec "+to_string(nbMunitions)+" munitions\n";
}

Missile* Bazooka::tirer(Position p){
	this->decrementMun();	//on décrémente la munition 
	return new MissileBazooka(p);
}