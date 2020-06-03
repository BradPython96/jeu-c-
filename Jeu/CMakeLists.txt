cmake_minimum_required(VERSION 3.16)
project(Jeu)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Jeu
        Accessoire.cpp
        Accessoire.hpp
        Arme.hpp
        Bazooka.cpp
        Bazooka.hpp
        Define.hpp
        Game.cpp
        Game.hpp
        Grenade.cpp
        Grenade.hpp
        Laser.cpp
        Laser.hpp
        main.cpp
        Map.cpp
        Map.hpp
        Missile.hpp
        MissileBazooka.cpp
        MissileBazooka.hpp
        MissileGrenade.cpp
        MissileGrenade.hpp
        MissileLaser.cpp
        MissileLaser.hpp
        Player.cpp
        Player.hpp
        Position.cpp
        Position.hpp
        Robot.cpp
        Robot.hpp)
