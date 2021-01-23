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
	alive = true;
	// Create new ship
	rocketTex = app->tex->Load("Assets/Textures/rocket.png");
	explosionTex = app->tex->Load("Assets/Textures/explosion.png");
	meteorTex = app->tex->Load("Assets/Textures/meteor.png");
	app->audio->PlayMusic("Output/Assets/Audio/Music/Hymn.ogg");
	position.x = 640;
	position.y = 65;

	for (int i = 0; i < 384 * 6; i += 384)
	{
		explosionAnim.PushBack({ i, 0, 384, 384 });
	}
	explosionAnim.loop = false;
	explosionAnim.speed = 0.05f;

	for (int i = 0; i < 58 * 4; i += 58)
	{
		meteorAnim.PushBack({ i, 0, 58, 58 });
	}
	meteorAnim.loop = true;
	meteorAnim.speed = 0.15f;

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
	if (alive == true) 
	{
		if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		{
			position.y -= 5;
		}
		if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		{
			position.y += 5;
		}
		if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		{
			position.x += 5;
		}
		if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		{
			position.x -= 5;
		}
	}

	//meteor harcoded hitbox (as all hitboxes will be cuz idk any other way rn)
	if (position.x < 50 + 58 && position.x + 55 > 50 && position.y < 50 + 58 && position.y + 175 > 50) alive = false;

	//No u cant go to the center of the earth Verne
	if (position.y > 70) position.y = 70;

	//enter to revive (as in real life)
	if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN) alive = true;

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

	//explosion trigger
	if (alive == false && explosionAnim.HasFinished() == false)
	{
		Animation* explotion = &explosionAnim;
		explotion->Update();
		SDL_Rect explosionRec = explotion->GetCurrentFrame();
		app->render->DrawTexture(explosionTex, position.x - 165, position.y - 100, &explosionRec);
	}

	//meteor texture
	Animation* meteor = &meteorAnim;
	meteor->Update();

	SDL_Rect meteorRec = meteor->GetCurrentFrame();
	app->render->DrawTexture(meteorTex, 50, 50, &meteorRec);

	//player texture

	if (alive == true)
	{
		SDL_Rect rocketRec = { 0, 0, 50, 175 };
		app->render->DrawTexture(rocketTex, position.x, position.y, &rocketRec);
	}
	return true;
}

bool Player::CleanUp()
{
	if (!active)
		return true;
	app->tex->UnLoad(explosionTex);
	app->tex->UnLoad(rocketTex);

	active = false;

	return true;
}

