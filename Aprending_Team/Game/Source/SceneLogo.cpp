#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Render.h"
#include "SceneLogo.h"
#include "Audio.h"

#include "Defs.h"
#include "Log.h"

#define LOGO_FADE_SPEED 500.0f

SceneLogo::SceneLogo()
{
	active = true;
	name.Create("sceneLogo");
}

SceneLogo::~SceneLogo()
{
}

bool SceneLogo::Awake()
{
	LOG("Loading SceneLogo");
	bool ret = true;
	return ret;
}

bool SceneLogo::Start()
{


	return true;
}

bool SceneLogo::PreUpdate()
{
	return true;
}

bool SceneLogo::Update(float dt)
{

	return true;
}

bool SceneLogo::PostUpdate()
{
	bool ret = true;
	
	return ret;
}

bool SceneLogo::CleanUp()
{
	
	return true;
}


