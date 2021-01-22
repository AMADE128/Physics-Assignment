#include "Player.h"
#include "Audio.h"
#include "Render.h"
#include "Input.h"
#include "App.h"
#include "Physics.h"
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
	playerData.state = IDLE;
	name.Create("player");
}

Player::~Player()
{}

bool Player::Start() 
{
	
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
	// Ckeck if player is in danger
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

	return true;
}

