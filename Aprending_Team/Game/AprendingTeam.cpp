#include "AprendingTeam.h"
#include "Source/Defs.h"

fPoint PhysicsEngine::CalculateGravity(iPoint player, float mass)
{
	moonRadius = player.y;
	earthRadius = 6000 - player.y;

	if (player.y < moonRange)
	{
		gravity = -gravityMoon + fabs(G * mass / moonRadius);
	}
	else if (player.y > 6000 - earthRange)
	{
		gravity = gravityEarth + fabs(G * mass / earthRadius);
	}
	else
		return { 0,0 };

	fPoint fg;
	fg.x = 0;
	fg.y = gravity;

	return fg;
}