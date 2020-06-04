#include <vector>
#include "Robot.hpp"
#include "Map.hpp"
#include "catch.hpp"



TEST_CASE("Apparition et Actions des robots"){


    Map* m = new Map(true,true,0);

    SECTION("Spawn"){
        m->addRobot(500,500);
        vector <Robot *> robs = m->getListeRobots();


        REQUIRE(robs[0]->getPos().getX()==500-120);
        REQUIRE(robs[0]->getPos().getY()==500-120);

        REQUIRE(robs[1]->getPos().getX()==500);
        REQUIRE(robs[1]->getPos().getY()==500-120);

        REQUIRE(robs[2]->getPos().getX()==500+120);
        REQUIRE(robs[2]->getPos().getY()==500-120);

        REQUIRE(robs[3]->getPos().getX()==500-120);
        REQUIRE(robs[3]->getPos().getY()==500);

        REQUIRE(robs[4]->getPos().getX()==500);
        REQUIRE(robs[4]->getPos().getY()==500);

        REQUIRE(robs[5]->getPos().getX()==500+120);
        REQUIRE(robs[5]->getPos().getY()==500);

        REQUIRE(robs[6]->getPos().getX()==500-120);
        REQUIRE(robs[6]->getPos().getY()==500+120);

        REQUIRE(robs[7]->getPos().getX()==500);
        REQUIRE(robs[7]->getPos().getY()==500+120);

        REQUIRE(robs[8]->getPos().getX()==500+120);
        REQUIRE(robs[8]->getPos().getY()==500+120);
    }

    SECTION("Mouvements sur Y"){
            Player* p = new Player(400,3000, true, 0, 3000, 0, 3000);

            //Robots immobiles
            m->addRobotTest(400,400);
            m->addRobotTest(400,800);

            //Collisions inter-robots
            m->addRobotTest(400,400-2*TAILLE_ROBOT);
            m->addRobotTest(400,399);
            m->addRobotTest(400, 800-TAILLE_ROBOT/2);


            
            vector<Robot*> robs = m->getListeRobots();

            //Robot loin des autres, il doit bouger normalement
             m->deplacementRobot(robs[2], p);
            REQUIRE(robs[2]->getPos().getX() == 400);
            REQUIRE(robs[2]->getPos().getY() == 400-2*TAILLE_ROBOT+1);

            //Robot superposé à un robot immobile, il ne doit pas bouger
            m->deplacementRobot(robs[3], p);
            REQUIRE(robs[3]->getPos().getX() == 400);
            REQUIRE(robs[3]->getPos().getY() == 399);

            //Robot a la limite d'un robot immobile, il ne doit pas bouger sur Y mais doit contourner en bougeant sur X
            m-> deplacementRobot(robs[4], p);
            REQUIRE(robs[4]->getPos().getX() == 399);
            REQUIRE(robs[4]->getPos().getY() == 800-TAILLE_ROBOT/2);

            //Cas où le robot a un robot en dessous de lui et un à sa gauche, il doit alors aller a droite

            m->addRobotTest(400,2000);
            m->addRobotTest(400-TAILLE_ROBOT/2, 2000-TAILLE_ROBOT/2);
            m->addRobotTest(400, 2000-TAILLE_ROBOT/2);
            robs = m->getListeRobots();

            m-> deplacementRobot(robs[7], p);
            REQUIRE(robs[7]->getPos().getX() == 401);
            REQUIRE(robs[7]->getPos().getY() == 2000-TAILLE_ROBOT/2);

    }

    SECTION("Mouvements sur X"){
            Player* p = new Player(3000,400, true, 0, 3000, 0, 3000);

            //Robots immobiles
            m->addRobotTest(400,400);
            m->addRobotTest(800,400);

            //Collisions inter-robots
            m->addRobotTest(400-2*TAILLE_ROBOT,400);
            m->addRobotTest(399,400);
            m->addRobotTest(800-TAILLE_ROBOT/2, 400);


            
            vector<Robot*> robs = m->getListeRobots();

            //Robot loin des autres, il doit bouger normalement
             m->deplacementRobot(robs[2], p);
            REQUIRE(robs[2]->getPos().getX() == 400-2*TAILLE_ROBOT+1);
            REQUIRE(robs[2]->getPos().getY() == 400);

            //Robot superposé à un robot immobile, il ne doit pas bouger
            m->deplacementRobot(robs[3], p);
            REQUIRE(robs[3]->getPos().getX() == 399);
            REQUIRE(robs[3]->getPos().getY() == 400);

            //Robot a la limite d'un robot immobile, il ne doit pas bouger sur X mais doit contourner en bougeant sur Y
            m-> deplacementRobot(robs[4], p);
            REQUIRE(robs[4]->getPos().getX() == 800-TAILLE_ROBOT/2);
            REQUIRE(robs[4]->getPos().getY() == 399);

            //Cas où le robot a un robot à sa droite et au dessus, il doit alors aller a en bas

            m->addRobotTest(2000,400);
            m->addRobotTest(2000-TAILLE_ROBOT/2, 400-TAILLE_ROBOT/2);
            m->addRobotTest(2000-TAILLE_ROBOT/2, 400);
            robs = m->getListeRobots();

            m-> deplacementRobot(robs[7], p);
            REQUIRE(robs[7]->getPos().getX() == 2000-TAILLE_ROBOT/2);
            REQUIRE(robs[7]->getPos().getY() == 401);

    }

    SECTION("Attaque"){
        
        m->getP1()->setPos(500,500);

        m->addRobotTest(500-LARGEUR_PERSO/2,500);

        vector<Robot*> robs = m->getListeRobots();
        m->tourRobot();
        REQUIRE(m->getP1()->getPV() == PV_MAX_JOUEUR-DMG_ROBOT);

    }
}