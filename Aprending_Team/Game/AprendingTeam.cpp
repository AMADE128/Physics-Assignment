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

void PhysicsEngine::ApplyForcesToWorld(ListItem<Body*>* item)
{
	for (item = bodies.start; item != NULL; item = item->next)
	{
		Body* b = item->data;
		fPoint FGravity = CalculateGravity(b->position ,b->mass);
		b->AddForce(FGravity);


		if (item->data->GetVelocity().x <= 0 && item->data->GetClass() == Class::ENEMIES)
		{
			// MAAARRCCC
		}
	}
}