#include "Map.hpp"

// CONSTRUCTEUR
Map::Map(bool sexP1, bool sexP2, int map){
	int moy_x;
	int moy_y;
	//Taille de la map
	Position* p1;
	Position* p2;
	Position* p3;
	Position* p4;
	switch(map){
		case 0: //map couloir
			min_taille_x = MIN_MAP_COULOIR_X;
			max_taille_x = MAX_MAP_COULOIR_X;
			min_taille_y = MIN_MAP_COULOIR_Y;
			max_taille_y = MAX_MAP_COULOIR_Y;
			moy_x = (min_taille_x + max_taille_x)/2;
			moy_y = (min_taille_y + max_taille_y)/2;
			p1 = new Position(MIN_MAP_COULOIR_X,moy_y,0);
			p2 = new Position(MAX_MAP_COULOIR_X,moy_y,0);
			spawn.push_back(p1);
			spawn.push_back(p2);
			break;

		case 1: //map arene
			min_taille_x = MIN_MAP_ARENE_X;
			max_taille_x = MAX_MAP_ARENE_X;
			min_taille_y = MIN_MAP_ARENE_Y;
			max_taille_y = MAX_MAP_ARENE_Y;
			moy_x = (min_taille_x + max_taille_x)/2;
			moy_y = (min_taille_y + max_taille_y)/2;
			p1 = new Position(min_taille_x,moy_y,0);
			p2 = new Position(max_taille_x,moy_y,0);
			p3 = new Position(moy_x,min_taille_y,0);
			p4 = new Position(moy_x,max_taille_y,0);
			spawn.push_back(p1);
			spawn.push_back(p2);
			spawn.push_back(p3);
			spawn.push_back(p4);
			break;
	}

	//Initialistaion des joueurs
	plys.push_back(new Player(moy_x, moy_y, sexP1, min_taille_x,max_taille_x,min_taille_y, max_taille_y));
	plys.push_back(new Player(moy_x+LARGEUR_PERSO, moy_y, sexP2, min_taille_x,max_taille_x,min_taille_y, max_taille_y));
		
    //Initialisation des accessoires
	for(int i=0; i<NB_ACCESSOIRES_INIT; i++){
		accs.push_back(new Accessoire(min_taille_x, max_taille_x, min_taille_y, max_taille_y));
	}

	
	//Initialisation des timers
	wait = clock();
	cptRob=0;
	robVague=18;
	isVague = true;	//le jeu commence sur une vague de robot

	spawnRobot();//Init robot

	apparAcc = clock();
	
}
Map::Map(){
		
	//Initialistaion des joueurs
	plys.push_back(new Player(TAILLE/2, TAILLE/2, true, 0, TAILLE, 0,TAILLE));
	plys.push_back(new Player(TAILLE/2+1, TAILLE/2, false, 0, TAILLE, 0,  TAILLE));
	
	
}



// Affichage
string Map::toString(){
	string s="Cette carte contient :\n";
	int i;
	if(plys.size()!=0){
		int const tailleP(plys.size());
		for (i=0; i<tailleP; i++){
			s+=plys[i]->toString();
		}
	}
	if(robs.size()!=0){
		int const tailleR(robs.size());
		for (i=0; i<tailleR; i++){
			s+=robs[i]->toString();
		}
	}
	int const tailleA(accs.size());
	for (i=0; i<tailleA; i++){
		s+=accs[i]->toString();
	}
	return s;
}

vector<sf::Sprite> Map::listeSprite(int tailleX, int tailleY, int x, int y){
	int i;
	vector<sf::Sprite> sp;

	//Centre de l'affichage
	int xa = (plys[0]->getPos().getX()+plys[1]->getPos().getX())/2;
	int ya = (plys[0]->getPos().getY()+plys[1]->getPos().getY())/2;
	
	//Liste des accessoires
	if(accs.size()!=0){
		int const tailleA(accs.size());
		for (i=0; i<tailleA; i++){
			sp.push_back(accs[i]->affiche(x, y));
		}
	}	
	
	
	//Liste de robot
	if(robs.size()!=0){
		int const tailleR(robs.size());
		for(i=0; i<tailleR; i++){
				sp.push_back(robs[i]->affiche(x,y));
		}
	}
	
	//Liste perso
	
	vector<sf::Sprite> mis0 = plys[0]->affiche(xa, ya, tailleX, tailleY, x, y);
	vector<sf::Sprite> mis1 = plys[1]->affiche(xa, ya, tailleX, tailleY, x, y);
	mis0.insert(mis0.end(), mis1.begin(), mis1.end());
	sp.insert(sp.end(), mis0.begin(), mis0.end());

	return sp;
}

