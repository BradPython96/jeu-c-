#include "MissileLaser.hpp"

MissileLaser::MissileLaser(Position p){
    boom = false;
    pos = p;
    int ang= pos.getAngle();
    int a;
    int b;
    switch (ang){
        case 0:
            a=2;
            b=0;
            break;
        case 45:
            a=0;
            b=1;
            break;
        case 90:
            a=1;
            b=0;
            break;
        case 135:
            a=2;
            b=1;
            break;
        case 180:
            a=0;
            b=0;
            break;
        case 225:
            a=3;
            b=2;
            break;
        case 270:
            a=3;
            b=0;
            break;
        case 315:
            a=1;
            b=1;
            break;
        default:
            cout<<"Une erreur c'est glissé dans l'orientation du missile"<<endl;
            break;
    }

    if(!miss.loadFromFile("Tirs.png")){
        cout<<"Erreur dans le chargement de la texture de tir"<<endl;
    }
    miss.setSmooth(true);
    sprite_miss.setTexture(miss);
    sprite_miss.setTextureRect(sf::IntRect(b*LARGEUR_BAZOOKA, a*HAUTEUR_BAZOOKA, LARGEUR_BAZOOKA, HAUTEUR_BAZOOKA));

}


void MissileLaser::move(int min_taille_x, int min_taille_y, int max_taille_x, int max_taille_y){
    
    int ang= pos.getAngle();
    int newX = pos.getX();
    int newY = pos.getY();

    switch (ang){
        case 0:
            newX=pos.getX()+VIT_BAZOOKA;
            if(newX>=max_taille_x){
                boom=true;
                newX=max_taille_x;
            }
            break;
        case 45:
            newX=pos.getX()+VIT_BAZOOKA/sqrt(2);
            newY=pos.getY()-VIT_BAZOOKA/sqrt(2);
            if(newX>=max_taille_x){
                boom=true;
                newX=max_taille_x;
            }
            if(newY<=min_taille_y){
                boom=true;
                newY=min_taille_y;
            }
            break;
        case 90:
            newY=pos.getY()-VIT_BAZOOKA;
            if(newY<=min_taille_y){
                boom=true;
                newY=min_taille_y;
            }
            break;
        case 135:
            newX=pos.getX()-VIT_BAZOOKA/sqrt(2);
            newY=pos.getY()-VIT_BAZOOKA/sqrt(2);
            if(newX<=min_taille_x){
                boom=true;
                newX=min_taille_x;
            }
            if(newY<=min_taille_y){
                boom=true;
                newY=min_taille_y;
            }
            break;
        case 180:
            newX=pos.getX()-VIT_BAZOOKA;
            if(newX<=min_taille_x){
                boom=true;
                newX=min_taille_x;
            }
            break;
        case 225:
            newX=pos.getX()-VIT_BAZOOKA/sqrt(2);
            newY=pos.getY()+VIT_BAZOOKA/sqrt(2);
            if(newX<=min_taille_x){
                boom=true;
                newX=min_taille_x;
            }
            if(newY>=max_taille_y){
                boom=true;
                newY=max_taille_y;
            }
            break;
        case 270:
            newY=pos.getY()+VIT_BAZOOKA;
            if(newY>=max_taille_y){
                boom=true;
                newY=max_taille_y;
            }
            break;
        case 315:
            newX=pos.getX()+VIT_BAZOOKA/sqrt(2);
            newY=pos.getY()+VIT_BAZOOKA/sqrt(2);
            if(newX>=max_taille_x){
                boom=true;
                newX=max_taille_x;
            }
            if(newY>=max_taille_y){
                boom=true;
                newY=max_taille_y;
            }
            break;
        default:
            cout<<"Une erreur c'est glissé dans l'orientation du missile"<<endl;
            break;
    }
    pos.setX(newX);
    pos.setY(newY);
}

sf::Sprite MissileLaser::affiche(int xa, int ya){
    
	sprite_miss.setPosition(pos.getX()-xa-LARGEUR_BAZOOKA/2, pos.getY()-ya-HAUTEUR_BAZOOKA/2);

    return sprite_miss;
}

void MissileLaser::explose(vector<Robot*> robots){
    int i;
    int const taille(robots.size());
    for(i=0; i<taille; i++){
        if(pos.distance(robots[i]->getPos())<ZONE_DE_DMG_BAZOOKA){
            robots[i]->setPV(robots[i]->getPV()-DMG_BAZOOKA);
        }
    }
}

void MissileLaser::robotTouche(vector<Robot*> robots){
    int i;
    int const taille(robots.size());
    for(i=0; i<taille; i++){
        if(pos.distance(robots[i]->getPos())<TAILLE_ROBOT/2){
            boom=true;
        }
    }
}