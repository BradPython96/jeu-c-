#include "Player.hpp"

// CONSTRUCTEUR
Player::Player(int i, int j, bool s, int min_taille_x_,int max_taille_x_,int min_taille_y_, int max_taille_y_){

	vit = VIT_JOUEUR;
	pos = Position(i, j, 0);
	recharge=clock();
	
	pv=PV_MAX_JOUEUR;
	min_taille_x = min_taille_x_;
	max_taille_x = max_taille_x_;
	min_taille_y = min_taille_y_;
	max_taille_y = max_taille_y_;
	
	enum Dir{Down, Right, Left, Up, UpRight, DownRight, DownLeft, UpLeft};
	sf::Vector2i anim(1, Down);
	
	sex=s;//initialisation du sex du joueur
	arms[0] = new Laser(sex);
	arms[1] = nullptr;
	arms[2] = nullptr;
	armCur=0;

	if (sex==true){
		if(!dead.loadFromFile("rob_girl_dead.png")){
			cout<<"Erreur du chargement de la rob morte"<<endl;
		}
	} else {
		if(!dead.loadFromFile("rob_boy_dead.png")){
			cout<<"Erreur du chargement du rob mort"<<endl;
		}
	}
	perso = arms[0]->texture();
	perso.setSmooth(true);
	sprite_perso.setTexture(perso);
	sprite_perso.setPosition(pos.getX()-LARGEUR_PERSO/2, pos.getY()-HAUTEUR_PERSO/2);

	if(!font.loadFromFile("Robot_Font.otf")){
		cout<<"Erreur chargement de la font"<<endl;
	}
	
	txt.setFont(font);
	txt.setCharacterSize(15);
	txt.setFillColor(sf::Color::Magenta);

}

bool Player::vivant() const{
	if (pv<=0){
		return false;
	} else {
		return true;
	}
}

// Affichage
string Player::toString(){
	string s;
	s="Un joueur se trouve à l'emplacement x = "+to_string(pos.getX())+", y = "+to_string(pos.getY())+", angle = "+to_string(pos.getAngle())+"\n";
	s+="Ce joueur possède "+to_string(pv)+"PV\n";
	if(NB_ARME!=0){
		s+="Il possède les armes suivantes :\n";
		int i;
		int const taille(NB_ARME);
		for(i=0; i<taille; i++){
			s+=arms[i]->toString();
		}
	}
	return s;
}


void Player::setMarche(){
	anim.x++;
	int const taille(perso.getSize().x);
	if(anim.x*LARGEUR_PERSO>=taille){
		anim.x=0;
	}
}

vector<sf::Sprite> Player::affiche(int xa, int ya, int tailleX, int tailleY, int xi, int yi){

	vector<sf::Sprite> liste;

	if(!this->vivant()){
		sprite_perso.setTexture(dead);
		sprite_perso.setTextureRect(sf::IntRect(0,0, LARGEUR_PERSO, HAUTEUR_PERSO));
		sprite_perso.setPosition(pos.getX()-xi-LARGEUR_PERSO/2, pos.getY()-yi-HAUTEUR_PERSO/2);

	} else {
		
		perso = arms[armCur]->texture();
		sprite_perso.setTexture(perso);
		int x;
		int y;
		sprite_perso.setTextureRect(sf::IntRect(anim.x*LARGEUR_PERSO,anim.y*HAUTEUR_PERSO,LARGEUR_PERSO,HAUTEUR_PERSO));
		if(xa<TAILLE/2){
			x=pos.getX()-LARGEUR_PERSO/2;
		} else if (xa>(tailleX-TAILLE/2)){
			x=pos.getX()-(tailleX-TAILLE)-LARGEUR_PERSO/2;
		} else {
			x=pos.getX()-(xa-TAILLE/2)-LARGEUR_PERSO/2;
		}
		
		if(ya<TAILLE/2){
			y=pos.getY()-HAUTEUR_PERSO/2;
		} else if (ya>(tailleY-TAILLE/2)){
			y=pos.getY()-(tailleY-TAILLE)-HAUTEUR_PERSO/2;
		} else {
			y=pos.getY()-(ya-TAILLE/2)-HAUTEUR_PERSO/2;
		}
		
		sprite_perso.setPosition(x,y);
	}
	int i;
	//Liste des sprite des missiles
	int const tailleM(miss.size());
	for(i=0;i<tailleM; i++){
		liste.push_back(miss[i]->affiche(xi, yi));
	}

	liste.push_back(sprite_perso);
	return liste;
}

sf::Text Player::info(int xa, int ya, int tailleX, int tailleY){

	if(this->vivant()){
		int x;
		int y;
		int i;

		if(xa<TAILLE/2){
			x=pos.getX()-LARGEUR_PERSO/2;
		} else if (xa>(tailleX-TAILLE/2)){
			x=pos.getX()-(tailleX-TAILLE)-LARGEUR_PERSO/2;
		} else {
			x=pos.getX()-(xa-TAILLE/2)-LARGEUR_PERSO/2;
		}
		
		if(ya<TAILLE/2){
			y=pos.getY()-HAUTEUR_PERSO/2;
		} else if (ya>(tailleY-TAILLE/2)){
			y=pos.getY()-(tailleY-TAILLE)-HAUTEUR_PERSO/2;
		} else {
			y=pos.getY()-(ya-TAILLE/2)-HAUTEUR_PERSO/2;
		}

		string s;
		s="   PV "+to_string(pv)+"\n";
		
		
		int const taille(NB_ARME);
		for(i=0; i<taille; i++){
			if(arms[i]!=nullptr){
				s+=arms[i]->toString();
			}
		}
		
		txt.setString(s);
		sf::Rect<float> f = txt.getLocalBounds();
		txt.setPosition(x,y-f.height);
	}


	
	return txt;

}


