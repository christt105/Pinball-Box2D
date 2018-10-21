#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"

class PhysBody;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	bool CleanUp();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

public:
	p2List<PhysBody*>	bodies;
	PhysBody*			back;
	PhysBody*			flipper_left;
	PhysBody*			flipper_right;
	PhysBody*			structure_right;
	PhysBody*			structure_left;
	PhysBody*			flipper_structure_left;
	PhysBody*			flipper_structure_right;


	PhysBody*			sensor;
	bool				sensed;

	SDL_Texture*		ball_tx;
	SDL_Texture*		background_tx;
	SDL_Texture*		layout_tx;
	
	uint bonus_fx;
};
