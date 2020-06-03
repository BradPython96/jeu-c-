#include "Map.hpp"

// CONSTRUCTEUR
Map::Map(bool sexP1, bool sexP2, int map){
	int moy_x;
	int moy_y;
	//Taille de la map
	Position* sp1=nullptr;
	Position* sp2=nullptr;
	Position* sp3=nullptr;
	Position* sp4=nullptr;
	switch(map){
		case 0: //map couloir
			min_taille_x = MIN_MAP_COULOIR_X;
			max_taille_x = MAX_MAP_COULOIR_X;
			min_taille_y = MIN_MAP_COULOIR_Y;
			max_taille_y = MAX_MAP_COULOIR_Y;
			moy_x = (min_taille_x + max_taille_x)/2;
			moy_y = (min_taille_y + max_taille_y)/2;
			sp1 = new Position(MIN_MAP_COULOIR_X,moy_y,0);
			sp2 = new Position(MAX_MAP_COULOIR_X,moy_y,0);
			spawn.push_back(sp1);
			spawn.push_back(sp2);
			break;

		case 1: //map arene
			min_taille_x = MIN_MAP_ARENE_X;
			max_taille_x = MAX_MAP_ARENE_X;
			min_taille_y = MIN_MAP_ARENE_Y;
			max_taille_y = MAX_MAP_ARENE_Y;
			moy_x = (min_taille_x + max_taille_x)/2;
			moy_y = (min_taille_y + max_taille_y)/2;
			sp1 = new Position(min_taille_x,moy_y,0);
			sp2 = new Position(max_taille_x,moy_y,0);
			sp3 = new Position(moy_x,min_taille_y,0);
			sp4 = new Position(moy_x,max_taille_y,0);
			spawn.push_back(sp1);
			spawn.push_back(sp2);
			spawn.push_back(sp3);
			spawn.push_back(sp4);
			break;
	}

	//Initialistaion des joueurs
	p1 = new Player(moy_x, moy_y, sexP1, min_taille_x,max_taille_x,min_taille_y, max_taille_y);
	p2 = new Player(moy_x+LARGEUR_PERSO, moy_y, sexP2, min_taille_x,max_taille_x,min_taille_y, max_taille_y);
	
	
	//Initialisation des accessoires
	for(int i=0; i<NB_ACCESSOIRES_INIT; i++){
		accs.push_back(new Accessoire(min_taille_x, max_taille_x, min_taille_y, max_taille_y));
	}

	
	//Lancement de la première vague de robot
	wait = clock();
	cptRob=0;
	cptVague=1;
	isVague = true;
	enAttente = false;

	//Lance les chronomètres
	apparAcc = clock();
	marcheRobot = clock();
}

