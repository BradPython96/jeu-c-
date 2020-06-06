#include <vector>
#include "Missile.hpp"
#include "MissileBazooka.hpp"
#include "MissileGrenade.hpp"
#include "MissileLaser.hpp"
#include "Arme.hpp"
#include "Position.hpp"
#include "Robot.hpp"
#include "catch.hpp"


TEST_CASE("Actions des missiles", "[missile]"){

    
    SECTION("Missile Bazooka"){
        vector<Robot*> robot;
       robot.push_back(new Robot(new Position(500+LARGEUR_PERSO/1.5+VIT_BAZOOKA*2, 500, 0)));

        MissileBazooka* mb1 = new MissileBazooka(Position(500, 500, 0));  //L'angle 0 le missile se dirige vers la droite
        REQUIRE(mb1->getBoom()==false);
        REQUIRE(mb1->getPos().getX()==500+LARGEUR_PERSO/1.5);
        REQUIRE(mb1->getPos().getY()==500);

        //Test déplacement du missile moveRight
        mb1->move(0,0,1000,1000);
        REQUIRE(mb1->getPos().getX()==(int) (500+LARGEUR_PERSO/1.5+VIT_BAZOOKA));
        REQUIRE(mb1->getPos().getY()==500);

        //Test déplacement du missile moveUp
        MissileBazooka* mb2 = new MissileBazooka(Position(500, 500, 90));
        mb2->move(0,0,1000,1000);
        REQUIRE(mb2->getPos().getX()==500);
        REQUIRE(mb2->getPos().getY()==(int) (500-HAUTEUR_PERSO/1.5-VIT_BAZOOKA));

        //Test déplacement du missile moveUpRight
        MissileBazooka* mb3 = new MissileBazooka(Position(500, 500, 45));
        mb3->move(0,0,1000,1000);
        REQUIRE(mb3->getPos().getX()==(int) (500+LARGEUR_PERSO/2+VIT_BAZOOKA/sqrt(2)));
        REQUIRE(mb3->getPos().getY()==(int) (500-HAUTEUR_PERSO/2-VIT_BAZOOKA/sqrt(2)));

        //Tests contact avec le robot
        mb1->move(0,0,1000,1000);
        REQUIRE(mb1->getPos().getX()==(int) (500+LARGEUR_PERSO/1.5+VIT_BAZOOKA*2));
        REQUIRE(mb1->getPos().getY()==500);
        mb1->robotTouche(robot);
        REQUIRE(mb1->getBoom()==true);
        REQUIRE(robot[0]->getPV()==30);
        mb1->explose(robot);
        REQUIRE(robot[0]->getPV()==30-DMG_BAZOOKA);
        
        //Test contact avec le mur
        MissileBazooka* mb4 = new MissileBazooka(Position(500, 500, 0));
        mb4->move(0,0,500+LARGEUR_PERSO/1.5+VIT_BAZOOKA, 1000);
        REQUIRE(mb4->getPos().getX()==(int) (500+LARGEUR_PERSO/1.5+VIT_BAZOOKA));
        REQUIRE(mb4->getPos().getY()==500);
        REQUIRE(mb4->getBoom()==true);
    }

    SECTION("Missile Grenade"){
        vector<Robot*> robot2;
        robot2.push_back(new Robot(new Position(500+PORTEE_GRENADE, 500, 0)));
        MissileGrenade* mg1 = new MissileGrenade(Position(500, 500, 0));  //L'angle 0 le missile se dirige vers la droite
        REQUIRE(mg1->getBoom()==false);
        REQUIRE(mg1->getPos().getX()==500);
        REQUIRE(mg1->getPos().getY()==500);

        //Test déplacement du missile moveRight
        mg1->move(0,0,1000,1000);
        REQUIRE(mg1->getPos().getX()==(int) (500+VIT_GRENADE));
        REQUIRE(mg1->getPos().getY()==500);

        //Test déplacement du missile moveUp
        MissileGrenade* mg2 = new MissileGrenade(Position(500, 500, 90));
        mg2->move(0,0,1000,1000);
        REQUIRE(mg2->getPos().getX()==500);
        REQUIRE(mg2->getPos().getY()==(int) (500-VIT_GRENADE));

        //Test déplacement du missile moveUpRight
        MissileGrenade* mg3 = new MissileGrenade(Position(500, 500, 45));
        mg3->move(0,0,1000,1000);
        REQUIRE(mg3->getPos().getX()==(int) (500+VIT_GRENADE/sqrt(2)));
        REQUIRE(mg3->getPos().getY()==(int) (500-VIT_GRENADE/sqrt(2)));

        //Tests contact avec le robot
        int i=0;
        while (mg1->getCptG()==0)
        {
            i++;
            mg1->move(0,0,1000,1000);
        }
        REQUIRE(mg1->getPos().getX()==500+VIT_GRENADE*i);
        REQUIRE(mg1->getPos().getY()==500);
        while (mg1->getCptG()<50)
        {
            mg1->move(0,0,1000,1000);
        }
        REQUIRE(mg1->getBoom()==true);
        mg1->explose(robot2);
        REQUIRE(robot2[0]->getPV()==30-DMG_GRENADE);
        
        //Test contact avec le mur
        MissileGrenade* mg4 = new MissileGrenade(Position(500, 500, 0));
        while (mg4->getCptG()<50)
        {
            mg4->move(0, 0, 600, 1000);
        }
        REQUIRE(mg4->getPos().getX()==600);
        REQUIRE(mg4->getPos().getY()==500);
        REQUIRE(mg4->getBoom()==true);
    }

    SECTION("Missile Laser"){
        vector<Robot*> robot3;
        robot3.push_back(new Robot(new Position(500+LARGEUR_PERSO/1.5+VIT_LASER*2, 500, 0)));

        MissileLaser* ml1 = new MissileLaser(Position(500, 500, 0));  //L'angle 0 le missile se dirige vers la droite
        REQUIRE(ml1->getBoom()==false);
        REQUIRE(ml1->getPos().getX()==500+LARGEUR_PERSO/1.5);
        REQUIRE(ml1->getPos().getY()==500);

        //Test déplacement du missile moveRight
        ml1->move(0,0,1000,1000);
        REQUIRE(ml1->getPos().getX()==(int) (500+LARGEUR_PERSO/1.5+VIT_LASER));
        REQUIRE(ml1->getPos().getY()==500);

        //Test déplacement du missile moveUp
        MissileLaser* ml2 = new MissileLaser(Position(500, 500, 90));
        ml2->move(0,0,1000,1000);
        REQUIRE(ml2->getPos().getX()==500);
        REQUIRE(ml2->getPos().getY()==(int) (500-HAUTEUR_PERSO/1.5-VIT_LASER));

        //Test déplacement du missile moveUpRight
        MissileLaser* ml3 = new MissileLaser(Position(500, 500, 45));
        ml3->move(0,0,1000,1000);
        REQUIRE(ml3->getPos().getX()==(int) (500+LARGEUR_PERSO/2+VIT_LASER/sqrt(2)));
        REQUIRE(ml3->getPos().getY()==(int) (500-HAUTEUR_PERSO/2-VIT_LASER/sqrt(2)));

        //Tests contact avec le robot
        ml1->move(0,0,1000,1000);
        REQUIRE(ml1->getPos().getX()==(int) (500+LARGEUR_PERSO/1.5+VIT_LASER*2));
        REQUIRE(ml1->getPos().getY()==500);
        ml1->robotTouche(robot3);
        REQUIRE(ml1->getBoom()==true);
        REQUIRE(robot3[0]->getPV()==30-DMG_LASER);
        
        //Test contact avec le mur
        MissileLaser* ml4 = new MissileLaser(Position(500, 500, 0));
        ml4->move(0,0,500+LARGEUR_PERSO/1.5+VIT_LASER, 1000);
        REQUIRE(ml4->getPos().getX()==(int) (500+LARGEUR_PERSO/1.5+VIT_LASER));
        REQUIRE(ml4->getPos().getY()==500);
        REQUIRE(ml4->getBoom()==true);
    }

}