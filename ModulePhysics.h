#pragma once
#include "Module.h"
#include "Globals.h"


#define GRAVITY_X 0.0f
#define GRAVITY_Y -7.0f

#define PIXELS_PER_METER 50.0f // if touched change METER_PER_PIXEL too
#define METER_PER_PIXEL 0.02f // this is 1 / PIXELS_PER_METER !

#define METERS_TO_PIXELS(m) ((int) floor(PIXELS_PER_METER * m))
#define PIXEL_TO_METERS(p)  ((float) METER_PER_PIXEL * p)

// Small class to return to other modules to track position and rotation of physics bodies



struct Collider
{
	enum Type
	{
		GROUND,
			OBJECT,

	};

	SDL_Rect rect;
	Type type;
	Module* listener = nullptr;

	Collider(SDL_Rect rectangle, Type type, Module* listener = nullptr);

};

Collider::Collider(SDL_Rect rectangle, Type type, Module* listener) : rect(rectangle), type(type), listener(listener)
{

}



class PhysBody
{
public:
	PhysBody()
	{}

	void GetPosition(int& x, int &y) const;

public:
	int width, height;
};

// Module --------------------------------------
class ModulePhysics : public Module
{
public:
	ModulePhysics(Application* app, bool start_enabled = true);
	~ModulePhysics();

	bool Start();
	update_status PreUpdate();
	update_status PostUpdate();
	bool CleanUp();

private:

	bool debug;
};