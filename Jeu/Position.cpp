#include "Position.hpp"

// CONSTRUCTEUR
Position :: Position(int i, int j, int a){ //Avec coordonnées
	x=i;
	y=j;
	angle=a;
}
Position :: Position(){
	x=0;
	y=0;
	angle=0;
}
		
		
// OPERATEUR
bool Position::operator==(const Position pos) const {  //opérateur ==
	return (x==pos.x && y==pos.y);
}

double Position::distance(const Position pos) const {
	return sqrt(pow(this->getX()-pos.getX(), 2)+pow(this->getY()-pos.getY(), 2));
}


// ACCESSEURS		
const int& Position::getX() const{
	return x;
}
const int& Position::getY() const{
	return y;
}
const int& Position::getAngle() const{
	return angle;
}

// MUTATEURS		
void Position::setX(const int i){
	x=i;
}
void Position::setY(const int j){
	y=j;
}
void Position::setAngle(const int a){
	angle=a;
}
