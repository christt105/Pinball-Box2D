#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleCircleDirection.h"
#include "ModuleSceneIntro.h"
#include "ModulePhysics.h"
#include "ModulePlayer.h"

ModuleCircleDirection::ModuleCircleDirection(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	interval = 2000;
	interval_ball = 3000;
}

ModuleCircleDirection::~ModuleCircleDirection()
{

}

bool ModuleCircleDirection::Start() {
	LOG("Loading Circle Direction assets");

	time_start = SDL_GetTicks();
	direction = UP_LEFT;

	sensor_mark = App->physics->CreateRectangleSensor(225, 380, 10, 10);
	sensor_mark->listener = this;

	return true;
}

bool ModuleCircleDirection::CleanUp() {
	LOG("Unloading Circle Direction");

	return true;
}

update_status ModuleCircleDirection::PreUpdate() {

	if(!active_mark)
		if (time_start + interval <= SDL_GetTicks()) {
			time_start = SDL_GetTicks();
			ChangeDirection();
		}

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleCircleDirection::Update() {

	if (active_mark) {
		App->player->ball->body->SetAwake(false);
		if (time_ball + interval_ball <= SDL_GetTicks()) {
			App->player->ball->body->SetAwake(true);
			App->player->ball->body->ApplyLinearImpulse(VectorDirection(), App->player->ball->body->GetWorldCenter(), true);
			active_mark = false;
		}
	}

	App->renderer->Blit(App->scene_intro->circle_robound_tx, 200, 360, &circle);

	App->renderer->Blit(App->scene_intro->circle_robound_tx, 219, 380, &mark, 1.0F, angle);

	return update_status::UPDATE_CONTINUE;
}

void ModuleCircleDirection::OnCollision(PhysBody* bodyA, PhysBody* bodyB) {

	if (bodyA == sensor_mark && !active_mark) {
		active_mark = true;
		time_ball = SDL_GetTicks();
	}
}

b2Vec2 ModuleCircleDirection::VectorDirection() {
	b2Vec2 ret;
	switch (direction) {
	case UP_LEFT:
		ret = b2Vec2(0.5F, 1);
		break;
	case UP_RIGHT:
		ret = b2Vec2(-0.5F, 1);
		break;
	case LEFT:
		ret = b2Vec2(1, 0);
		break;
	case RIGHT:
		ret = b2Vec2(-1, 0);
		break;
	case DOWN_LEFT:
		ret = b2Vec2(0.5F, -1);
		break;
	case DOWN_RIGHT:
		ret = b2Vec2(-0.5F, -1);
		break;
	default:
		break;
	}

	return ret;
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