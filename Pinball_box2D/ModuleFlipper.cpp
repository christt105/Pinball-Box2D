#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleFlipper.h"
#include "ModulePhysics.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"


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

	int flipper_right_chain[14] = {
			-6, 13,
			-12, 1,
			-76, 5,
			-85, 13,
			-79, 22,
			-16, 25,
			-6, 13
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

	right.flipper = App->physics->CreatePolygon(300, 920, flipper_right_chain, 14);
	right.rotor = App->physics->CreateCircleStatic(300, 930, 3);

	revolutionDef.bodyA = right.rotor->body;
	revolutionDef.bodyB = right.flipper->body;
	revolutionDef.collideConnected = false;
	revolutionDef.localAnchorA.Set(0, 0);
	revolutionDef.localAnchorB.Set(PIXEL_TO_METERS(-21), PIXEL_TO_METERS(5));
	revolutionDef.enableLimit = true;
	revolutionDef.upperAngle = 30 * DEGTORAD;
	revolutionDef.lowerAngle = -20 * DEGTORAD;
	right.joint = (b2RevoluteJoint*)App->physics->CreateJoint(&revolutionDef);

	fx_flipper = App->audio->LoadFx("pinball/Audio/SFx/Flipper.wav");

	return ret;
}

bool ModuleFlipper::CleanUp() {
	LOG("Unloading flippers");

	App->textures->Unload(flipper_tx);
	flipper_tx = nullptr;

	left.flipper = nullptr;
	left.rotor = nullptr;
	right.flipper = nullptr;
	right.rotor = nullptr;

	return true;
}

update_status ModuleFlipper::PreUpdate() {

	if (App->input->GetKey(SDL_SCANCODE_LEFT) && !left.mov) {
		if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN)
			App->audio->PlayFx(fx_flipper);
		left.mov = true;
	}
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) && !right.mov) {
		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
			App->audio->PlayFx(fx_flipper);
		right.mov = true;
	}

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleFlipper::Update() {

	if (left.mov) {
		MoveLeft();
		left.mov = false;
	}
	else {
		left.flipper->body->ApplyAngularImpulse(0.2f, true); //Apply force contraty to set origin faster
	}

	if (right.mov) {
		MoveRight();
		right.mov = false;
	}
	else {
		right.flipper->body->ApplyAngularImpulse(-0.2f, true);
	}

	int flipper_left_x, flipper_left_y, flipper_right_x, flipper_right_y;

	left.flipper->GetPosition(flipper_left_x, flipper_left_y);
	right.flipper->GetPosition(flipper_right_x, flipper_right_y);

	SDL_Rect f1 = { 0,0,87,27 };
	SDL_Rect f2 = { 100,0,87,27 };
	App->renderer->Blit(flipper_tx, flipper_left_x, flipper_left_y, &f1, 1.0F, left.flipper->GetRotation(), 5, 5);
	App->renderer->Blit(flipper_tx, flipper_right_x-f2.w, flipper_right_y, &f2, 1.0F, right.flipper->GetRotation(), 75, 5);


	return update_status::UPDATE_CONTINUE;
}

void ModuleFlipper::MoveLeft() {
	left.flipper->body->ApplyAngularImpulse(-9.0f, true);
}

void ModuleFlipper::MoveRight() {
	right.flipper->body->ApplyAngularImpulse(9.0f, true);
}

update_status ModuleFlipper::PostUpdate() {


	return update_status::UPDATE_CONTINUE;
}