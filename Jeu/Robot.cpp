#include "Robot.hpp"

// CONSTRUCTEURS

Robot :: Robot(int i, int j){
	pos = Position(i, j, 0);
	pv=PV_MAX_ROBOT;
	
	enum Dir{Down, Left, Right, Up};
	sf::Vector2i anim(1, Down);
	
	if(!robot.loadFromFile("robot.png")){
		cout<<"Erreur du chargement du robot"<<endl;
	}
	robot.setSmooth(true);
	sprite_robot.setTexture(robot);
	sprite_robot.setPosition(pos.getX()-TAILLE_ROBOT/2, pos.getY()-TAILLE_ROBOT/2);
}
Robot :: Robot(Position* p){
	pv=PV_MAX_ROBOT;
	
	pos = *p;

	enum Dir{Down, Left, Right, Up};
	sf::Vector2i anim(1, Down);
	
	if(!robot.loadFromFile("robot.png")){
		cout<<"Erreur du chargement du robot"<<endl;
	}
	robot.setSmooth(true);
	sprite_robot.setTexture(robot);
	sprite_robot.setPosition(pos.getX()-TAILLE_ROBOT/2, pos.getY()-TAILLE_ROBOT/2);

}

// Affichage
string Robot::toString(){
	return "Un robot se trouve à l'emplacement x = "+to_string(pos.getX())+", y = "+to_string(pos.getY())+", angle = "+ to_string(pos.getAngle())+",  avec "+to_string(pv)+"PV.\n";
}	

sf::Sprite Robot::affiche(int x, int y){
	
	sprite_robot.setTextureRect(sf::IntRect(anim.x*TAILLE_ROBOT,anim.y*TAILLE_ROBOT,TAILLE_ROBOT,TAILLE_ROBOT));
	
	sprite_robot.setPosition(pos.getX()-x-TAILLE_ROBOT/2, pos.getY()-y-TAILLE_ROBOT/2);
	
	return sprite_robot;
}

void Robot::setMarche(){
	anim.x++;
	if(anim.x*TAILLE_ROBOT>=robot.getSize().x){
		anim.x=0;
	}
}

// DEPLACEMENT
void Robot::moveLeft(){
	enum Dir{Down, Left, Right, Up};
	anim.y = Left;
	pos.setX(pos.getX()-1);
}

void Robot::moveDown(){
	enum Dir{Down, Left, Right, Up};
	anim.y=Down;
	pos.setY(pos.getY()+1);
}

void Robot::moveRight(){
	enum Dir{Down, Left, Right, Up};
	anim.y=Right;
	pos.setX(pos.getX()+1);
}

void Robot::moveUp(){
	enum Dir{Down, Left, Right, Up};
	anim.y=Up;
	pos.setY(pos.getY()-1);
}

// PV ACC/MUT
const int& Robot::getPV() const{
	return pv;
}		
void Robot::setPV(const int p){
	pv = p;
}
const Position& Robot::getPos() const{	//Accesseur Position
	return pos;
}
