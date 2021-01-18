#include "Player.h"
#include "App.h"
#include "Textures.h"
#include "Log.h"
#include "Render.h"
#include "Input.h"
#include "Scene.h"
#include "Window.h"
#include "Map.h"
#include "Audio.h"
#include "SceneMenu.h"
#include "FadeToBlack.h"
#include "ModuleParticles.h"
#include "Fonts.h"
#include "ModuleParticles.h"
#include "SceneWin.h"
#include "SceneLoose.h"

#include "Collisions.h"

#define TILESIZE 96
#define POSXINIT 720
#define POXYINIT 1584

Player::Player() : Module()
{
	name.Create("player");
	
	btnResume = new GuiButton(6, { NULL, NULL, BUTT_WIDTH, BUTT_HEIGHT });
	btnResume->SetObserver(this);

	btnSettings = new GuiButton(7, { NULL, NULL, BUTT_WIDTH, BUTT_HEIGHT });
	btnSettings->SetObserver(this);

	btnBack = new GuiButton(8, { NULL, NULL, BUTT_WIDTH, BUTT_HEIGHT });
	btnBack->SetObserver(this);

	btnExit = new GuiButton(9, { NULL, NULL, BUTT_WIDTH, BUTT_HEIGHT });
	btnExit->SetObserver(this);

	btnBack2 = new GuiButton(10, { 1280 / 2 - BUTT_WIDTH / 2, 570, BUTT_WIDTH, BUTT_HEIGHT });
	btnBack2->SetObserver(this);

	playerCheckFullScreen = new GuiCheckBox(2, { 1280 / 2 - SMALL_BUTT_WIDTH / 2, 500, SMALL_BUTT_WIDTH, SMALL_BUTT_HEIGHT });
	playerCheckFullScreen->SetObserver(this);

	playerSliderMusic = new GuiSlider(3, { 1280 / 2 - SLIDER_WIDTH / 2, 450, SLIDER_WIDTH, SLIDER_HEIGHT }, 0, 128);
	playerSliderMusic->SetObserver(this);

	playerSliderFx = new GuiSlider(4, { 1280 / 2 - SLIDER_WIDTH / 2, 400, SLIDER_WIDTH, SLIDER_HEIGHT }, 0, 128);
	playerSliderFx->SetObserver(this);

	for (int i = 0; i < TILESIZE * 11; i += TILESIZE)
	{
		idleAnim.PushBack({ i, 0, TILESIZE, TILESIZE });
	}
	idleAnim.loop = true;
	idleAnim.speed = 5.0f;

	for (int i = 0; i < TILESIZE * 12; i += TILESIZE)
	{
		runAnim.PushBack({ i, 0, TILESIZE, TILESIZE });
	}
	runAnim.loop = true;
	runAnim.speed = 5.0f;

	fallAnim.PushBack({ 0, 0, TILESIZE, TILESIZE });

	jumpAnim.PushBack({ 0, 0, TILESIZE, TILESIZE });

	for (int i = 0; i < TILESIZE * 7; i += TILESIZE)
	{
		deathAnim.PushBack({ i, 0, TILESIZE, TILESIZE });
	}
	deathAnim.loop = false;
	deathAnim.speed = 5.0f;

	for (int i = 0; i < TILESIZE * 6; i += TILESIZE)
	{
		doubleJumpAnim.PushBack({ i, 0, TILESIZE, TILESIZE });
	}
	doubleJumpAnim.loop = false;
	doubleJumpAnim.speed = 5.0f;

	for (int i = 0; i < TILESIZE * 7; i += TILESIZE)
	{
		appeAnim.PushBack({ i, 0, TILESIZE, TILESIZE });
	}
	appeAnim.loop = false;
	appeAnim.speed = 5.0f;

	for (int i = 0; i < 96 * 17; i += 96)
	{
		appleGUIAnim.PushBack({ i, 0, 96, 96 });
	}
	appleGUIAnim.loop = false;
	appleGUIAnim.speed = 0.4f;

	for (int i = 0; i < TILESIZE * 7; i += TILESIZE)
	{
		desAppeAnim.PushBack({ i, 0, TILESIZE, TILESIZE });
	}
	desAppeAnim.loop = false;
	desAppeAnim.speed = 5.0f;

	for (int i = 0; i < 60 * 6; i += 60)
	{
		dronAnim.PushBack({ i, 0, 60, 76 });
	}
	dronAnim.loop = true;
	dronAnim.speed = 0.4f;

	for (int i = 0; i < 40 * 8; i += 40)
	{
		chickenAnim.PushBack({ i, 0, 40, 48 });
	}
	chickenAnim.loop = true;
	chickenAnim.speed = 0.3f;


}

// Destructor
Player::~Player()
{}

bool Player::Awake()
{
	LOG("Init Player");
	bool ret = true;

	return ret;
}

