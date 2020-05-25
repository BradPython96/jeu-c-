#include "Accessoire.hpp"

// CONSTRUCTEUR
Accessoire :: Accessoire(int i, int j){	// Avec Coordonnées
	pos = Position(i, j, 0);
	
	if(!acc.loadFromFile("accessoire.png")){
		cout<<"Erreur du chargement de l'accessoire"<<endl;
	}
	acc.setSmooth(true);
	sprite_acc.setTexture(acc);
	sprite_acc.setPosition(pos.getX()-TAILLE_ACCESSOIRE/2, pos.getY()-TAILLE_ACCESSOIRE/2);
}
Accessoire :: Accessoire(int xmin, int xmax, int ymin, int ymax){		// Création en fonction de la map
	int i = rand()%(xmax-xmin)+xmin;
	int j = rand()%(ymax-ymin)+ymin;
	pos = Position(i, j, 0);
	
	if(!acc.loadFromFile("accessoire.png")){
		cout<<"Erreur du chargement de l'accessoire"<<endl;
	}
	acc.setSmooth(true);
	sprite_acc.setTexture(acc);
	sprite_acc.setPosition(pos.getX()-TAILLE_ACCESSOIRE/2, pos.getY()-TAILLE_ACCESSOIRE/2);
}


// Affichage
string Accessoire::toString(){
	return "Un accessoire se trouve à l'emplacement x = "+to_string(pos.getX())+", y = "+to_string(pos.getY())+".\n";
}

sf::Sprite Accessoire::affiche(int x, int y){
		
	sprite_acc.setPosition(pos.getX()-x+3*TAILLE_ACCESSOIRE/2, pos.getY()-y+TAILLE_ACCESSOIRE/2);
	
	return sprite_acc;
}

void Accessoire::win(Player* p){
	int i = rand()%4;
	switch(i){
		case 0:
			p->setPV(PV_MAX_JOUEUR);
			cout<<"Votre vie est totalement restaurée"<<endl;
			break;
		case 1:
			p->addArme(new Laser());
			cout<<"Vous avez trouvé un pistolet laser"<<endl;
			break;
		case 2:
			p->addArme(new Bazooka());
			cout<<"Vous avez trouvé un bazooka"<<endl;
			break;
		case 3:
			p->addArme(new Grenade());
			cout<<"Vous avez trouvé une grenade"<<endl;
			break;
	}
}


const Position& Accessoire::getPos() const{	//Accesseur Position
	return pos;
}
