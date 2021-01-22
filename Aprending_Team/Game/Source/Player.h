#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Textures.h"

#include "Animation.h"
#include "p2Point.h"
#include "Body.h"

enum State {

	IDLE,
	FLY,
	TURBO,
	ATTACK,
	HIT,
	DEADING,
	DEAD
};

struct PlayerData
{
	State state;

	Animation* currentAnimation;
	uint lives = 5;
	uint respawns = 0;
	float fuel = 0;
	SDL_Rect rectPlayer = {0,0,0,0};

	SDL_Texture* texture;
	SDL_Texture* texLaserFly;
	SDL_Texture* texLaserTurbo;
	SDL_Texture* texTurboVelocity;
	SDL_Texture* texHitDead;

	static const int numPoints = 3;
	fPoint* pointsCollision;
	fPoint* pointsCollisionWorld;
	fPoint vecDir = { 0,0 };
};


class Player : public Module
{
public:

	Player();
	Player( iPoint pPosition, float pVelocity, SDL_Texture* pTexture);
	virtual ~Player();

	bool Awake(pugi::xml_node&);

	bool Start();

	bool PreUpdate();

	bool Update(float dt);

	bool PostUpdate();

	bool CleanUp();


private:



public:

	PlayerData playerData;

private:
	
	
};

#endif // _PLAYER_H_


