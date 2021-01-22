#include "Source/p2Point.h"

enum class BodyType
{
    STATIC,
    DYNAMIC,
    KINEMATIC
};

enum class Class
{
    NONE,
    PLAYER,
    ASTEROIDS,
    WINEARTH,
    WINMOON
};

class Body
{
public: 
    //General
    float mass;
    int lives = 1;
    int fuel;
    float width;
    float height;
    //Lineal
    fPoint position = { 0,0 };
    fPoint velocity = { 0,0 };
    fPoint acceleration = { 0,0 };
    //Angular

    //Forces

   

public: 
    // Methods
    void addForce();
    void addMomentum();
}