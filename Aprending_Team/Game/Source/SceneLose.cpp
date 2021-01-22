#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "SceneLose.h"
#include "SceneManager.h"

#include <SDL_mixer\include\SDL_mixer.h>

#include "Defs.h"
#include "Log.h"

SceneLose::SceneLose()
{
	active = true;
	name.Create("sceneLose");
}

SceneLose::~SceneLose()
{
}

bool SceneLose::Awake()
{
	LOG("Loading SceneLose");
	bool ret = true;
	return ret;
}

bool SceneLose::Start()
{

	return true;
}

bool SceneLose::PreUpdate()
{
	return true;
}

bool SceneLose::Update(float dt)
{
	
	return true;
}

bool SceneLose::PostUpdate()
{
	bool ret = true;

	return ret;
}

bool SceneLose::CleanUp()
{

	return true;
}
