#ifndef __SCENEINTRO_H__
#define __SCENEINTRO_H__

#include "SceneControl.h"
#include "Animation.h"

struct SDL_Texture;

struct AnimationIntro
{
	iPoint position;
	Animation* currentAnimation;
	SDL_Texture* texture;
};

class SceneIntro : public SceneControl
{
public:

	SceneIntro();

	// Destructor
	virtual ~SceneIntro();

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

private:

};

#endif // __SCENEINTRO_H__





