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
	//int flipper_left_chain[26] = {
	//		-3, -11,
	//		57, -7,
	//		62, -6,
	//		66, -2,
	//		66, 3,
	//		64, 9,
	//		57, 12,
	//		-3, 13,
	//		-9, 9,
	//		-12, 3,
	//		-11, -4,
	//		-7, -8,
	//		-3, -11
	//};
	int flipper_left_chain[8]
	{
		0,  12,
		0 ,-12,
		70,  7,
		70 ,-7
	};

	left.flipper = App->physics->CreatePolygon(160, 925, flipper_left_chain, 8);
	left.rotor = App->physics->CreateCircleStatic(160, 925, 1);

	b2RevoluteJointDef revolutionDef;
	revolutionDef.bodyA = left.rotor->body;
	revolutionDef.bodyB = left.flipper->body;
	revolutionDef.collideConnected = false;
	revolutionDef.localAnchorA.Set(0, 0);
	revolutionDef.localAnchorB.Set(0, 0);
	revolutionDef.enableLimit = true;
	revolutionDef.upperAngle = 30 * DEGTORAD; 
	revolutionDef.lowerAngle = -25 * DEGTORAD;
	left.joint = (b2RevoluteJoint*)App->physics->CreateJoint(&revolutionDef);;

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
	}

	/*if (action_right) {
		MoveRight();
	}*/
	LOG("%.2f", left.flipper->GetRotation());
	int flipper_left_x, flipper_left_y, flipper_right_x, flipper_right_y;

	left.flipper->GetPosition(flipper_left_x, flipper_left_y);
	//flipper_right->GetPosition(flipper_right_x, flipper_right_y);


	//App->renderer->Blit(flipper_tx, flipper_left_x, flipper_left_y, NULL, 1.0F, left.flipper->GetRotation()/*,flipper_left_pivotX,flipper_left_pivotY*/);


	return update_status::UPDATE_CONTINUE;
}

void ModuleFlipper::MoveLeft() {
	left.flipper->body->ApplyAngularImpulse(2.0f, true);
}

void ModuleFlipper::MoveRight() {

}

update_status ModuleFlipper::PostUpdate() {


	return update_status::UPDATE_CONTINUE;
}