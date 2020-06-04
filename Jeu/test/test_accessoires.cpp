#include <vector>
#include "Map.hpp"
#include "Player.hpp"
#include "Accessoire.hpp"
#include "catch.hpp"


TEST_CASE("Apparition et Récupration des accessoires"){



    Map* m = new Map(true, true, 0);
    
    SECTION("Appariton des accessoires"){
        REQUIRE(m->getAccs().size() == NB_ACCESSOIRES_INIT);

        //Le test de l'appartion d'un accessoire été fait en condition réelle
    }

    SECTION("Récupération des accessoires"){
        vector<Accessoire*> listeAcc;
        listeAcc = m->getAccs();
        Accessoire* acc;
        int i;

        //Cas où le joueur est sur les accessoires
        for (i=0; i<NB_ACCESSOIRES_INIT-1; i++){
            acc = listeAcc[i];
            m->getP1()->setPos(acc->getPos().getX(), acc->getPos().getY());
            m->recuperationAcc();
            REQUIRE(m->getAccs().size() == abs(NB_ACCESSOIRES_INIT-i-1));
        }

        //cas où le joueur est à côté de l'accessoire
            acc = listeAcc[NB_ACCESSOIRES_INIT-1];
            m->getP1()->setPos(acc->getPos().getX()+51, acc->getPos().getY());
            m->getP2()->setPos(acc->getPos().getX(), acc->getPos().getY()+51);
            m->recuperationAcc();
            REQUIRE(m->getAccs().size() == 1);

        //Cas où le joueur est à la limite de l'accessoire
            m->getP2()->setPos(acc->getPos().getX()+50, acc->getPos().getY());
            m->recuperationAcc();
            REQUIRE(m->getAccs().size() == 0);
    }


}