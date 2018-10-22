#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "p2List.h"


class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	p2List<PhysBody*>	bodies;
	PhysBody*			ball;
	SDL_Texture*		ball_tx;
	SDL_Texture*		circle_robound_tx;
	
	SDL_Rect			ball_rect;
	SDL_Rect			circle_robound1_rect;
	SDL_Rect			circle_robound2_rect;

	bool dead;
};