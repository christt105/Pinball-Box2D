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

public:


};
#endif // !__CIRCLEDIRECTION_H__
