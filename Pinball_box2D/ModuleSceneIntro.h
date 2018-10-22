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

	
	PhysBody*			back = nullptr;
	PhysBody*			flipper_left = nullptr;
	PhysBody*			flipper_right = nullptr;
	PhysBody*			structure_right = nullptr;
	PhysBody*			structure_left = nullptr;
	PhysBody*			flipper_structure_left = nullptr;
	PhysBody*			flipper_structure_right = nullptr;
	PhysBody*			triangle_right = nullptr;
	PhysBody*			triangle_left = nullptr;
	PhysBody*			capsule1 = nullptr;
	PhysBody*			capsule2 = nullptr;
	PhysBody*			capsule3 = nullptr;
	PhysBody*			circle1 = nullptr;
	PhysBody*			circle2 = nullptr;
	PhysBody*			circle3 = nullptr;



	PhysBody*			sensor = nullptr;
	bool				sensed;

	SDL_Texture*		ball_tx = nullptr;
	SDL_Texture*		background_tx = nullptr;
	SDL_Texture*		layout_tx = nullptr;
	
	uint bonus_fx;
};
