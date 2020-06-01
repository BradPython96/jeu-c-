#include "MissileLaser.hpp"

MissileLaser::MissileLaser(Position p){

    cpt=0;          //initialisation des variables
    boom = false;
    pos = p;

    int ang= pos.getAngle();    //angle du missile pour avoir l'affichage adapté
    int a;
    switch (ang){
        case 0:
            a=0;
            pos.setX(pos.getX()+LARGEUR_PERSO/1.5);   //on décale le missile
            break;
        case 45:
            a=2;
            pos.setX(pos.getX()+LARGEUR_PERSO/2);
            pos.setY(pos.getY()-HAUTEUR_PERSO/2);
            break;
        case 90:
            a=1;
            pos.setY(pos.getY()-HAUTEUR_PERSO/1.5);
            break;
        case 135:
            a=3;
            pos.setX(pos.getX()-LARGEUR_PERSO/2);
            pos.setY(pos.getY()-HAUTEUR_PERSO/2);
            break;
        case 180:
            a=0;
            pos.setX(pos.getX()-LARGEUR_PERSO/1.5);
            break;
        case 225:
            a=2;
            pos.setX(pos.getX()-LARGEUR_PERSO/2);
            pos.setY(pos.getY()+HAUTEUR_PERSO/2);
            break;
        case 270:
            a=1;
            pos.setY(pos.getY()+HAUTEUR_PERSO/1.5);
            break;
        case 315:
            a=3;
            pos.setX(pos.getX()+LARGEUR_PERSO/2);
            pos.setY(pos.getY()+HAUTEUR_PERSO/2);
            break;
        default:
            cout<<"Une erreur s'est glissé dans l'orientation du missile"<<endl;
            break;
    }

    if(!miss.loadFromFile("Laser.png")){
        cout<<"Erreur dans le chargement de la texture du laser"<<endl;
    }
    miss.setSmooth(true);
    sprite_miss.setTexture(miss);
    sprite_miss.setTextureRect(sf::IntRect(0, a*HAUTEUR_LASER, LARGEUR_LASER, HAUTEUR_LASER));
}

void MissileLaser::move(int min_taille_x, int min_taille_y, int max_taille_x, int max_taille_y){
    int ang= pos.getAngle();
    int newX = pos.getX();
    int newY = pos.getY();
    switch (ang){
        case 0:
            newX=pos.getX()+VIT_LASER;
            if(newX>=max_taille_x){
                boom=true;
                newX=max_taille_x;
            }
            break;
        case 45:
            newX=pos.getX()+VIT_LASER/sqrt(2);
            newY=pos.getY()-VIT_LASER/sqrt(2);
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
            newY=pos.getY()-VIT_LASER;
            if(newY<=min_taille_y){
                boom=true;
                newY=min_taille_y;
            }
            break;
        case 135:
            newX=pos.getX()-VIT_LASER/sqrt(2);
            newY=pos.getY()-VIT_LASER/sqrt(2);
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
            newX=pos.getX()-VIT_LASER;
            if(newX<=min_taille_x){
                boom=true;
                newX=min_taille_x;
            }
            break;
        case 225:
            newX=pos.getX()-VIT_LASER/sqrt(2);
            newY=pos.getY()+VIT_LASER/sqrt(2);
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
            newY=pos.getY()+VIT_LASER;
            if(newY>=max_taille_y){
                boom=true;
                newY=max_taille_y;
            }
            break;
        case 315:
            newX=pos.getX()+VIT_LASER/sqrt(2);
            newY=pos.getY()+VIT_LASER/sqrt(2);
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
            cout<<"Une erreur s'est glissé dans l'orientation du missile"<<endl;
            break;
    }
    pos.setX(newX);
    pos.setY(newY);
}


sf::Sprite MissileLaser::affiche(int xa, int ya){
    if(!boom){
        sprite_miss.setPosition(pos.getX()-xa-LARGEUR_LASER/2, pos.getY()-ya-HAUTEUR_LASER/2); 
    } else {
        cpt=31;
    }
    
    
    return sprite_miss;
}

void MissileLaser::explose(vector<Robot*> robots){
    //Pas necessaire dans le cas du laser
}

void MissileLaser::robotTouche(vector<Robot*> robots){
    int i;
    int const taille(robots.size());
    for(i=0; i<taille; i++){
        if(pos.distance(robots[i]->getPos())<TAILLE_ROBOT/2){
            boom=true;
            robots[i]->setPV(robots[i]->getPV()-DMG_LASER);
        }
    }
}