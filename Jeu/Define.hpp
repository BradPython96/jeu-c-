#ifndef DEFINE_HPP
#define DEFINE_HPP

#define TAILLE 1000
//Dimension de la map couloir
#define MIN_MAP_COULOIR_X 0
#define MAX_MAP_COULOIR_X 5000
#define MIN_MAP_COULOIR_Y 235
#define MAX_MAP_COULOIR_Y 823
#define TAILLE_MAP_COULOIR_X 5000
#define TAILLE_MAP_COULOIR_Y 1000
//Dimension de la map arene
#define MIN_MAP_ARENE_X 0
#define MAX_MAP_ARENE_X 5000
#define MIN_MAP_ARENE_Y 300
#define MAX_MAP_ARENE_Y 800
#define TAILLE_MAP_ARENE_X 5000
#define TAILLE_MAP_ARENE_Y 1000


#define NB_ROB_INIT 10
#define NB_ACCESSOIRES_INIT 20

#define NB_MUN_MAX_LASER 15
#define NB_MUN_MAX_BAZOOKA 10
#define NB_MUN_MAX_GRENADE 5

#define PORTEE_GRENADE 5

#define ZONE_DE_DMG_LASER 2
#define ZONE_DE_DMG_BAZOOKA LARGEUR_EXPLOSION/2+5
#define ZONE_DE_DMG_GRENADE LARGEUR_EXPLOSION/2+5

#define DMG_LASER 15
#define DMG_BAZOOKA 100
#define DMG_GRENADE 10
#define DMG_ROBOT 10

//PV
#define PV_MAX_JOUEUR 100
#define PV_MAX_ROBOT 30

//Vitesse
#define VIT_JOUEUR 8
#define VIT_ROBOT 1
#define VIT_BAZOOKA 8
#define VIT_GRENADE 6

// AFFICHAGE
#define HAUTEUR_PERSO 115.75
#define LARGEUR_PERSO 90
#define TAILLE_ROBOT 120
#define TAILLE_ACCESSOIRE 50

#define LARGEUR_BAZOOKA 120
#define HAUTEUR_BAZOOKA 90

#define LARGEUR_EXPLOSION 115
#define HAUTEUR_EXPLOSION_1 75
#define HAUTEUR_EXPLOSION_2 100
#define HAUTEUR_EXPLOSION_3 130


#endif
