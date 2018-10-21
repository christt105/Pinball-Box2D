#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleFlipper.h"
#include "ModulePhysics.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"


ModuleFlipper::ModuleFlipper(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	flipper_tx = nullptr;
}

ModuleFlipper::~ModuleFlipper()
{}

bool ModuleFlipper::Start() {
	LOG("Loading Flippers assets");
	bool ret = true;

	flipper_tx = App->textures->Load("pinball/Textures/flippersAndTriangularBoundsFx.png");
	int flipper_left_chain[26] = {
			-3, -11,
			57, -7,
			62, -6,
			66, -2,
			66, 3,
			64, 9,
			57, 12,
			-3, 13,
			-9, 9,
			-12, 3,
			-11, -4,
			-7, -8,
			-3, -11
	};

	flipper_left = App->physics->CreateChain(155, 925, flipper_left_chain, 25, b2_staticBody);

	return ret;
}

bool ModuleFlipper::CleanUp() {
	LOG("Unloading flippers");

	App->textures->Unload(flipper_tx);
	flipper_tx = nullptr;

	flipper_left = nullptr;
	flipper_right = nullptr;

	return true;
}

update_status ModuleFlipper::PreUpdate() {

	if (App->input->GetKey(SDL_SCANCODE_LEFT) && !action_left)
		action_left = true;

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) && !action_right)
		action_right = true;

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleFlipper::Update() {
	if (action_left) {
		MoveLeft();
	}

	if (action_right) {
		MoveRight();
	}

	int flipper_left_x, flipper_left_y, flipper_right_x, flipper_right_y;

	flipper_left->GetPosition(flipper_left_x, flipper_left_y);
	//flipper_right->GetPosition(flipper_right_x, flipper_right_y);


	App->renderer->Blit(flipper_tx, flipper_left_x, flipper_left_y, NULL, 1.0F, flipper_left->GetRotation()/*,flipper_left_pivotX,flipper_left_pivotY*/);


	return update_status::UPDATE_CONTINUE;
}

void ModuleFlipper::MoveLeft() {

}

void ModuleFlipper::MoveRight() {

}

update_status ModuleFlipper::PostUpdate() {


	return update_status::UPDATE_CONTINUE;
}