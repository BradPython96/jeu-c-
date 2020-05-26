#include "Game.hpp"



void Game::lancement(){
	
	//Initialisation de la fenêtre
	sf::RenderWindow menu(sf::VideoMode(TAILLE,TAILLE), "Menu d'accueil");
	menu.setPosition(sf::Vector2i(10, 50));
	//sf::RectangleShape page(sf::Vector2f(taille, taille));
    //page.setFillColor(sf::Color::Red);
    sf::Texture accueil;
    sf::Sprite sprite_accueil;
    bool p1;
    bool p2;
    bool m1 = false;
	bool m2 = false;
    if (!accueil.loadFromFile("Pre_Menu.png", sf::IntRect(0,0,TAILLE,TAILLE))){
			cout<<"Erreur de chargement du pré menu"<<endl;
	}


	//Ouverture de la fenêtre
    while (menu.isOpen()){
		
		//Recherche d'évenement
        sf::Event event;
        while (menu.pollEvent(event)){
			
			//Fermeture de la fenêtre
			if(event.type==sf::Event::Closed){
				menu.close();
			}
			
			//Choix des personnages
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){

				if (!accueil.loadFromFile("Menu_perso1.png", sf::IntRect(0,0,TAILLE,TAILLE))){
					cout<<"Erreur de chargement du menu perso 1"<<endl;
				}
				
				m1 = true;
			}

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) && m1 && !m2){
				p1=true;
				if (!accueil.loadFromFile("Menu_perso2.png", sf::IntRect(0,0,TAILLE,TAILLE))){
					cout<<"Erreur de chargement du menu perso 2"<<endl;
				}
				m1 = false;
				m2 = true;

				
			}else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) && m1 && !m2){
				p1=false;
				if (!accueil.loadFromFile("Menu_perso2.png", sf::IntRect(0,0,TAILLE,TAILLE))){
					cout<<"Erreur de chargement du menu perso 2"<<endl;
				}
				m1 = false;
				m2 = true;				
				
			}

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) && !m1 && m2){
				p2=true;
				if (!accueil.loadFromFile("Menu_map.png", sf::IntRect(0,0,TAILLE,TAILLE))){
					cout<<"Erreur de chargement du menu map"<<endl;
				}

				m2 = false;
				
			}else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num4) &&m2){
				p2=false;
				if (!accueil.loadFromFile("Menu_map.png", sf::IntRect(0,0,TAILLE,TAILLE))){
					cout<<"Erreur de chargement du menu map"<<endl;
				}
				m2 = false;
			}

				//Initialistion de la texture de fond
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num5) && !m1 && !m2){
				if (!fond.loadFromFile("Map_couloir.png")){
					cout<<"Erreur de chargement de la map couloir"<<endl;
				}
				fond.setSmooth(true);
				sprite_fond.setTexture(fond);
				menu.close();
				taille_x = TAILLE_MAP_COULOIR_X;
				taille_y = TAILLE_MAP_COULOIR_Y;
				m = Map(p1,p2,0);
				
			} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6) && !m1 && !m2){
				if (!fond.loadFromFile("fond_caillou.jpg")){
					cout<<"Erreur de chargement de la map arene"<<endl;
				}
				fond.setSmooth(true);
				sprite_fond.setTexture(fond);
				menu.close();
				taille_x = TAILLE_MAP_ARENE_X;
				taille_y = TAILLE_MAP_ARENE_Y;
				m = Map(p1,p2,1);
			}
			
		}
		accueil.setSmooth(true);
		sprite_accueil.setTexture(accueil);
		window.clear();
		menu.draw(sprite_accueil);
		menu.display();
		
	}
	
	this->gestion();
}
	
	

