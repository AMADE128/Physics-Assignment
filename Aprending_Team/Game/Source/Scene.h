#ifndef __SCENE_H__
#define __SCENE_H__

#include "Module.h"
#include "Animation.h"
#include "SceneControl.h"

struct SDL_Texture;

class Scene : public SceneControl
{
public:

	Scene();

	// Destructor
	virtual ~Scene();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();


	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	SDL_Texture* backgroundTex;
	SDL_Texture* moonTex;
	SDL_Texture* earthTex;
	SDL_Texture* cloudTex;
	SDL_Texture* rocketTex;

private:
};

#endif // __SCENE_H__