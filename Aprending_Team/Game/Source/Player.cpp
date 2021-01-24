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
	maxAcc = 20.0f;
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
	pl1Tex = app->tex->Load("Assets/Textures/planet1.png");
	pl2Tex = app->tex->Load("Assets/Textures/planet2.png");
	oceanTex = app->tex->Load("Assets/Textures/ocean.png");
	cloudTex = app->tex->Load("Assets/Textures/clouds.png");
	fuelTex = app->tex->Load("Assets/Textures/fuel.png");
	fxWin = app->audio->PlayMusic("Assets/Audio/Hymn.wav");
	app->fxList.Add(&fxWin);


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
	ship->SetPosition(startingPos);
	ship->SetMass(125.5f);
	ship->SetClassType(Class::PLAYER);
	motor = new PhysicsEngine;

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
		ship->ResetForce();
		if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		{
			if (acc <= maxAcc)acc += 0.1f;
			addForceX = sin(angle * M_PI / 180) * acc;
			if (addForceX > 100) addForceX = 100;
			else if (addForceX < -100) addForceX = -100;
			addForceY = -cos(angle * M_PI / 180) * acc;
			if (addForceY > 100) addForceX = 100;
			else if (addForceY < -100) addForceX = -100;

			ship->AddForce({ addForceX , addForceY });
			
			fire = true;
			landed = false;


			if (fuelC < 750)
			{
				fuelC++;
			}
			if (fuelC == 750)
			{
				fuelC = 0;
				fuel--;
			}
		}
		else if (acc > 0)acc -= 0.05;


		if (landed == false)
		{
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

		if(landed != true)
		{
			motor->ApplyForcesToWorld(ship);
			motor->MRUA(ship, 1);
		}
		else
		{
			ship->setVelocity({ 0,0 });
			ship->SetAcceleration({ 0,0 });
			ship->ResetForce();
			addForceX = addForceY = 0;
		}
	}

	//meteor harcoded hitbox (as all hitboxes will be cuz idk any other way rn)
	
	if (ship->position.x < 250 + 58 && ship->position.x + 55 > 250 && ship->position.y < -2500 + 58 && ship->position.y + 175 > -2500) alive = false;

	if (ship->position.x < 570 + 58 && ship->position.x + 55 > 570 && ship->position.y < -3550 + 58 && ship->position.y + 175 > -3550) alive = false;

	if (ship->position.x < 700 + 58 && ship->position.x + 55 > 700 && ship->position.y < -4100 + 58 && ship->position.y + 175 > -4100) alive = false;

	//No you cant go to the center of the earth Verne
	if (ship->position.y > 70 && angle > 355  && ship->velocity.y < 3.0f && ship->velocity.x < 3.0f || ship->position.y > 70 && angle < 5  && velocity < 100 && ship->velocity.y < 5.0f && ship->velocity.x < 5.0f)
	{
		ship->setVelocity({ 0, 0 }); 
		ship->SetAcceleration({ 0,-2000000 });
		ship->SetPosition({ ship->position.x, 70 });
		landed = true;
	}
	else if(ship->position.y > 75 ) alive = false;
	
	if (fuel == 0)alive = false;

	if (ship->position.y == 70 && alive == true && bomb == true)
	{
		win = true;
	}
	
	//moon is solid
	if (ship->position.y <= -5800 && angle >= 175 && angle <= 185 && ship->velocity.y > -3.0f && ship->velocity.x < 3.0f && ship->velocity.x > -3.0f)
	{
		ship->position.y = -5800;
		bomb = true;
		bombPos = ship->position.x;
	}
	else if (ship->position.y <= -5800)
	{
		alive = false;
	}
	if (ship->position.y == (-5800) && alive == true)
	{
		bomb = true;
	}
	
	else if (ship->position.y < -5800) alive = false;

	//enter to revive (as in real life)
	if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
	{
		win = false;
		alive = true;
		ship->SetPosition(startingPos);
		angle = 0;
		acc = 0;
		bomb = false;
		ship->velocity.x = 0.0f;
		ship->velocity.y = 0.0f;
		fuel = 4;
		fuelC = 0;
	}
	return true;
}

