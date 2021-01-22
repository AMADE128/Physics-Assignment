#include "App.h"
#include "Window.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Player.h"
#include "Font.h"
#include "HUD.h"
#include "SceneManager.h"
#include "Scene.h"

#include "Log.h"
#include "Defs.h"

HUD::HUD() : Module()
{
	name.Create("HUD");
}

HUD::~HUD()
{
}

bool HUD::Awake(pugi::xml_node&)
{
	LOG("Loading HUD");
	bool ret = true;

	return ret;
}

bool HUD::Start()
{
	return true;
}

bool HUD::PreUpdate()
{
	return true;
}

bool HUD::Update(float dt)
{
	return true;
}

bool HUD::PostUpdate()
{
	return true;
}

bool HUD::CleanUp()
{
	if (!active)
		return true;
	active = false;

	return true;
}
