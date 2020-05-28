#include "MissileGrenade.hpp"

MissileGrenade::MissileGrenade(Position p){
    cpt=0;
    cptG=0;
    boom = false;
    pos = p;
    init = p;

    if(!miss.loadFromFile("Tirs.png")){
        cout<<"Erreur dans le chargement de la texture de tir"<<endl;
    }

    miss.setSmooth(true);
    sprite_miss.setTexture(miss);
    sprite_miss.setTextureRect(sf::IntRect(2*LARGEUR_BAZOOKA, 0, LARGEUR_EXPLOSION, HAUTEUR_EXPLOSION_1));
}



void MissileGrenade::move(int min_taille_x, int min_taille_y, int max_taille_x, int max_taille_y){
    
    if(init.distance(pos)>PORTEE_GRENADE || pos.getX()==max_taille_x || pos.getX()==min_taille_x || pos.getY()==min_taille_y || pos.getY()==max_taille_y){  //on vérifie que la grenda n'a pas atteint sa portée
        cptG++;
        if(cptG==50){
            boom=true;
        }
    } else {
        int ang= pos.getAngle();
        int newX = pos.getX();
        int newY = pos.getY();

        
        switch (ang){
            case 0:
                newX=pos.getX()+VIT_BAZOOKA;
                if(newX>=max_taille_x){
                    newX=max_taille_x;
                }
                break;
            case 45:
                newX=pos.getX()+VIT_BAZOOKA/sqrt(2);
                newY=pos.getY()-VIT_BAZOOKA/sqrt(2);
                if(newX>=max_taille_x){
                    newX=max_taille_x;
                }
                if(newY<=min_taille_y){
                    newY=min_taille_y;
                }
                break;
            case 90:
                newY=pos.getY()-VIT_BAZOOKA;
                if(newY<=min_taille_y){
                    newY=min_taille_y;
                }
                break;
            case 135:
                newX=pos.getX()-VIT_BAZOOKA/sqrt(2);
                newY=pos.getY()-VIT_BAZOOKA/sqrt(2);
                if(newX<=min_taille_x){
                    newX=min_taille_x;
                }
                if(newY<=min_taille_y){
                    newY=min_taille_y;
                }
                break;
            case 180:
                newX=pos.getX()-VIT_BAZOOKA;
                if(newX<=min_taille_x){
                    newX=min_taille_x;
                }
                break;
            case 225:
                newX=pos.getX()-VIT_BAZOOKA/sqrt(2);
                newY=pos.getY()+VIT_BAZOOKA/sqrt(2);
                if(newX<=min_taille_x){
                    newX=min_taille_x;
                }
                if(newY>=max_taille_y){
                    newY=max_taille_y;
                }
                break;
            case 270:
                newY=pos.getY()+VIT_BAZOOKA;
                if(newY>=max_taille_y){
                    newY=max_taille_y;
                }
                break;
            case 315:
                newX=pos.getX()+VIT_BAZOOKA/sqrt(2);
                newY=pos.getY()+VIT_BAZOOKA/sqrt(2);
                if(newX>=max_taille_x){
                    newX=max_taille_x;
                }
                if(newY>=max_taille_y){
                    newY=max_taille_y;
                }
                break;
            default:
                cout<<"Une erreur s'est glissé dans l'orientation du missile"<<endl;
                break;
        }
        pos.setX(newX);
        pos.setY(newY);
    }
}



sf::Sprite MissileGrenade::affiche(int xa, int ya){
    
    if(boom){
        if(cpt<=10){
            sprite_miss.setTextureRect(sf::IntRect(2*LARGEUR_BAZOOKA, HAUTEUR_EXPLOSION_1, LARGEUR_EXPLOSION, HAUTEUR_EXPLOSION_1));
        } else if (cpt<=20){
            sprite_miss.setTextureRect(sf::IntRect(2*LARGEUR_BAZOOKA, 2*HAUTEUR_EXPLOSION_1, LARGEUR_EXPLOSION, HAUTEUR_EXPLOSION_2));  
        } else if (cpt<=30){
            sprite_miss.setTextureRect(sf::IntRect(2*LARGEUR_BAZOOKA, 2*HAUTEUR_EXPLOSION_1+HAUTEUR_EXPLOSION_2, LARGEUR_EXPLOSION, HAUTEUR_EXPLOSION_3));  
        }
        sprite_miss.setPosition(pos.getX()-xa-LARGEUR_EXPLOSION/2, pos.getY()-ya-HAUTEUR_EXPLOSION_1/2);
        cpt++;
        
    } else {
        sprite_miss.setPosition(pos.getX()-xa-LARGEUR_EXPLOSION/2, pos.getY()-ya-HAUTEUR_EXPLOSION_1/2);
    }    
    
    return sprite_miss;
}

void MissileGrenade::explose(vector<Robot*> robots){
    int i;
    int const taille(robots.size());
    for(i=0; i<taille; i++){
        if(pos.distance(robots[i]->getPos())<ZONE_DE_DMG_GRENADE){
            robots[i]->setPV(robots[i]->getPV()-DMG_GRENADE);
        }
    }
}

void MissileGrenade::robotTouche(vector<Robot*> robots){
    //ici rien ne se passe car la grenade ne s'arrete pas lorsquelle touche un robot
}