#include "Player.h"
#include "Audio.h"
#include "Render.h"
#include "Input.h"
#include "App.h"
#include "SceneManager.h"
#include "Scene.h"

#include "Log.h"
#include "Defs.h"


Player::Player() : Module()
{
	name.Create("player");
}

Player::Player(iPoint pPosition, float pVelocity, SDL_Texture* pTexture): Module()
{
	name.Create("player");
}

Player::~Player()
{}

bool Player::Start() 
{
	active = true;
	// Create new ship
	player = app->tex->Load("Output/Assets/Textures/Rocket.png");
	app->audio->PlayMusic("Output/Assets/Audio/Music/Hymn.ogg");
	position.x = 0;
	position.y = 0;

	return true;
}

bool Player::Awake(pugi::xml_node& config)
{
	LOG("Loading Player Parser");
	bool ret = true;
	
	return true;
}

bool Player::PreUpdate() 
{
	if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
	{
			app->render->camera.y += 30;
	}
	if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{
			app->render->camera.y -= 30;
	}
	if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		if (app->render->camera.x > 0 && app->render->camera.x > 1280)
		{
			app->render->camera.x -= 30;
		}
	}
	if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		if (app->render->camera.x > 0 && app->render->camera.x > 1280)
		{
			app->render->camera.x += 30;
		}
	}
	return true;
}

bool Player::Update(float dt) 
{
	return true;
}

bool Player::PostUpdate()
{
	return true;
}

bool Player::CleanUp()
{
	if (!active)
		return true;

	active = false;

	return true;
}

