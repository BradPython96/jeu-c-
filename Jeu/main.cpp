#include "Game.hpp"
#include <string>
#include <ctime>
#include <SFML/Graphics.hpp>

int main(){
	
	srand (time(NULL));
	Game* g = new Game();
	g->lancement();
	
	return 0;
}
