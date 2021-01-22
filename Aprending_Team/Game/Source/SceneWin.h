#ifndef __SCENEWIN_H__
#define __SCENEWIN_H__

#include "SceneControl.h"

struct SDL_Texture;

class SceneWin :public SceneControl
{
public:

	SceneWin();

	// Destructor
	virtual ~SceneWin();

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

	int GetNumThisScene() { return 0; };

private:

};

#endif // !__SCENEWIN_H__

