#include "AprendingTeam.h"
#include "Defs.h"

fPoint PhysicsEngine::CalculateGravity(iPoint player, float mass)
{
	moonRadius = player.y;
	earthRadius = 6000 - player.y;

	if (player.y < moonRange)
	{
		gravity = -gravityMoon + fabs(G * mass / moonRadius);
	}
	else if (player.y > earthRange)
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

void PhysicsEngine::ApplyForcesToWorld(Body* body)
{
	
		fPoint FGravity = CalculateGravity(body->position ,body->mass);
		body->AddForce(FGravity);

}

void PhysicsEngine::CalculateAcceleration(Body* body)
{
	//Using Newton's 2nd law F = m * a we get a = F / m
	body->SetAcceleration({ body->GetForces().x / body->GetMass(), body->GetForces().y / body->GetMass()});
}

void PhysicsEngine::MRUA(Body* body, float dt)
{
	CalculateAcceleration(body);
	//using MRUA formula x = x0 + v0*t + 1/2 a * t^2
	if (body->GetAcceleration().y >= 1 || body->GetAcceleration().y < -1) body->SetAcceleration({ 0,0 });
	iPoint pos;
	(pos.x) = body->GetPosition().x + body->GetVelocity().x * dt + 0.5 * body->GetAcceleration().x * dt * dt;
	pos.y = body->GetPosition().y + body->GetVelocity().y * dt + 0.5 * body->GetAcceleration().y * dt * dt;
	PIXEL_TO_METERS(pos.x); PIXEL_TO_METERS(pos.y);
	body->SetPosition(pos);

	fPoint vel;
	vel.x = body->GetVelocity().x + body->GetAcceleration().x * dt;
	vel.y = body->GetVelocity().y + body->GetAcceleration().y * dt;
	if (body->GetVelocity().y < -6)
	{
		body->setVelocity({ 0, -6 });
	}
	else if (body->GetVelocity().y > 6)
	{
		body->setVelocity({ 0, 6 });
	}
	else body->setVelocity(vel);
}