bool Player::Start()
{
	LOG("Loading player textures");

	btnResume->texture = btnSettings->texture = btnBack->texture = btnBack2->texture = btnExit->texture = app->tex->Load("Assets/Textures/Interface/button.png");
	boxTex = app->tex->Load("Assets/Textures/Interface/box.png");
	btnResume->text = app->tex->Load("Assets/Textures/Interface/start.png");
	btnSettings->text = app->tex->Load("Assets/Textures/Interface/option.png");
	btnBack->text = btnBack2->text = app->tex->Load("Assets/Textures/Interface/back.png");
	btnExit->text = app->tex->Load("Assets/Textures/Interface/exit.png");

	playerSliderFx->text = app->tex->Load("Assets/Textures/Interface/sound.png");
	playerSliderMusic->text = app->tex->Load("Assets/Textures/Interface/music.png");
	playerSliderMusic->texture = playerSliderFx->texture = app->tex->Load("Assets/Textures/Interface/slider.png");

	playerCheckFullScreen->texture = app->tex->Load("Assets/Textures/Interface/small_button.png");
	playerCheckFullScreen->text = app->tex->Load("Assets/Textures/Interface/checked.png");
	playerCheckFullScreen->leftText = app->tex->Load("Assets/Textures/Interface/full_screen.png");
	
	setScore = true;
	app->LoadGameRequest();
	if (cont == false)
	app->SaveGameRequest();

	//Cargar texturas
	idleTex = app->tex->Load("Assets/Textures/Character/idle.png");
	fallTex = app->tex->Load("Assets/Textures/Character/fall.png");
	deathTex = app->tex->Load("Assets/Textures/Character/hit.png");
	runTex = app->tex->Load("Assets/Textures/Character/run.png");
	jumpTex = app->tex->Load("Assets/Textures/Character/jump.png");
	doubleJumpTex = app->tex->Load("Assets/Textures/Character/double_jump.png");
	lifesTex = app->tex->Load("Assets/Textures/Character/life.png");
	appeTex = app->tex->Load("Assets/Textures/Character/appearing.png");
	desAppeTex = app->tex->Load("Assets/Textures/Character/desappearing.png");
	appleTex = app->tex->Load("Assets/Textures/Items/Fruits/apple.png");
	dronTex = app->tex->Load("Assets/Textures/Drone/flying.png");
	chickenFlyTex = app->tex->Load("Assets/Textures/Drone/idle_skill.png");

	hitFx = app->audio->LoadFx("Assets/Audio/MyscMusic/damage.wav");
	app->fxList.Add(&hitFx);
	abilityFx = app->audio->LoadFx("Assets/Audio/MyscMusic/ability.wav");
	app->fxList.Add(&abilityFx);
	jumpFx = app->audio->LoadFx("Assets/Audio/MyscMusic/jumps.wav");
	app->fxList.Add(&jumpFx);
	pointFx = app->audio->LoadFx("Assets/Audio/MyscMusic/points.wav");
	app->fxList.Add(&pointFx);
	leafFx = app->audio->LoadFx("Assets/Audio/MyscMusic/leaf_shot.wav");
	app->fxList.Add(&leafFx);
	menuHoverFx = app->audio->LoadFx("Assets/Audio/GuiMusic/button_hover.wav");
	app->fxList.Add(&menuHoverFx);
	menuPressedFx = app->audio->LoadFx("Assets/Audio/GuiMusic/button_click.wav");
	app->fxList.Add(&menuPressedFx);

	playerColl = app->collision->AddCollider({ (int)position.x, (int)position.y, TILESIZE - 50, TILESIZE - 20}, Collider::Type::PLAYER, this);
	cameraColl = app->collision->AddCollider({ (int)position.x - 100, (int)position.y - 100, app->render->camera.w/4, app->render->camera.h / 3 + 20}, Collider::Type::CAMERA, this);
	app->render->camera.x = app->win->scale * ((cameraColl->rect.x + cameraColl->rect.w / 3) - (app->render->camera.w / 2)) * -1;
	app->render->camera.y = app->win->scale * ((cameraColl->rect.y + cameraColl->rect.h / 3) - (app->render->camera.h / 2.5)) * -1;

	playerState = NORMAL;

	playerSliderFx->value = app->volumeFX;
	playerSliderMusic->value = app->volumeMusic;


	if (app->win->fullScreen == true)
	{
		playerCheckFullScreen->checked = true;
	}
	else
	{
		playerCheckFullScreen->checked = false;
	}

	startTime = SDL_GetTicks();

	currentAnimation = &idleAnim;
	death = false;
	appear = true;
	currentTex = idleTex;
	flip = false;
	speedY = 0.3f;
	return true;
}

bool Player::PreUpdate()
{
	switch (playerState)
	{
	case Player::NORMAL:
		msLvl = (SDL_GetTicks() - startTime) / 10;
		if (msLvl >= 100)
		{
			secondsLvl += 1;
			msLvl = 0;
			startTime = SDL_GetTicks();
		}
		if (secondsLvl >= 60)
		{
			minutesLvl += 1;
			secondsLvl = 0;
		}
		break;
	case Player::EXIT:
		break;
	default:
		break;
	}

	if (appear == true)
	{
		app->render->camera.x = app->win->scale * ((cameraColl->rect.x + cameraColl->rect.w / 3) - (app->render->camera.w / 2)) * -1;
		app->render->camera.y = app->win->scale * ((cameraColl->rect.y + cameraColl->rect.h / 3) - (app->render->camera.h / 2.5)) * -1;
		currentAnimation = &appeAnim;
		currentTex = appeTex;
		if (appeAnim.finish == true)
		{
			appear = false;
			appeAnim.Reset();
		}
	}
	return true;
}

