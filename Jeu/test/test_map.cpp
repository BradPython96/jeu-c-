#include <vector>
#include "Map.hpp"
#include "Player.hpp"
#include "Accessoire.hpp"
#include "catch.hpp"


TEST_CASE("Creation de la carte et Game Over"){



    Map* m = new Map(true, true, 0);
    
    SECTION("Creation de la carte"){
        int max_X = MAX_MAP_COULOIR_X;
        int min_X = MIN_MAP_COULOIR_X;
        int max_Y = MAX_MAP_COULOIR_Y;
        int min_Y = MIN_MAP_COULOIR_Y;
        REQUIRE(m->getMinTailleX() == min_X);
		REQUIRE(m->getMaxTailleX() == max_X);
		REQUIRE(m->getMinTailleY() == min_Y);
		REQUIRE(m->getMaxTailleY() == max_Y);

        vector<Position*> spawns = m->getSpawns();
        REQUIRE(spawns[0]->getX() == min_X);
        REQUIRE(spawns[0]->getY() == (min_Y + max_Y)/2);
        REQUIRE(spawns[1]->getX() == max_X);
        REQUIRE(spawns[1]->getY() == (min_Y + max_Y)/2);
    }

    SECTION("Game Over"){
        m->getP1()->setPV(0);
        REQUIRE(!m->gameOver());
        m->getP2()->setPV(0);
        REQUIRE(m->gameOver());

    }


}