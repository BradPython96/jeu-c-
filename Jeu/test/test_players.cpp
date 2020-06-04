#include <vector>
#include "Player.hpp"
#include "Map.hpp"
#include "catch.hpp"


TEST_CASE("Actions des joueurs", "[joueur]"){

    Player* p = new Player(500,500,true, 0, 1000, 0, 1000);
    
    SECTION("Initialisation"){
        REQUIRE(p->getSex()==true);
        REQUIRE(p->getPos().getX()==500);
        REQUIRE(p->getPos().getY()==500);
        REQUIRE(p->getPV()==PV_MAX_JOUEUR);
        p->setPV(50);
        REQUIRE(p->getPV()==50);
        REQUIRE(p->getArmCur()==0);
        REQUIRE(p->vivant()==true);
    }

    SECTION("Deplacement"){

        //Test de chacun des déplacement du joueur
        p->moveDown(250);
        REQUIRE(p->getPos().getX()==500);
        REQUIRE(p->getPos().getY()==500+VIT_JOUEUR);
        p->moveUp(250+VIT_JOUEUR);
        REQUIRE(p->getPos().getX()==500);
        REQUIRE(p->getPos().getX()==500);
        p->moveLeft(250);
        REQUIRE(p->getPos().getX()==500+VIT_JOUEUR);
        REQUIRE(p->getPos().getY()==500);
        p->moveRight(250+VIT_JOUEUR);
        REQUIRE(p->getPos().getX()==500);
        REQUIRE(p->getPos().getX()==500);

        p->moveDownRight(250, 250);
        REQUIRE(p->getPos().getX()==500-VIT_JOUEUR);
        REQUIRE(p->getPos().getY()==500+VIT_JOUEUR);
        p->moveUpLeft(250-VIT_JOUEUR, 250+VIT_JOUEUR);
        REQUIRE(p->getPos().getX()==500);
        REQUIRE(p->getPos().getX()==500);
        p->moveDownLeft(250, 250);
        REQUIRE(p->getPos().getX()==500+VIT_JOUEUR);
        REQUIRE(p->getPos().getY()==500+VIT_JOUEUR);
        p->moveUpRight(250+VIT_JOUEUR, 250+VIT_JOUEUR);
        REQUIRE(p->getPos().getX()==500);
        REQUIRE(p->getPos().getX()==500);
        REQUIRE(p->getPos().getAngle()==45);

        //Test dans le cas ou le joueur veux sortir de la fenetre
        int i;
        for(i=0; i<255; i++){
            p->moveDown(250);
        }
        REQUIRE(p->getPos().getX()==500);
        REQUIRE(p->getPos().getX()==750);
        
    }

    SECTION("Swap"){

        //Le joueur n'a qu'une seul arme
        p->swapArme();
        REQUIRE(p->getArmCur()==0);
        //Le joueur a deux armes
        p->addBazooka();
        p->swapArme();
        REQUIRE(p->getArmCur()==1);
        p->swapArme();
        REQUIRE(p->getArmCur()==0);
        //Le joueur a trois armes
        p->addGrenade();
        p->swapArme();
        p->swapArme();
        REQUIRE(p->getArmCur()==2);
        p->swapArme();
        REQUIRE(p->getArmCur()==0);
    }


    SECTION("Tir"){
        vector<Missile *> miss=p->getListMiss();
        REQUIRE(miss.size()==0);
        p->tir();
        miss=p->getListMiss();
        REQUIRE(miss.size()==1);
        //Suite des test dans "test_missile.cpp"
    }

    SECTION("Mort"){
        p->setPV(-10);
        REQUIRE(p->vivant()==false);
    }

}