bool Player::Update(float dt) 
{
	//camera follows player up

	if (app->render->camera.y - 250 < -(ship->position.y))app->render->camera.y = -ship->position.y + 250;

	//camera follows player down

	if (app->render->camera.y - 300 > -(ship->position.y))
	{
		app->render->camera.y = -ship->position.y + 300;
		if (app->render->camera.y < 0)app->render->camera.y = 0;
	}

	if (ship->position.x < -60 )ship->position.x = 1280;
	if (ship->position.x > 1285 )ship->position.x = -55;

	return true;
}

bool Player::PostUpdate()
{

	SDL_Rect pl1Rec = { 0, 0, 884, 884 };
	app->render->DrawTexture(pl1Tex, 800, -2600, &pl1Rec);

	SDL_Rect pl2Rec = { 0, 0, 884, 884 };
	app->render->DrawTexture(pl2Tex, -200, -3800, &pl2Rec);

	app->audio->PlayFx(fxWin);
	//meteor texture
	Animation* meteor = &meteorAnim;
	meteor->Update();

	SDL_Rect meteorRec = meteor->GetCurrentFrame();
	app->render->DrawTexture(meteorTex, 250, -2500, &meteorRec);

	SDL_Rect meteorRec2 = meteor->GetCurrentFrame();
	app->render->DrawTexture(meteorTex, 570, -3550, &meteorRec2);

	SDL_Rect meteorRec3 = meteor->GetCurrentFrame();
	app->render->DrawTexture(meteorTex, 700, -4100, &meteorRec3);


	//bomb print
	if (bomb == true)
	{
		SDL_Rect bombRec = { 0, 0, 50, 50 };
		app->render->DrawTexture(bombTex, bombPos, -5800, &bombRec);
	}

	

	//ocean print
	/*if (bomb == true)
	{
		SDL_Rect oceanRec = { 0, 0, 1280, 1900 };
		app->render->DrawTexture(oceanTex, 0, -1025, &oceanRec);
	}*/
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

	
	SDL_Rect cloudRec = { 0, 0, 2360, 984 };
	app->render->DrawTexture(cloudTex, -500, -1500, &cloudRec);
	
	if (fuel == 4)
	{
		SDL_Rect fuelRec1 = { 0, 0, 46, 20 };
		app->render->DrawTexture(fuelTex, 0, -app->render->camera.y, &fuelRec1);
	}

	if (fuel == 3)
	{
		SDL_Rect fuelRec2 = { 47, 0, 46, 20 };
		app->render->DrawTexture(fuelTex, 0, -app->render->camera.y, &fuelRec2);
	}

	if (fuel == 2)
	{
		SDL_Rect fuelRec3 = { 94, 0, 46, 20 };
		app->render->DrawTexture(fuelTex, 0, -app->render->camera.y, &fuelRec3);
	}

	if (fuel == 1)
	{
		SDL_Rect fuelRec4 = { 141, 0, 46, 20 };
		app->render->DrawTexture(fuelTex, 0, -app->render->camera.y, &fuelRec4);
	}

	if (fuel == 0)
	{
		SDL_Rect fuelRec5 = { 188, 0, 46, 20 };
		app->render->DrawTexture(fuelTex, 0, -app->render->camera.y, &fuelRec5);
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
		app->audio->PlayFx(fxWin);
	}
	return true;	
}

bool Player::CleanUp()
{
	if (!active)
		return true;
	app->tex->UnLoad(explosionTex);
	app->tex->UnLoad(rocketTex);
	app->tex->UnLoad(oceanTex);
	app->tex->UnLoad(meteorTex);
	app->tex->UnLoad(fireTex);
	app->tex->UnLoad(winTex);
	app->tex->UnLoad(loseTex);
	app->tex->UnLoad(bombTex);
	app->tex->UnLoad(cloudTex);


	app->audio->UnloadFX(fxWin);
	app->fxList.Clear();
	active = false;

	return true;
}

