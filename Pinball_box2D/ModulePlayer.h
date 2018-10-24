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
	
	SDL_Rect			ball_rect;	
	SDL_Rect			live_rect;


	bool dead = false;
	bool game_over = false;
	uint lives = 5;
	bool tp1;
	bool tp2;
	uint counter = 2;
	uint counter2 = 0;
};