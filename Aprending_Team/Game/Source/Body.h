#include "p2Point.h"

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
    iPoint position = { 0,0 };
    fPoint velocity = { 0,0 };
    fPoint acceleration = { 0,0 };
    fPoint forces = { 0,0 };
    //Angular

    //Forces



public:
    // Methods
    void SetMass(float _Mass) { mass = _Mass; };
    void SetLives(float _Lives) { lives = _Lives; };
    void SetClassType(Class type) { classType = type; };
    void SetAcceleration(fPoint acc) { acceleration = acc; };
    void setVelocity(fPoint vel) { velocity = vel; };
    void SetPosition(iPoint pos) {position = pos; };
    void AddForce(fPoint force);
    void ResetForce() { forces = { 0,0 };};
    fPoint GetForces() { return forces; };
    fPoint GetVelocity() { return velocity; };
    float GetMass() { return mass; };
    Class GetClass() { return classType; };
    iPoint GetPosition() { return position; };
    fPoint GetAcceleration() { return acceleration; };

    //void SetDimension(float width)

};