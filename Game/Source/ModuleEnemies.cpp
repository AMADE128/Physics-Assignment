#include "ModuleEnemies.h"

#include "App.h"

#include "Collisions.h"
#include "Render.h"
#include "Textures.h"
#include "Audio.h"
#include "FadeToBlack.h"
#include "Player.h"
#include "Fonts.h"
#include "Log.h"
#include "Window.h"
#include <stdio.h>
#include "Point.h"
#include "Map.h"

#include "Enemy.h"

#include "SDL/include/SDL.h"


ModuleEnemies::ModuleEnemies() : Entity()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;
}

ModuleEnemies::~ModuleEnemies()
{

}

bool ModuleEnemies::Start()
{
	LOG("Loading enemies textures and sounds");
	bunnyIdle = app->tex->Load("Assets/Textures/Enemies/Bunny/idle.png");
	bunnyRun = app->tex->Load("Assets/Textures/Enemies/Bunny/run.png");
	bunnyFall = app->tex->Load("Assets/Textures/Enemies/Bunny/fall.png");

	birdFly = app->tex->Load("Assets/Textures/Enemies/Bird/flying.png");

	bunnyDieFx = app->audio->LoadFx("Assets/Audio/EnemiesMusic/bunny_hit.wav");
	app->fxList.Add(&bunnyDieFx);
	birdDieFx = app->audio->LoadFx("Assets/Audio/EnemiesMusic/bird_hit.wav");
	app->fxList.Add(&birdDieFx);

	return true;
}

bool ModuleEnemies::PreUpdate()
{
	bool ret = true;

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr && enemies[i]->deathFinish == true)
		{
			LOG("Despawning enemy");
			app->collision->RemoveCollider(enemies[i]->collider);
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	return ret;
}

bool ModuleEnemies::Update(float dt)
{
	bool ret = true;
	EnemiesSpawn();

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			if (app->player->playerState == app->player->NORMAL)
			{
				enemies[i]->Update();
			}
		}
	}
	return ret;
}

bool ModuleEnemies::PostUpdate()
{
	bool ret = true;

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			enemies[i]->Draw();
		}
	}

	return ret;
}

// Called before quitting
bool ModuleEnemies::CleanUp()
{
	LOG("Freeing all enemies");

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			enemies[i]->CleanUp();
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	app->tex->UnLoad(bunnyFall);
	app->tex->UnLoad(bunnyHit);
	app->tex->UnLoad(bunnyIdle);
	app->tex->UnLoad(bunnyRun);
	app->tex->UnLoad(birdFly);

	app->audio->UnloadFX(bunnyDieFx);
	app->audio->UnloadFX(birdDieFx);
	app->fxList.Clear();

	active = false;

	return true;
}

bool ModuleEnemies::AddEnemy(EnemyType type, int x, int y)
{
	bool ret = false;

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (spawnQueue[i].type == EnemyType::NO_TYPE)
		{
			spawnQueue[i].type = type;
			spawnQueue[i].x = x;
			spawnQueue[i].y = y;
			ret = true;
			break;
		}
	}

	return ret;
}

void ModuleEnemies::EnemiesSpawn()
{
	// Iterate all the enemies queue
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (spawnQueue[i].type != EnemyType::NO_TYPE)
		{
			LOG("Spawning enemy at %d", spawnQueue[i].x);
			SpawnEnemy(spawnQueue[i]);
			spawnQueue[i].type = EnemyType::NO_TYPE;
		}
	}
}

void ModuleEnemies::SpawnEnemy(const EnemySpawnpoint& info)
{
	// Find an empty slot in the enemies array
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] == nullptr)
		{
		}
	}
}

bool ModuleEnemies::Die(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1)
		{
			enemies[i]->Die(c1, c2);

			break;
		}
	}

	return true;
}


iPoint ModuleEnemies::MapToWorld(iPoint position)
{
	iPoint mapDimensions = app->map->GetDimensionsMap();
	iPoint ret;
	ret.x = position.x * mapDimensions.x;
	ret.y = position.y * mapDimensions.y;
	return ret;
}