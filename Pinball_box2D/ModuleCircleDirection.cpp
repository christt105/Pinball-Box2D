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

	if (time_start + interval <= SDL_GetTicks()) {
		time_start = SDL_GetTicks();
		ChangeDirection();
	}

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleCircleDirection::Update() {

	App->renderer->Blit(App->scene_intro->circle_robound_tx, 200, 360, &circle);

	App->renderer->Blit(App->scene_intro->circle_robound_tx, 219, 380, &mark, 1.0F, angle);

	return update_status::UPDATE_CONTINUE;
}

void ModuleCircleDirection::ChangeDirection() {

	direction = static_cast<Direction>(rand() % Direction::MAX);

	switch (direction) {
		case UP_LEFT:
			angle = 150.0F;
			break;

		case UP_RIGHT:
			angle = -150.0F;
			break;
		
		case LEFT:
			angle = 90.0F;
			break;
		
		case RIGHT:
			angle = -90.0F;
			break;

		case DOWN_LEFT:
			angle = 30.0;
			break;
		
		case DOWN_RIGHT:
			angle = -30.0F;
			break;
		
		default:
			angle = 0.0F;
			break;
	}

}