#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Textures.h"

#include "Defs.h"
#include "Animation.h"
#include "p2Point.h"
#include "AprendingTeam.h"

enum State 
{
	IDLE,
	DEAD,
	HIT,
	FLY,
	TURBO
};

class Player : public Module
{
public:

	Player();
	Player( iPoint pPosition, float velocity, SDL_Texture* pTexture);
	virtual ~Player();

	bool Awake(pugi::xml_node&);

	bool Start();

	bool PreUpdate();

	bool Update(float dt);

	bool PostUpdate();

	bool CleanUp();

	iPoint startingPos = { PIXEL_TO_METERS(6000), PIXEL_TO_METERS(-2000) };
	iPoint position;
	fPoint directionVec = { 0,0 };
	bool alive;
	bool fire;
	bool bomb;
	bool win;
	bool landed = false;
	int angle;
	float acc;
	int maxAcc;
	int bombPos;
	float addForceX;
	float addForceY;
	PhysicsEngine* motor;
	Body* ship;

private:

	float velocity;
	SDL_Texture* texture = nullptr;
	SDL_Texture* rocketTex;
	SDL_Texture* meteorTex;
	SDL_Texture* fireTex;
	SDL_Texture* explosionTex;
	SDL_Texture* winTex;
	SDL_Texture* loseTex;
	SDL_Texture* bombTex;
	SDL_Texture* oceanTex;
	unsigned int fxWin;
	Animation explosionAnim;
	Animation meteorAnim;
	Animation fireAnim;
	Animation* currentAnimation = nullptr;

	
};

#endif // _PLAYER_H_


