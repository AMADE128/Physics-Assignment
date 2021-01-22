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
	// Active Motor Engine
	app->physics->Init();
	app->physics->Start();


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
	bool ret = true;

	return ret;
}

void Scene::DrawStaticBodies(Body* body)
{
	
}

void Scene::CreateWalls(Body* body, fPoint position, float w, float h, BodyClass bodyClass)
{
	
}

void Scene::CreateEntity()
{

}

void Scene::ComprobeStateAsteroids()
{
	
}

// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}
