#ifndef POSITION_HPP
#define POSITION_HPP

#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

class Position {
	private :
		int x;
		int y;
		int angle;
		
	public :
		Position(int i, int j, int a); // CONSTRUCTEUR Avec Coordonnées
		Position();	// CONSTRUCTEUR Aléatoire
		
		bool operator==(const Position pos) const; // Opérateur==
		double distance(const Position pos) const; //Donne la distance entre deux positions
		
		const int& getX() const;	// Accesseur : x
		const int& getY() const;	// Accesseur : y
		const int& getAngle() const;// Accesseur : angle
		
		void setX(const int i);		// Mutateur : x
		void setY(const int j);		// Mutateur : y
		void setAngle(const int a); // Mutateur : angle
};
#endif	
