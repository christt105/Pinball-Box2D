#ifndef __CIRCLEDIRECTION_H__
#define __CIRCLEDIRECTION_H__

#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"

class ModuleCircleDirection : public Module
{
public:
	ModuleCircleDirection(Application* app, bool start_enabled = true);
	~ModuleCircleDirection();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	bool CleanUp();

	enum Direction {
		UP_LEFT,
		UP_RIGHT,
		LEFT,
		RIGHT,
		DOWN_LEFT,
		DOWN_RIGHT,

		MAX
	};

private:
	void ChangeDirection();

private:
	Uint32	interval = 2000; //2 seconds
	Uint32	time_start = 0;

	float	angle = 0.0F;

public:
	SDL_Rect	circle = { 0,0,46,46 };
	SDL_Rect	mark = { 61,14,18,17 };

	Direction	direction;

};
#endif // !__CIRCLEDIRECTION_H__
