#ifndef __SCENE_H__
#define __SCENE_H__

#include "Module.h"
#include "Animation.h"
#include "Physics.h"
#include "SceneControl.h"

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

	// Create Entities
	void CreateWalls(Body* body, fPoint position, float w, float h, BodyClass bodyClass);
	void CreateEntity();
	void DrawStaticBodies(Body* wallDown);

	// Called before quitting
	bool CleanUp();

private:

};

#endif // __SCENE_H__