#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Textures.h"

#include "Animation.h"
#include "p2Point.h"


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

	iPoint position;
	bool alive;
	bool fire;
private:

	float velocity;
	SDL_Texture* texture = nullptr;
	SDL_Texture* rocketTex;
	SDL_Texture* meteorTex;
	SDL_Texture* fireTex;
	SDL_Texture* explosionTex;
	Animation explosionAnim;
	Animation meteorAnim;
	Animation fireAnim;
	Animation* currentAnimation = nullptr;
	
};

#endif // _PLAYER_H_


