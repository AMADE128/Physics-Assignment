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
	maxAcc = 8;
	bomb = false;
	fire = true;
	active = true;
	alive = true;
	// Create new ship
	rocketTex = app->tex->Load("Assets/Textures/rocket.png");
	explosionTex = app->tex->Load("Assets/Textures/explosion.png");
	meteorTex = app->tex->Load("Assets/Textures/meteor.png");
	fireTex = app->tex->Load("Assets/Textures/fire.png");
	winTex = app->tex->Load("Assets/Textures/win.png");
	loseTex = app->tex->Load("Assets/Textures/lose.png");
	app->audio->PlayMusic("Output/Assets/Audio/Music/Hymn.ogg");
	position.x = 640;
	position.y = 70;

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

	for (int i = 0; i < 49 * 8; i += 49)
	{
		fireAnim.PushBack({ i, 0, 49, 215 });
	}
	fireAnim.loop = true;
	fireAnim.speed = 0.15f;

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
			if(acc<=maxAcc)acc +=0.05f;
			fire = true;
			position.y -= cos(angle * M_PI / 180) * acc;
			position.x += sin(angle * M_PI / 180) * acc;
		}
		if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		{
			position.y -= 5;
		}
		if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		{
			//position.x += 5;
			angle++;
			if (angle >= 360)angle = 0;
		}
		if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		{
			//position.x -= 5;
			angle--;
			if (angle <= 0)angle = 360;

		}
		
	}

	//meteor harcoded hitbox (as all hitboxes will be cuz idk any other way rn)
	if (position.x < 50 + 58 && position.x + 55 > 50 && position.y < 50 + 58 && position.y + 175 > 50) alive = false;

	//No u cant go to the center of the earth Verne
	if (position.y > 70 && angle >= 355 && angle <= 5) position.y = 70;
	else if (position.y > 70) alive = false;
	//moon is solid
	if (position.y < -5800 && angle >= 175 && angle <= 185) position.y = -5800;
	else if (position.y < -5800) alive = false;
	//enter to revive (as in real life)
	if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN) alive = true;

	return true;
}

bool Player::Update(float dt) 
{
	//camera follows player up
	if (app->render->camera.y - 250 < -(position.y))app->render->camera.y += cos(angle * M_PI / 180) * acc;

	//camera follows player down
	if (app->render->camera.y - 300 > -(position.y))app->render->camera.y -= cos(angle * M_PI / 180) * acc;

	if (position.x < -60 )position.x = 1280;
	if (position.x > 1285 )position.x = -55;

	return true;
}

bool Player::PostUpdate()
{
	//meteor texture
	Animation* meteor = &meteorAnim;
	meteor->Update();

	SDL_Rect meteorRec = meteor->GetCurrentFrame();
	app->render->DrawTexture(meteorTex, 50, 50, &meteorRec);

	//fire anim
	if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT && alive == true)
	{
		Animation* fire = &fireAnim;
		fire->Update();
		SDL_Rect fireRec = fire->GetCurrentFrame();
		app->render->DrawTexture(fireTex, position.x, position.y, &fireRec, 1.0f,angle);
	}

	//player texture
	else if (alive == true)
	{
		SDL_Rect rocketRec = { 0, 0, 50, 215 };
		app->render->DrawTexture(rocketTex, position.x, position.y, &rocketRec, 1.0f, angle);
	}

	if (position.y == (-5800) && alive==true) 
	{
		bomb = true;
	}

	if (position.y == 0 && bomb == true && alive == true)
	{
		win = true;
	}
	//explosion trigger


	if (alive == false && explosionAnim.HasFinished() == false)
	{		
		Animation* explotion = &explosionAnim;
		explotion->Update();
		SDL_Rect explosionRec = explotion->GetCurrentFrame();
		app->render->DrawTexture(explosionTex, position.x - 165, position.y - 100, &explosionRec);
	}

	if (alive == false && explosionAnim.HasFinished() == true)
	{
		SDL_Rect loseSceen = { 0, 0, 1280, 720 };
		app->render->DrawTexture(loseTex, 0, -app->render->camera.y, &loseSceen);
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

