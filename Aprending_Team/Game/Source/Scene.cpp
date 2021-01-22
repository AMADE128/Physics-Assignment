#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Font.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "Player.h"
#include "HUD.h"
#include "SceneManager.h"

#include "Defs.h"
#include "Log.h"

Scene::Scene() : SceneControl()
{
	active = true;
	name.Create("scene");
}

// Destructor
Scene::~Scene()
{}

// Called before render is available
bool Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool Scene::Start()
{
	backgroundTex = app->tex->Load("Assets/Textures/background.png");
	moonTex = app->tex->Load("Assets/Textures/moon.png");
	earthTex = app->tex->Load("Assets/Textures/earth.png");
	cloudTex = app->tex->Load("Assets/Textures/clouds.png");
	return true;
}

// Called each loop iteration
bool Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool Scene::Update(float dt)
{
	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	SDL_Rect backgroundRec = { 0, 0, 1280, 7108 };
	app->render->DrawTexture(backgroundTex, 0, -6000, &backgroundRec);

	SDL_Rect moonRec = { 0, 0, 1280, 804 };
	app->render->DrawTexture(moonTex, 0, -6000, &moonRec);

	SDL_Rect earthRec = { 0, 0, 1280, 1000 };
	app->render->DrawTexture(earthTex, 0, 110, &earthRec);

	SDL_Rect cloudRec = { 0, 0, 2360, 984 };
	app->render->DrawTexture(cloudTex, -500, -1500, &cloudRec); 
	
	
	bool ret = true;

	return ret;
}

// Called before quitting
bool Scene::CleanUp()
{
	if (!active)
		return true;
	app->tex->UnLoad(backgroundTex);
	app->tex->UnLoad(moonTex);
	app->tex->UnLoad(earthTex);
	app->tex->UnLoad(cloudTex);

	LOG("Freeing scene");
	active = false;

	return true;
}
