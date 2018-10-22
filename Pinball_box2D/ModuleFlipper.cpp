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

	int flipper_left_chain[14] = {
			6, 13,
			12, 1,
			76, 5,
			85, 13,
			79, 22,
			16, 25,
			6, 13
	};

	left.flipper = App->physics->CreatePolygon(100, 920, flipper_left_chain, 14);
	left.rotor = App->physics->CreateCircleStatic(160, 930, 3);

	b2RevoluteJointDef revolutionDef;
	revolutionDef.bodyA = left.rotor->body;
	revolutionDef.bodyB = left.flipper->body;
	revolutionDef.collideConnected = false;
	revolutionDef.localAnchorA.Set(0, 0);
	revolutionDef.localAnchorB.Set(PIXEL_TO_METERS(20), PIXEL_TO_METERS(5));
	revolutionDef.enableLimit = true;
	revolutionDef.upperAngle = 30 * DEGTORAD; 
	revolutionDef.lowerAngle = -20 * DEGTORAD;
	left.joint = (b2RevoluteJoint*)App->physics->CreateJoint(&revolutionDef);

	return ret;
}

bool ModuleFlipper::CleanUp() {
	LOG("Unloading flippers");

	App->textures->Unload(flipper_tx);
	flipper_tx = nullptr;

	left.flipper = nullptr;

	return true;
}

update_status ModuleFlipper::PreUpdate() {

	if (App->input->GetKey(SDL_SCANCODE_LEFT) && !left.mov)
		left.mov = true;

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleFlipper::Update() {
	if (left.mov) {
		MoveLeft();
		left.mov = false;
	}

	/*if (action_right) {
		MoveRight();
	}*/
	int flipper_left_x, flipper_left_y, flipper_right_x, flipper_right_y;

	left.flipper->GetPosition(flipper_left_x, flipper_left_y);
	//flipper_right->GetPosition(flipper_right_x, flipper_right_y);

	SDL_Rect r = { 0,0,87,27 };
	App->renderer->Blit(flipper_tx, flipper_left_x, flipper_left_y, &r, 1.0F, left.flipper->GetRotation(), 5, 5);


	return update_status::UPDATE_CONTINUE;
}

void ModuleFlipper::MoveLeft() {
	left.flipper->body->ApplyAngularImpulse(-3.0f, true);
}

void ModuleFlipper::MoveRight() {

}

update_status ModuleFlipper::PostUpdate() {


	return update_status::UPDATE_CONTINUE;
}