bool Player::Update(float dt)
{

	switch (playerState)
	{
	case Player::NORMAL:
		break;
	case Player::EXIT:
		return false;
		break;
	default:
		break;
	}

	return true;
}

bool Player::PostUpdate()
{

	
	return true;
}


bool Player::CleanUp()
{
	if (!active)
	{
		return true;
	}

	LOG("Unloading player");

	//Unload de texturas
	app->tex->UnLoad(idleTex);
	app->tex->UnLoad(fallTex);
	app->tex->UnLoad(deathTex);
	app->tex->UnLoad(runTex);
	app->tex->UnLoad(jumpTex);
	app->tex->UnLoad(doubleJumpTex);
	app->tex->UnLoad(lifesTex);
	app->tex->UnLoad(appeTex);
	app->tex->UnLoad(desAppeTex);
	app->tex->UnLoad(appleTex);
	app->tex->UnLoad(dronTex);
	app->tex->UnLoad(chickenFlyTex);
	app->tex->UnLoad(btnResume->texture);
	app->tex->UnLoad(boxTex);
	app->tex->UnLoad(btnResume->text);
	app->tex->UnLoad(btnSettings->text);
	app->tex->UnLoad(btnBack->text);
	app->tex->UnLoad(btnExit->text);

	app->tex->UnLoad(btnBack2->text);
	app->tex->UnLoad(playerSliderMusic->texture);
	app->tex->UnLoad(playerSliderMusic->text);
	app->tex->UnLoad(playerSliderFx->text);

	app->tex->UnLoad(playerCheckFullScreen->texture);
	app->tex->UnLoad(playerCheckFullScreen->text);
	app->tex->UnLoad(playerCheckFullScreen->leftText);

	//Remove de los colliders
	app->collision->RemoveCollider(playerColl);
	app->collision->RemoveCollider(cameraColl);

	//Unload de las pistas de audio
	app->audio->UnloadFX(jumpFx);
	app->audio->UnloadFX(hitFx);
	app->audio->UnloadFX(pointFx);
	app->audio->UnloadFX(leafFx);
	app->audio->UnloadFX(abilityFx);
	app->audio->UnloadFX(menuHoverFx);
	app->audio->UnloadFX(menuPressedFx);

	app->fxList.Clear();

	active = false;

	return true;
}

bool Player::LoadPlayerCamera()
{
	if (playerColl != NULL)
	{
		playerColl->SetPos(position.x + 25, position.y + 20);
		cameraColl->rect.x = playerColl->rect.x - 100;
		cameraColl->rect.y = playerColl->rect.y - 100;
		death = false;
	}

	return true;
}


bool Player::Die(Collider* c1, Collider* c2)
{
	dead = true;
	death = true;
	currentAnimation = &deathAnim;
	currentTex = deathTex;
	if (speedXLastFrame > 0)
	{
		flip = false;
	}
	else if (speedXLastFrame < 0)
	{
		flip = true;
	}
	app->audio->PlayFx(hitFx);
	
	return true;
}


bool Player::CameraScroll(Collider* c1, Collider* c2)
{
	if (c1->rect.x < c2->rect.x)
	{
		c2->rect.x -= c2->rect.x - c1->rect.x;
	}
	if ((c1->rect.x + c1->rect.w) > (c2->rect.x + c2->rect.w))
	{
		c2->rect.x += (c1->rect.x + c1->rect.w) - (c2->rect.x + c2->rect.w);
	}
	if (c1->rect.y < c2->rect.y)
	{
		c2->rect.y -= c2->rect.y - c1->rect.y;
	}
	if ((c1->rect.y + c1->rect.h) > (c2->rect.y + c2->rect.h))
	{
		c2->rect.y += (c1->rect.y + c1->rect.h) - (c2->rect.y + c2->rect.h);
	}

	return true;
}

bool Player::CollectApple(Collider* c1, Collider* c2)
{
	app->audio->PlayFx(pointFx);
	appleCounter += 1;
	c1->isCollected = true;
	app->moduleParticles->AddParticle(app->moduleParticles->fruitGet, c1->rect.x, c1->rect.y);
	app->collision->RemoveCollider(c1);
	appleGUICollected = true;

	return true;
}

bool Player::CollectPineapple(Collider* c1, Collider* c2)
{
	app->audio->PlayFx(pointFx);
	c1->isCollected = true;
	appleCounter += 2;
	app->moduleParticles->AddParticle(app->moduleParticles->fruitGet, c1->rect.x, c1->rect.y);
	if (app->player->lifes < 3 && app->player->lifes > 0)
	{
		app->player->lifes++;
	}
	app->collision->RemoveCollider(c1);
	appleGUICollected = true;

	return true;
}
