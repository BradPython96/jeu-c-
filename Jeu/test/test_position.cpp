#include "Position.hpp"
#include "catch.hpp"

TEST_CASE("Position"){
    Position* pos1 = new Position(0,0,0);
    Position* pos2 = new Position(10,0,0);
    Position* pos3 = new Position(0,10,0);
    Position* pos4 = new Position(0,10,0);

    REQUIRE(pos1->distance(*pos2) == 10);
    REQUIRE(pos1->distance(*pos3) == 10);
    REQUIRE(!(*pos1==*pos2));
    REQUIRE((*pos3==*pos4));
}