// DEPLACEMENT
void Player::moveLeft(int x_fen){
	enum Dir{Down, Right, Left, Up, UpRight, DownRight, DownLeft, UpLeft};
	anim.y=Left;
	if(pos.getX()-vit>min_taille_x && pos.getX()-vit > x_fen){
		pos.setX(pos.getX()-vit);
	}
	pos.setAngle(180);
}

void Player::moveDown(int y_fen){
	enum Dir{Down, Right, Left, Up, UpRight, DownRight, DownLeft, UpLeft};
	anim.y=Down;
	if(pos.getY()+vit<max_taille_y && pos.getY()+vit < y_fen + TAILLE){
		pos.setY(pos.getY()+vit);
	}
	pos.setAngle(270);
}

void Player::moveRight(int x_fen){
	enum Dir{Down, Right, Left, Up, UpRight, DownRight, DownLeft, UpLeft};
	anim.y=Right;
	if(pos.getX()+vit<max_taille_x && pos.getX()+vit < x_fen + TAILLE){
		pos.setX(pos.getX()+vit);
	} else {

	}
	pos.setAngle(0);
}

void Player::moveUp(int y_fen){
	enum Dir{Down, Right, Left, Up, UpRight, DownRight, DownLeft, UpLeft};
	anim.y=Up;
	if(pos.getY()-vit>min_taille_y && pos.getY()-vit>y_fen){
		pos.setY(pos.getY()-vit);
	}
	pos.setAngle(90);
}

void Player::moveUpRight(int x_fen,int y_fen){
	enum Dir{Down, Right, Left, Up, UpRight, DownRight, DownLeft, UpLeft};
	this->moveUp(y_fen);
	this->moveRight(x_fen);
	anim.y=UpRight;
	pos.setAngle(45);
}
void Player::moveDownRight(int x_fen,int y_fen){
	enum Dir{Down, Right, Left, Up, UpRight, DownRight, DownLeft, UpLeft};
	this->moveDown(y_fen);
	this->moveRight(x_fen);
	anim.y=DownRight;
	pos.setAngle(315);
}
void Player::moveDownLeft(int x_fen,int y_fen){
	enum Dir{Down, Right, Left, Up, UpRight, DownRight, DownLeft, UpLeft};
	this->moveDown(y_fen);
	this->moveLeft(x_fen);
	anim.y=DownLeft;
	pos.setAngle(225);
}
void Player::moveUpLeft(int x_fen,int y_fen){
	enum Dir{Down, Right, Left, Up, UpRight, DownRight, DownLeft, UpLeft};
	this->moveUp(y_fen);
	this->moveLeft(x_fen);
	anim.y=UpLeft;
	pos.setAngle(135);
}

void Player::addBazooka(){
	if(arms[1]==nullptr){
		arms[1]= new Bazooka(sex);
	} else {
		arms[1]->addMun();
	}
}

void Player::addGrenade(){
	if(arms[2]==nullptr){
		arms[2]= new Grenade(sex);
	} else {
		arms[2]->addMun();
	}
}

void Player::swapArme(){
	int x = armCur+1;
	if(NB_ARME==x){
		x=0;
	}
	while(arms[x]==nullptr){
		x++;
		if(NB_ARME==x){
			x=0;
		}
	}
	armCur=x;
}

void Player::tir(){
	if((clock()-recharge)/(double)CLOCKS_PER_SEC>CADENCE_TIR){	//si on a tirer depuis plus de 1 sec
		recharge = clock();
		miss.push_back(arms[armCur]->tirer(pos));	//on tire un missile
		if(arms[armCur]->getMunitions()<=0){	//on supprime l'arme si elle n'a plus de munition
			arms[armCur] = nullptr;
			armCur=0;
		}
	}
}

void Player::tourMissile(vector<Robot*> rob){
	int i;
	int const taille(miss.size());
	for(i=0; i<taille; i++){
		if(miss[i]->getCpt()==0){
			miss[i]->move(min_taille_x, min_taille_y, max_taille_x, max_taille_y);
			miss[i]->robotTouche(rob);
			if(miss[i]->getBoom()){
				miss[i]->explose(rob);
			}
		} else if(miss[i]->getCpt()==31){
			miss.erase(miss.begin()+i);
		}
	}
}


// PV ACC/MUT
const int& Player::getArmCur() const{
	return armCur;
}
const int& Player::getPV() const{
	return pv;
}		
void Player::setPV(const int p){
	pv = p;
}
const bool& Player::getSex() const{
	return sex;
}
const Position& Player::getPos() const{	//Accesseur Position
	return pos;
}
const vector<Missile*>& Player::getListMiss() const{
	return miss;
}