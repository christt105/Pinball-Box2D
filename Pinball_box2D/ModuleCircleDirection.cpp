#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleCircleDirection.h"
#include "ModuleSceneIntro.h"

ModuleCircleDirection::ModuleCircleDirection(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	interval = 2000;
	direction = UP_LEFT;
}

ModuleCircleDirection::~ModuleCircleDirection()
{

}

bool ModuleCircleDirection::Start() {
	LOG("Loading Circle Direction assets");

	time_start = SDL_GetTicks();

	return true;
}

bool ModuleCircleDirection::CleanUp() {
	LOG("Unloading Circle Direction");

	return true;
}

update_status ModuleCircleDirection::PreUpdate() {

	if (time_start + interval >= SDL_GetTicks()) {
		time_start = SDL_GetTicks();
		ChangeDirection();
	}

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleCircleDirection::Update() {

	App->renderer->Blit(App->scene_intro->circle_robound_tx, 200, 360, &circle);

	return update_status::UPDATE_CONTINUE;
}

void ModuleCircleDirection::ChangeDirection() {

	direction = static_cast<Direction>(rand() % Direction::MAX);

}