#include "List.h"
#include "p2Point.h"
#include "Body.h"

class PhysicsEngine
{
public:

	List<Body*> bodies;
	PhysicsEngine() {};
	~PhysicsEngine() {};
	fPoint CalculateGravity(iPoint player, float mass);
	void ApplyForcesToWorld(Body* body);
	void CalculateAcceleration(Body* b);
	void MRUA(Body* body, float dt);

private:
	int gravityMoon = 2;
	int gravityEarth = 10;
	int earthRange = -2000;
	int moonRange = -4000;
	int moonRadius;
	int earthRadius;
	int gravity;
};

