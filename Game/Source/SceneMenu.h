#ifndef __SCENEMENU_H__
#define __SCENEMENU_H__

#include "Module.h"

struct SDL_Texture;

class SceneMenu : public Module
{
public:

	enum MenuStates
	{
		NORMAL,
		SETTINGS,
		CREDITS,
		EXIT
	};

	SceneMenu();

	// Destructor
	virtual ~SceneMenu();

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


	SDL_Texture* menuTex;
	SDL_Texture* boxTex;
	SDL_Texture* creditsTex;
	SDL_Texture* licenseTex;

	char btnCreditsText[10] = { "\0" };

	MenuStates menuState = NORMAL;

	unsigned int pressedFx;
	unsigned int hoverFx;
	unsigned int startButtonFx;



	float valueToVolume = 0;

private:

	int currentLvl;
};

#endif // __SCENE_H__