//Ajout  d'Element sur la map

void Map::addAccs(){
	
	accs.push_back(new Accessoire(min_taille_x, max_taille_x, min_taille_y, max_taille_y));
}


//Récup Acc par les P
void Map::recuperationAcc(){
	int i;
	int const tailleA(accs.size());
	for (i=0; i<tailleA; i++){
		if(sqrt(plys[0]->getPos().getX() - accs[i]->getPos().getX()) + sqrt(plys[0]->getPos().getY() - accs[i]->getPos().getY()) <= 10){
			accs[i]->win(plys[0]);
			accs.erase(accs.begin()+i);
		} else if (sqrt(plys[1]->getPos().getX() - accs[i]->getPos().getX()) + sqrt(plys[1]->getPos().getY() - accs[i]->getPos().getY()) <= 10){
			accs[i]->win(plys[1]);
			accs.erase(accs.begin()+i);
		}
	}
}

void Map::addRobot(int x_min, int x_max, int y_min, int y_max){
	
	robs.push_back(new Robot(x_min+TAILLE_ROBOT/2, y_min+TAILLE_ROBOT/2));
	robs.push_back(new Robot(x_min+TAILLE_ROBOT*1.5, y_min+TAILLE_ROBOT/2));
	robs.push_back(new Robot(x_max-TAILLE_ROBOT/2, y_min+TAILLE_ROBOT/2));

	robs.push_back(new Robot(x_min+TAILLE_ROBOT/2, y_min+TAILLE_ROBOT*1.5));
	robs.push_back(new Robot(x_min+TAILLE_ROBOT*1.5, y_min+TAILLE_ROBOT*1.5));
	robs.push_back(new Robot(x_max-TAILLE_ROBOT/2, y_min+TAILLE_ROBOT*1.5));
	
	robs.push_back(new Robot(x_min+TAILLE_ROBOT/2, y_max-TAILLE_ROBOT/2));
	robs.push_back(new Robot(x_min+TAILLE_ROBOT*1.5, y_max-TAILLE_ROBOT/2));
	robs.push_back(new Robot(x_max-TAILLE_ROBOT/2, y_max-TAILLE_ROBOT/2));

	cptRob+=9;
}


void Map::spawnRobot(){
	if (cptRob>=robVague){
		isVague=false;
		cptRob=0;
		robVague*=1.5;
	} else if (isVague){
		int const sizeSpa(spawn.size());
		int const sizeRob(robs.size());
		int r;
		int x_min;//On délimite la zone de spawn
		int x_max;
		int y_min;
		int y_max;
		
		for(r=0; r<sizeSpa; r++){
			x_min = spawn[r]->getX()-TAILLE_ROBOT*1.5;//On délimite la zone de spawn
			x_max = spawn[r]->getX()+TAILLE_ROBOT*1.5;
			y_min = spawn[r]->getY()-TAILLE_ROBOT*1.5;
			y_max = spawn[r]->getY()+TAILLE_ROBOT*1.5;
			bool free=true;
			int i;
			for(i=0; i<sizeRob; i++){
				if((robs[i]->getPos().getX()<x_max && robs[i]->getPos().getX()>x_min) && (robs[i]->getPos().getY()<y_max && robs[i]->getPos().getY()>y_min)){
					free=false;
					break;
				}
			}

			if(free){
				break;
			}
		}
		this->addRobot(x_min, x_max, y_min, y_max);
	}
}

bool Map::emplacementLibre(Robot *rob, Position pos){
	int i;
	int const tailleR(robs.size());
	//cout<<"Position désiré : x="<<pos.getX()<<", y="<<pos.getY()<<endl;
	for(i=0; i<tailleR; i++){
		if (robs[i]!=rob && pos.distance(robs[i]->getPos())<TAILLE_ROBOT/2){
			return false;
		}
	}
	return true;
}

