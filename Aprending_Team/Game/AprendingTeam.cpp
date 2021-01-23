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

void PhysicsEngine::CalculateAcceleration(Body* body)
{
	//Using Newton's 2nd law F = m * a we get a = F / m
	body->SetAcceleration({ body->GetForces().x / body->GetMass(), body->GetForces().y / body->GetMass()});
}

void PhysicsEngine::MRUA(Body* body, float dt)
{
	//using MRUA formula x = x0 + v0*t + 1/2 a * t^2
	iPoint pos;
	pos.x = body->GetPosition().x + body->GetVelocity().x * dt + 0.5 * body->GetAcceleration().x * dt * dt;
	pos.y = body->GetPosition().y + body->GetVelocity().y * dt + 0.5 * body->GetAcceleration().y * dt * dt;
	body->SetPosition(pos);

	fPoint vel;
	vel.x = body->GetVelocity().x + body->GetAcceleration().x * dt;
	vel.y = body->GetVelocity().y + body->GetAcceleration().y * dt;
	body->setVelocity(vel);
}