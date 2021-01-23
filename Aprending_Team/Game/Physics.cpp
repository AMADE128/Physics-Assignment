#include "Physics.h"
#include "Source/Defs.h"

Physics::Physics() : Module()
{

}

Physics::~Physics()
{

}

bool Physics::Start()
{
	return true;
}

bool Physics::PreUpdate()
{
	return true;
}

bool Physics::Update(float dt)
{
	return true;
}

bool Physics::PostUpdate()
{
	return true;
}

bool Physics::CleanUp()
{
	return true;
}