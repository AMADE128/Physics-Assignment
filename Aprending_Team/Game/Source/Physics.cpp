#include "Physics.h"
#include "Defs.h"

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

Body* Physics::CreateBody(Body* b)
{

	return b;
}

void Physics::DestroyBody(Body* b)
{
	ListItem<Body*>* item = bodies.start;

	while (item != nullptr)
	{
		if (item->data == b)
			bodies.Del(item);

		item = item->next;
	}
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 

bool Physics::CleanUp()
{
	
	return true;
}