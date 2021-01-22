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
	rocketTex = app->tex->Load("Assets/Textures/rocket.png");
	app->audio->PlayMusic("Output/Assets/Audio/Music/Hymn.ogg");
	position.x = 640;
	position.y = 65;

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
		position.y -=5;
	}
	if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{
		position.y +=5;
	}
	if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		position.x += 5;
	}
	if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		position.x -= 5;
	}
	return true;
}

bool Player::Update(float dt) 
{
	//camera follows player up
	if (app->render->camera.y - 250 < -(position.y))app->render->camera.y += 5;

	//camera follows player down
	if (app->render->camera.y - 300 > -(position.y))app->render->camera.y -= 5;

	if (position.x < -60 )position.x = 1280;
	if (position.x > 1285 )position.x = -55;

	return true;
}

bool Player::PostUpdate()
{
	SDL_Rect rocketRec = { 0, 0, 50, 175 };
	app->render->DrawTexture(rocketTex, position.x, position.y, &rocketRec);

	return true;
}

bool Player::CleanUp()
{
	if (!active)
		return true;

	active = false;

	return true;
}

