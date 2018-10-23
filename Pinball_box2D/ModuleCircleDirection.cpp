#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleCircleDirection.h"

ModuleCircleDirection::ModuleCircleDirection(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	
}

ModuleCircleDirection::~ModuleCircleDirection()
{

}

bool ModuleCircleDirection::Start() {
	LOG("Loading Circle Direction assets");

	return true;
}

bool ModuleCircleDirection::CleanUp() {
	LOG("Unloading flippers");

	return true;
}

update_status ModuleCircleDirection::PreUpdate() {

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleCircleDirection::Update() {

	return update_status::UPDATE_CONTINUE;
}