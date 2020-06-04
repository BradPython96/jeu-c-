#include "Bazooka.hpp"
#include "Grenade.hpp"
#include "Laser.hpp"
#include "Player.hpp"
#include "catch.hpp"

TEST_CASE("Armes"){
    Player* p = new Player(500,500,true,0,1000,0,1000);
    

    SECTION("Ajout d'arme"){
        REQUIRE(p->getLaser() != nullptr);
        REQUIRE(p->getBazooka() == nullptr);
        REQUIRE(p->getGrenade() == nullptr);

        p->addBazooka();
        REQUIRE(p->getBazooka() != nullptr);

        p->addGrenade();
        REQUIRE(p->getGrenade()!=nullptr);
    }

}