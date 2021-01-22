#include "Source/List.h"
#include "Source/p2Point.h"

class PhysicsEngine
{
public:
	PhysicsEngine() {};
	~PhysicsEngine() {};
	fPoint CalculateGravity(iPoint player, float mass);

private:
	int gravityMoon = 2;
	int gravityEarth = 10;
	int earthRange = 2500;
	int moonRange = 2500;
	int moonRadius;
	int earthRadius;
	int gravity;
};

