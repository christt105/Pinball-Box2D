#ifndef __MODULEFLIPPER_H__
#define __MODULEFLIPPER_H__

#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"

class PhysBody;

class ModuleFlipper : public Module
{
public:
	ModuleFlipper(Application* app, bool start_enabled = true);
	~ModuleFlipper();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	void MoveLeft();
	void MoveRight();

public:
	PhysBody*			flipper_left;
	PhysBody*			motor_left;
	PhysBody*			flipper_right;
	PhysBody*			motor_right;

	bool action_left = false;
	bool action_right = false;

	SDL_Texture*		flipper_tx;

};
#endif // !__MODULEFLIPPER_H__