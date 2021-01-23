#include "Source/List.h"
#include "Source/p2Point.h"
#include "Body.h"

class PhysicsEngine
{
public:

	List<Body*> bodies;
	PhysicsEngine() {};
	~PhysicsEngine() {};
	fPoint CalculateGravity(iPoint player, float mass);
	void ApplyForcesToWorld(ListItem<Body*>* item);

private:
	int gravityMoon = 2;
	int gravityEarth = 10;
	int earthRange = 2500;
	int moonRange = 2500;
	int moonRadius;
	int earthRadius;
	int gravity;
};

