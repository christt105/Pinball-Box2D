#ifndef __CIRCLEDIRECTION_H__
#define __CIRCLEDIRECTION_H__

#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"

class b2Vec2;

class ModuleCircleDirection : public Module
{
public:
	ModuleCircleDirection(Application* app, bool start_enabled = true);
	~ModuleCircleDirection();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	bool CleanUp();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

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
	b2Vec2 VectorDirection();

private:
	Uint32	interval = 2000; //2 seconds interval btw mark changes direction
	Uint32	interval_ball = 3000; //3 seconds interval ball is suspended on air

	Uint32	time_start = 0;
	Uint32	time_ball = 0;

	float	angle = 0.0F;


public:
	SDL_Rect	circle = { 0,0,58,55 };
	SDL_Rect	mark = { 77,18,21,21 };

	PhysBody*	sensor_mark = nullptr;
	bool		active_mark = false;

	Direction	direction;

};
#endif // !__CIRCLEDIRECTION_H__