Map::Map(){
		//Initialistaion des joueurs
	p1 = new Player(0, 0, true, min_taille_x,max_taille_x,min_taille_y, max_taille_y);
	p2 = new Player(0+LARGEUR_PERSO, 0, false, min_taille_x,max_taille_x,min_taille_y, max_taille_y);
	
}
///Affichage//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Renvoie la description complete de la map
string Map::toString(){
	string s="Cette carte contient :\n";
	int i;
	s+=p1->toString();
	s+=p2->toString();
	
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

//Affichage SFML des éléments de la map
vector<sf::Sprite> Map::listeSprite(int tailleX, int tailleY, int x, int y){	
	int i;
	vector<sf::Sprite> sp;

	//Centre de l'affichage
	int xa;
	int ya;
	if(p1->vivant() && p2->vivant()){
		xa = (p1->getPos().getX()+p2->getPos().getX())/2;
		ya = (p1->getPos().getY()+p2->getPos().getY())/2;
	} else if(!p1->vivant()){
		xa = p2->getPos().getX();
		ya = p2->getPos().getY();
	} else {
		xa = p1->getPos().getX();
		ya = p1->getPos().getY();
	}
	
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
	vector<sf::Sprite> mis0;
	vector<sf::Sprite> mis1;


	mis0 = p1->affiche(xa, ya, tailleX, tailleY, x, y);

	mis1 = p2->affiche(xa, ya, tailleX, tailleY, x, y);

	mis0.insert(mis0.end(), mis1.begin(), mis1.end());
	sp.insert(sp.end(), mis0.begin(), mis0.end());
	return sp;
}

//Affichage SFML des données au dessus de la tête de chacun des joueurs
vector<sf::Text> Map::infoPlayer(int tailleX, int tailleY){
	vector<sf::Text> liste;

	//Centre de l'affichage
	int xa;
	int ya;
	if(p1->vivant() && p2->vivant()){
		xa = (p1->getPos().getX()+p2->getPos().getX())/2;
		ya = (p1->getPos().getY()+p2->getPos().getY())/2;
	} else if(!p1->vivant()){
		xa = p2->getPos().getX();
		ya = p2->getPos().getY();
	} else {
		xa = p1->getPos().getX();
		ya = p1->getPos().getY();
	}
	if(p1->vivant()){
		liste.push_back(p1->info(xa, ya, tailleX, tailleY));
	}

	if(p2->vivant()){
		liste.push_back(p2->info(xa, ya, tailleX, tailleY));
	}	

	return liste;
}

//Accessoires/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Ajout  des accessoires sur la map
void Map::addAccs(){
	if((clock()-apparAcc)/(double)CLOCKS_PER_SEC>5){
		apparAcc=clock();
		accs.push_back(new Accessoire(min_taille_x, max_taille_x, min_taille_y, max_taille_y));
	}
}

//Récup Acc par les Players
void Map::recuperationAcc(){
	int i;
	sf::Text text;
	int const tailleA(accs.size());
	for (i=0; i<tailleA; i++){
		if(sqrt(p1->getPos().getX() - accs[i]->getPos().getX()) + sqrt(p1->getPos().getY() - accs[i]->getPos().getY()) <= 10){
			accs[i]->win(p1);
			accs.erase(accs.begin()+i);
		} else if (sqrt(p2->getPos().getX() - accs[i]->getPos().getX()) + sqrt(p2->getPos().getY() - accs[i]->getPos().getY()) <= 10){
			accs[i]->win(p2);
			accs.erase(accs.begin()+i);
		}
	}
}

//Robots////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Ajout des robots sur la map par groupe de 9 autour des points de spawn
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

//Détecte si l'emplacement désiré pour placer le robot est libre
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

//Cherche le prochain point de spawn libre ou faire apparaitre les nouveau robots de la vague
void Map::spawnRobot(){
	if (cptRob>=NB_ROB_INIT*pow(1.5, cptVague)){	//On vérifie si la vague est complète
		isVague=false;
		cptRob=0;
	} else {	//Si des robots doivent encore apparaitre dans cette vague
		int const sizeSpa(spawn.size());
		int const sizeRob(robs.size());
		int r;
		int x_min;
		int x_max;
		int y_min;
		int y_max;
		int x_spa;
		int y_spa;
		bool free;

		for(r=0; r<sizeSpa; r++){
			x_spa = spawn[r]->getX();
			y_spa = spawn[r]->getY();
			x_min = spawn[r]->getX()-TAILLE_ROBOT*1.5;//On délimite la zone de spawn
			x_max = spawn[r]->getX()+TAILLE_ROBOT*1.5;
			y_min = spawn[r]->getY()-TAILLE_ROBOT*1.5;
			y_max = spawn[r]->getY()+TAILLE_ROBOT*1.5;
			free=true;
			int i;
			for(i=0; i<sizeRob; i++){	//On vérifie que les 9 emplacements soit disponible
				free*=emplacementLibre(robs[i], Position(x_spa-TAILLE_ROBOT, y_spa-TAILLE_ROBOT, 0));
				free*=emplacementLibre(robs[i], Position(x_spa-TAILLE_ROBOT, y_spa, 0));
				free*=emplacementLibre(robs[i], Position(x_spa-TAILLE_ROBOT, y_spa+TAILLE_ROBOT, 0));

				free*=emplacementLibre(robs[i], Position(x_spa, y_spa-TAILLE_ROBOT, 0));
				free*=emplacementLibre(robs[i], Position(x_spa, y_spa, 0));
				free*=emplacementLibre(robs[i], Position(x_spa, y_spa+TAILLE_ROBOT, 0));

				free*=emplacementLibre(robs[i], Position(x_spa+TAILLE_ROBOT, y_spa-TAILLE_ROBOT, 0));
				free*=emplacementLibre(robs[i], Position(x_spa+TAILLE_ROBOT, y_spa, 0));
				free*=emplacementLibre(robs[i], Position(x_spa+TAILLE_ROBOT, y_spa+TAILLE_ROBOT, 0));
				
				if(!free){	//si l'un des emplacement est occupé on chage de spawn
					break;
				}
			}

			if(free){	//si tous les emplacement sont libres on garde le spawn
				break;
			}
		}
		if(free){	//si on a trouvé un spawn disponible on y place les robots
			this->addRobot(x_min, x_max, y_min, y_max);
		}
		
	}
}

//Gère le déplacement des robots sur la map
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


//Gère le tour complet des robots (Rassemblr les méthodes ci-dessus)
void Map::tourRobot(){
	if(isVague){
		spawnRobot();
	} else {
		if(robs.size()==0 && !enAttente){		//si il n'
			cout<<"remise de l'horloge a 0"<<endl;
			wait=clock();
			enAttente=true;
		}		
		if(enAttente && (clock()-wait)/(double)CLOCKS_PER_SEC>5){
			isVague=true;
			enAttente=false;
			cptVague++;
		}
	}

	if((clock()-marcheRobot)/(double)CLOCKS_PER_SEC>0.01){
		marcheRobot= clock();
		int i;
		int const tailleR(robs.size());

		for (i=0; i<tailleR; i++){
			Position p;
			if(p1->vivant() && p2->vivant()){	//si les 2 joueurs sont en vit
				//on cherche le joueur le plus proche
				double d0 = p1->getPos().distance(robs[i]->getPos());
				double d1 = p2->getPos().distance(robs[i]->getPos());
				
				if(d0<d1){	//si P1 est plus proche
					//on vérifie si il est a côté du joueur
					if (d0<=LARGEUR_PERSO/2){
						p1->setPV(p1->getPV()-DMG_ROBOT);
					} else {	//sinon on se rapproche
						this->deplacementRobot(robs[i], p1);
					}

				} else {	//si P2 est plus proche
					if (d1<=LARGEUR_PERSO/2){
						p2->setPV(p2->getPV()-DMG_ROBOT);
					} else {
						this->deplacementRobot(robs[i], p2);
					}
				}
			} else if (!p1->vivant()){	//si P1 est mort
				double d1 = p2->getPos().distance(robs[i]->getPos());
				if (d1<=LARGEUR_PERSO/2){
						p2->setPV(p2->getPV()-DMG_ROBOT);
					} else {
						this->deplacementRobot(robs[i], p2);
					}
			} else {	//Si le P2 est mort
				double d0 = p1->getPos().distance(robs[i]->getPos());
				if (d0<=LARGEUR_PERSO/2){
					p1->setPV(p1->getPV()-DMG_ROBOT);
				} else {
					this->deplacementRobot(robs[i], p1);
				}
			}
		}
	}
}

//Missiles///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Map::gestionMissile(){
	p1->tourMissile(robs);	//Les joueurs font avancer leurs missiles respectif
	p2->tourMissile(robs);
	int i;
	int taille(robs.size());
	for(i=0;i<taille; i++){	//Si l'un des robots n'a plus de vie on le retire de la map
		if(robs[i]->getPV()<=0){
			robs.erase(robs.begin()+i);
			taille--;	//on fait attention de ne pas sortir de la liste
			i--;
		}
	}
}

//GameOver//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Map::gameOver(){
	if (p1->vivant()){
		return false;
	} else if (p2->vivant()){
		return false;
	} else {
		return true;
	}
}

//Accesseurs/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Player* Map::getP1(){
	return p1;
}
Player* Map::getP2(){
	return p2;
}

const int& Map::getMinTailleX() const{
	return min_taille_x;
}

const int& Map::getMaxTailleX() const{
	return max_taille_x;
}

const int& Map::getMinTailleY() const{
	return min_taille_y;
}

const int& Map::getMaxTailleY() const{
	return max_taille_y;
}

const int& Map::getCptVague() const{
	return cptVague;
}