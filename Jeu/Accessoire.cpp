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
		
	sprite_acc.setPosition(pos.getX()-x+TAILLE_ACCESSOIRE/8, pos.getY()-y+TAILLE_ACCESSOIRE/4);
	
	return sprite_acc;
}

sf::Text Accessoire::win(Player* p){
	int i = rand()%3;
	sf::Text text;
	switch(i){
		case 0:
			p->setPV(PV_MAX_JOUEUR);
			text.setString("Vie est totalement restaurée");
			break;
		case 1:
			p->addArme(new Bazooka(p->getSex()));
			text.setString("Vous avez trouvé un bazooka");
			break;
		case 2:
			p->addArme(new Grenade(p->getSex()));
			text.setString("Vous avez trouvé une grenade");
			break;
		default:
			break;
	}
	text.setCharacterSize(20);
	text.setPosition(10.f,10.f);
	text.setFillColor(sf::Color::White);
	return text;
}


const Position& Accessoire::getPos() const{	//Accesseur Position
	return pos;
}
