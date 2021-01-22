#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "SceneWin.h"
#include "SceneManager.h"

#include <SDL_mixer\include\SDL_mixer.h>

#include "Defs.h"
#include "Log.h"

SceneWin::SceneWin()
{
	active = true;
	name.Create("sceneWin");
}

SceneWin::~SceneWin()
{
}

bool SceneWin::Awake()
{
	LOG("Loading SceneWin");
	bool ret = true;
	return ret;
}

bool SceneWin::Start()
{

	return true;
}

bool SceneWin::PreUpdate()
{
	return true;
}

bool SceneWin::Update(float dt)
{
	
	return true;
}

bool SceneWin::PostUpdate()
{

	return true;
}

bool SceneWin::CleanUp()
{

	return true;
}

