#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	ball_tx = background_tx = NULL;
	sensed = false;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;

	ball_tx = App->textures->Load("pinball/Pinball_Ball.png"); 
	background_tx = App->textures->Load("pinball/Background.png");
	layout_tx = App->textures->Load("pinball/Layout.png");

	bonus_fx = App->audio->LoadFx("pinball/bonus.wav");

	int background_chain[166] = {
	464, 256,
	470, 270,
	473, 298,
	473, 1004,
	502, 1004,
	503, 308,
	499, 269,
	492, 237,
	483, 210,
	468, 174,
	442, 132,
	422, 109,
	396, 83,
	358, 61,
	324, 46,
	300, 40,
	270, 35,
	238, 33,
	211, 34,
	179, 40,
	152, 48,
	125, 62,
	97, 81,
	81, 97,
	61, 120,
	44, 148,
	33, 178,
	24, 204,
	13, 270,
	12, 301,
	8, 336,
	6, 365,
	6, 401,
	6, 427,
	9, 453,
	11, 476,
	18, 512,
	23, 535,
	35, 562,
	43, 579,
	60, 596,
	58, 705,
	44, 713,
	34, 721,
	23, 732,
	16, 741,
	12, 752,
	11, 942,
	50, 942,
	50, 918,
	175, 1020,
	0, 1017,
	0, -1,
	510, 1,
	511, 1022,
	276, 1022,
	405, 921,
	405, 944,
	444, 944,
	446, 748,
	439, 734,
	430, 722,
	418, 709,
	408, 702,
	393, 697,
	393, 597,
	408, 573,
	420, 548,
	432, 511,
	438, 487,
	446, 452,
	449, 413,
	450, 380,
	449, 325,
	445, 293,
	441, 260,
	437, 229,
	428, 197,
	419, 175,
	417, 166,
	444, 201,
	458, 232,
	464, 256
	};

	int flipper_right_chain[18] = {
			0, 83,
			155, -1,
			168, 7,
			176, 19,
			171, 41,
			157, 50,
			15, 96,
			5, 97,
			0, 91
	};

	int flipper_left_chain[26] = {
		501, 616,
		558, 655,
		562, 661,
		561, 666,
		559, 672,
		553, 674,
		544, 672,
		515, 655,
		487, 638,
		483, 629,
		488, 620,
		493, 616,
		501, 616
	};

	back = App->physics->CreateChain(0, 0, background_chain, 165, b2_staticBody);

	/*flipper_left = App->physics->CreateChain(0, 0, flipper_left_chain, 50, b2_staticBody);
	flipper_right = App->physics->CreateChain(0, 0, flipper_right_chain, 15, b2_staticBody);*/

	//sensor = App->physics->CreateRectangleSensor(SCREEN_WIDTH / 2, SCREEN_HEIGHT, SCREEN_WIDTH, 50, this);

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	back = nullptr;

	App->textures->Unload(ball_tx);
	App->textures->Unload(background_tx);

	return true;
}

update_status ModuleSceneIntro::PreUpdate() {

	App->renderer->Blit(background_tx, 0, 0);
	App->renderer->Blit(layout_tx, 0, 0);

	int speed = 3;

	if (App->input->GetKey(SDL_SCANCODE_I) == KEY_REPEAT)
		App->renderer->camera.y += speed;

	if (App->input->GetKey(SDL_SCANCODE_K) == KEY_REPEAT)
		App->renderer->camera.y -= speed;

	if (App->input->GetKey(SDL_SCANCODE_J) == KEY_REPEAT)
		App->renderer->camera.x += speed;

	if (App->input->GetKey(SDL_SCANCODE_L) == KEY_REPEAT)
		App->renderer->camera.x -= speed;

	return UPDATE_CONTINUE;
}
// Update: draw objects
update_status ModuleSceneIntro::Update()
{
	if(App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		bodies.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 11));
		bodies.getLast()->data->listener = this;
	}

	// All draw functions ------------------------------------------------------
	p2List_item<PhysBody*>* b = bodies.getFirst();

	while(b != NULL)
	{
		int x, y;
		b->data->GetPosition(x, y);
		App->renderer->Blit(ball_tx, x, y, NULL, 1.0f, b->data->GetRotation());
		b = b->next;
	}

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	int x, y;

	App->audio->PlayFx(bonus_fx);

	/*
	if(bodyA)
	{
		bodyA->GetPosition(x, y);
		App->renderer->DrawCircle(x, y, 50, 100, 100, 100);
	}

	if(bodyB)
	{
		bodyB->GetPosition(x, y);
		App->renderer->DrawCircle(x, y, 50, 100, 100, 100);
	}*/
}
