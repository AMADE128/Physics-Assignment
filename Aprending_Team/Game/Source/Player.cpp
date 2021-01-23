#include "Player.h"
#include "Audio.h"
#include "Render.h"
#include "Input.h"
#include "App.h"
#include "SceneManager.h"
#include "Scene.h"
#include "AprendingTeam.h"

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
	motor = new PhysicsEngine;
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
	bombTex = app->tex->Load("Assets/Textures/bomb.png");
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

	ship = new Body;
	ship->SetClassType(Class::PLAYER);
	ship->SetMass(125.5f);
	ship->SetPosition({ 640, 70 });
	ship->SetBodyType(BodyType::DYNAMIC);

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
			ship->AddForce({ sin(angle * M_PI / 180) * acc,cos(angle * M_PI / 180) * acc });
			fire = true;
		}
		else if (acc > 0)acc -= 0.05;
		if (acc < 0)acc = 0;
		//position.y -= cos(angle * M_PI / 180) * acc;
		//position.x += sin(angle * M_PI / 180) * acc;
		
		if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		{
			ship->position.y -= 5;
		}
		if (app->input->GetKey(SDL_SCANCODE_P) == KEY_REPEAT)
		{
			ship->position.x += 5;
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
	if (ship->position.x < 50 + 58 && ship->position.x + 55 > 50 && ship->position.y < 50 + 58 && ship->position.y + 175 > 50) alive = false;

	//No u cant go to the center of the earth Verne
	if (ship->position.y > 70 && angle > 355 || ship->position.y > 70 && angle < 5) ship->position.y = 70;
	else if (ship->position.y > 70) alive = false;
	
	
	
	//moon is solid
	if (ship->position.y <= -5800 && angle >= 175 && angle <= 185)
	{
		ship->position.y = -5800;
		bomb = true;
		bombPos = ship->position.x;
	}

	if (ship->position.y == (-5800) && alive == true)
	{
		bomb = true;
	}

	if (ship->position.y == 70 && bomb == true && alive == true)
	{
		win = true;
	}
	
	else if (ship->position.y < -5800) alive = false;
	//enter to revive (as in real life)
	if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
	{
		alive = true;
		ship->position.y = 70;
		angle = 0;
		acc = 0;
		bomb = false;
		win = false;
	}

	if (alive == true)
	{
		motor->ApplyForcesToWorld(app->player->ship);

		motor->MRUA(ship, app->secondsSinceStartup);

	}
	return true;
}

bool Player::Update(float dt) 
{
	//camera follows player up

	if (app->render->camera.y - 250 < -(ship->position.y))app->render->camera.y = -ship->position.y + 250;

	//camera follows player down

	if (app->render->camera.y - 300 > -(ship->position.y))app->render->camera.y = -ship->position.y + 300;

	if (ship->position.x < -60 )ship->position.x = 1280;
	if (ship->position.x > 1285 )ship->position.x = -55;

	return true;
}

bool Player::PostUpdate()
{
	//meteor texture
	Animation* meteor = &meteorAnim;
	meteor->Update();

	SDL_Rect meteorRec = meteor->GetCurrentFrame();
	app->render->DrawTexture(meteorTex, 50, 50, &meteorRec);

	//bomb print
	if (bomb == true)
	{
		SDL_Rect bombRec = { 0, 0, 50, 50 };
		app->render->DrawTexture(bombTex, bombPos, -5800, &bombRec);
	}

	//fire anim
	if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT && alive == true)
	{
		Animation* fire = &fireAnim;
		fire->Update();
		SDL_Rect fireRec = fire->GetCurrentFrame();
		app->render->DrawTexture(fireTex, ship->position.x, ship->position.y, &fireRec, 1.0f,angle);
	}

	//player texture
	else if (alive == true)
	{
		SDL_Rect rocketRec = { 0, 0, 50, 215 };
		app->render->DrawTexture(rocketTex, ship->position.x, ship->position.y, &rocketRec, 1.0f, angle);
	}

	
	//explosion trigger
	if (alive == false && explosionAnim.HasFinished() == false)
	{		
		Animation* explotion = &explosionAnim;
		explotion->Update();
		SDL_Rect explosionRec = explotion->GetCurrentFrame();
		app->render->DrawTexture(explosionTex, ship->position.x - 165, ship->position.y - 100, &explosionRec);
	}

	//lose screen print
	if (alive == false && explosionAnim.HasFinished() == true)
	{
		SDL_Rect loseSceen = { 0, 0, 1280, 720 };
		app->render->DrawTexture(loseTex, 0, -app->render->camera.y, &loseSceen);
	}

	//win screen print
	if (win == true) 
	{
		SDL_Rect winSceen = { 0, 0, 1280, 720 };
		app->render->DrawTexture(winTex, 0, -app->render->camera.y, &winSceen);
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

