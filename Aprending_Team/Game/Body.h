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
    ENEMIES,
    WINEARTH,
    WINMOON,
    FLOOR
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
    Class classType;
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
    void SetMass(float _Mass) { mass = _Mass; };
    void SetLives(float _Lives) { lives = _Lives; };
    void SetClassType(Class type) { classType = type; };
    void SetDimension(float width)

};