// Gestion jeu
void Game:: gestion(){
    
	//Ouverture de la Map
	while (window.isOpen()){
		
	
		//Recherche d'évenement
        sf::Event event;
        while (window.pollEvent(event)){
			//Fermeture de la fenêtre
			if(event.type==sf::Event::Closed){
				window.close();
			}
			
			this->tour();
			
			/*
            //Si la fenêtre n'est plus active
            if (event.type == sf::Event::LostFocus){
				myGame.pause();
			}
			
			//Si la fenêtre est de nouveau active
			if (event.type == sf::Event::GainedFocus){
				myGame.resume();
             }*/
             		
		}
		window.clear();

		m.tourRobot();
		this->actualise();	//Chargement des éléments sur la map
		
    }
    
}

void Game::tour(){

	this->deplacement();
	this->action();
}


//Actualisation de la map
void Game::actualise(){

	if (m.gameOver()){
		window.draw(sprite_gameOver);
	} else {
		//On centre la map sur les joueurs
		int x = (m.getP1()->getPos().getX()+m.getP2()->getPos().getX())/2-TAILLE/2;
		if (x<0){x = 0;}
		if (x>taille_x - TAILLE){x = taille_x - TAILLE;}
		x_fen = x;

		int y = (m.getP1()->getPos().getY()+m.getP2()->getPos().getY())/2-TAILLE/2;
		if (y<0){y = 0;}
		if (y>taille_y - TAILLE){y = taille_y - TAILLE;}
		y_fen = y;

		sprite_fond.setTextureRect(sf::IntRect(x_fen,y_fen,TAILLE,TAILLE));
		window.draw(sprite_fond);
	
		vector<sf::Sprite> sp = m.listeSprite(taille_x, taille_y, x, y);
	

    	int i;
    	//Affichage des éléments
    		int const tailleS(sp.size());
    		for (i=0; i<tailleS; i++){
				window.draw(sp[i]);
			}
	}
	window.display();
}


//Déplacement des joueurs
void Game::deplacement(){
	
	Player* P1=m.getP1();
	Player* P2=m.getP2();

		//Déplacement P1
	if(P1->vivant()){

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
			P1->moveUpRight(x_fen, y_fen);
			m.getP1()->setMarche();
		} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
			P1->moveDownRight(x_fen, y_fen);
			m.getP1()->setMarche();
		} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
			P1->moveDownLeft(x_fen, y_fen);
			m.getP1()->setMarche();
		} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
			P1->moveUpLeft(x_fen, y_fen);
			m.getP1()->setMarche();
		} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
			P1->moveRight(x_fen);
			m.getP1()->setMarche();
		} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
			P1->moveDown(y_fen);
			m.getP1()->setMarche();
		} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
			P1->moveLeft(x_fen);
			m.getP1()->setMarche();
		} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
			P1->moveUp(y_fen);
			m.getP1()->setMarche();
		}
	}
	//Déplacement P2
	if(P2->vivant()){

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
			P2->moveUpRight(x_fen, y_fen);
			m.getP2()->setMarche();
		} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
			P2->moveDownRight(x_fen, y_fen);
			m.getP2()->setMarche();
		} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
			P2->moveDownLeft(x_fen, y_fen);
			m.getP2()->setMarche();
		} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
			P2->moveUpLeft(x_fen, y_fen);
			m.getP2()->setMarche();
		} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
			P2->moveRight(x_fen);
			m.getP2()->setMarche();
		} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
			P2->moveDown(y_fen);
			m.getP2()->setMarche();
		} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
			P2->moveLeft(x_fen);
			m.getP2()->setMarche();
		} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
			P2->moveUp(y_fen);
			m.getP2()->setMarche();
		}
	}
}

void Game::action(){

	Player* P1=m.getP1();
	Player* P2=m.getP2();

	//CHANGEMENT ARME P1
	if(P1->vivant()){

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::E)){
			P1->swapArme();
		}
	}
	//CHANGEMENT ARME P2
	if(P2->vivant()){

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)){
			P2->swapArme();
		}
	}

	//RECUPERATION DES ACCESSOIRES
	m.recuperationAcc();
}