void Map::deplacementRobot(Robot *r, Player *p){
	Position pos = p->getPos();	//on stock l'emplacement du joueur
	bool moved=false;
	int newX = r->getPos().getX(); 
	int newY = r->getPos().getY();
	//on se rapproche du joueur
	if(pos.getX()<r->getPos().getX()){
		newX = r->getPos().getX()-VIT_ROBOT;
		if(emplacementLibre(r, Position(newX, newY, 0))){	//on vérifie si il peut aller a gauche
			r->moveLeft();
			moved=true;
		}
	} else if (pos.getX()>r->getPos().getX()){
		newX = r->getPos().getX()+VIT_ROBOT;
		if(emplacementLibre(r, Position(newX, newY, 0))){	//on vérifie si il peut aller a droite
			r->moveRight();
			moved=true;
		}
	}
	if(pos.getY()<r->getPos().getY()){
		newY = r->getPos().getY()-VIT_ROBOT;
		if(emplacementLibre(r, Position(newX, newY, 0))){	//on vérifie si il peut aller en haut
			r->moveUp();
			moved=true;
		}
	} else if (pos.getY()>r->getPos().getY()){
		newY = r->getPos().getY()+VIT_ROBOT;
		if(emplacementLibre(r, Position(newX, newY, 0))){	//on vérifie si il peut aller en bas
			r->moveDown();
			moved=true;
		}
	}
	
	if(!moved){	//si il n'a pas bougé on essaie de le faire aller dans une autre direction
		if(newY == r->getPos().getY()){	//si il voulait aller à droite ou a gauche
			if(emplacementLibre(r, Position(newX, newY-TAILLE_ROBOT, 0))){	//on vérifie si il peut aller en bas
				r->moveUp();
				moved=true;
			} else if (emplacementLibre(r, Position(newX, newY+TAILLE_ROBOT, 0))){	//ou en haut
				r->moveDown();
				moved=true;
			}
		} else {	//si il voulait aller en haut ou en bas
			if(emplacementLibre(r, Position(newX-TAILLE_ROBOT, newY, 0))){	//on vérifie si il peut aller a gauche
				r->moveLeft();
				moved=true;
			} else if (emplacementLibre(r, Position(newX+TAILLE_ROBOT, newY, 0))){	//ou a droite
				r->moveRight();
				moved=true;
			}
		}
	}
	if(moved){
		r->setMarche();
	}

}


//Attaque des robot
void Map::tourRobot(){
	if(robs.size()==0 && !isVague){	
		cout<<"remise de l'horloge a 0"<<endl;
		wait=clock();
	}
		
	if((clock()-wait)/(double)CLOCKS_PER_SEC>5 && !isVague){
		isVague=true;
	}
	
	spawnRobot();

	int i;
	int const tailleR(robs.size());

	for (i=0; i<tailleR; i++){
		Position p;
		if(plys[0]->vivant() && plys[1]->vivant()){	//si les 2 joueurs sont en vit
			//on cherche le joueur le plus proche
			double d0 = plys[0]->getPos().distance(robs[i]->getPos());
			double d1 = plys[1]->getPos().distance(robs[i]->getPos());
			
			if(d0<d1){	//si P1 est plus proche
				//on vérifie si il est a côté du joueur
				if (d0<=LARGEUR_PERSO/2){
					plys[0]->setPV(plys[0]->getPV()-DMG_ROBOT);
				} else {	//sinon on se rapproche
					this->deplacementRobot(robs[i], plys[0]);
				}

			} else {	//si P2 est plus proche
				if (d1<=LARGEUR_PERSO/2){
					plys[1]->setPV(plys[1]->getPV()-DMG_ROBOT);
				} else {
					this->deplacementRobot(robs[i], plys[1]);
				}
			}
		} else if (!plys[0]->vivant()){	//si P1 est mort
			double d1 = plys[1]->getPos().distance(robs[i]->getPos());
			if (d1<=LARGEUR_PERSO/2){
					plys[1]->setPV(plys[1]->getPV()-DMG_ROBOT);
				} else {
					this->deplacementRobot(robs[i], plys[1]);
				}
		} else {	//Si le P2 est mort
			double d0 = plys[0]->getPos().distance(robs[i]->getPos());
			if (d0<=LARGEUR_PERSO/2){
				plys[0]->setPV(plys[0]->getPV()-DMG_ROBOT);
			} else {
				this->deplacementRobot(robs[i], plys[0]);
			}
		}
	}
	sleep(0.01);
}




void Map::gestionMissile(){
	plys[0]->tourMissile(robs);
	plys[1]->tourMissile(robs);
	int i;
	for(i=0;i<robs.size(); i++){
		if(robs[i]->getPV()<=0){
			robs.erase(robs.begin()+i);
		}
	}
}

bool Map::gameOver(){
	if (plys[0]->vivant()){
		return false;
	} else if (plys[1]->vivant()){
		return false;
	} else {
		return true;
	}
}

//Récupérer P1 et P2
Player* Map::getP1(){
	return plys[0];
}
Player* Map::getP2(){
	return plys[1];
}

int Map::getMinTailleX(){
	return min_taille_x;
}

int Map::getMaxTailleX(){
	return max_taille_x;
}

int Map::getMinTailleY(){
	return min_taille_y;
}

int Map::getMaxTailleY(){
	return max_taille_y;
}