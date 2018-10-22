#ifndef __MODULEFLIPPER_H__
#define __MODULEFLIPPER_H__

#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"

class PhysBody;
class b2RevoluteJoint;

struct Flipper {
	PhysBody*			flipper = nullptr;
	PhysBody*			rotor = nullptr;

	bool				mov = false;

	b2RevoluteJoint*	joint = nullptr;
};

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
	Flipper		left;
	Flipper		right;

	uint fx_flipper;

	SDL_Texture*		flipper_tx = nullptr;

};
#endif // !__MODULEFLIPPER_H__