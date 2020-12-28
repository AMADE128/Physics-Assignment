#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePhysics.h"
#include "p2Point.h"
#include "math.h"

ModulePhysics::ModulePhysics(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	debug = true;
}


// Destructor
ModulePhysics::~ModulePhysics()
{
}

bool ModulePhysics::Start()
{
	LOG("Creating Physics 2D environment");
	
	SDL_Rect box;



	box.x = 100;
	box.y = 100;
	return true;
}

// 
update_status ModulePhysics::PreUpdate()
{
	if (box.y < 500)
	{
		box.y--;
	}
	else if (box.y >= 500)
	{
		speed_y = 0;
	}
	return UPDATE_CONTINUE;
}

update_status ModulePhysics::PostUpdate()
{
	Uint8 alpha = 120;

	if(App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	//Update positions

	box.x += speed_x;
	box.y += speed_y;

	App->renderer->DrawRectangle(box, 100, 42, 42, 0, true, alpha);

	App->renderer->DrawLine(0,500, 2000, 500, 1000, 42, 42, 42, alpha);
	if(!debug)
		return UPDATE_CONTINUE;

	return UPDATE_CONTINUE;
}


// Called before quitting
bool ModulePhysics::CleanUp()
{
	LOG("Destroying physics world");

	return true;
}

void PhysBody::GetPosition(int& x, int &y) const
{

}