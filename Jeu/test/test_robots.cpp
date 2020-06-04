#include <vector>
#include "Robot.hpp"
#include "Map.hpp"
#include "catch.hpp"


TEST_CASE("Actions des robots", "[robot]"){

    Map* m = new Map(true,true,0);
    m->addRobot(500,500);
    Player* p = new Player(500,500,true, 0,1000,0,1000);
    vector <Robot *> robs = m->getListeRobots();
    REQUIRE(robs[0]->getPos().getX()==500-120);
    REQUIRE(robs[0]->getPos().getY()==500-120);

    SECTION("Mouvements"){
            m->deplacementRobot(robs[3], p);
            REQUIRE(robs[3]->getPos().getX() == 500-120);


    }




}