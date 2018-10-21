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

	ball_tx = App->textures->Load("pinball/Textures/Pinball_Ball.png");
	background_tx = App->textures->Load("pinball/Textures/Background.png");
	layout_tx = App->textures->Load("pinball/Textures/Layout.png");

	bonus_fx = App->audio->LoadFx("pinball/Audio/SFx/bonus.wav");

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

	// Right Half big structure
	int structure_right_chain[104] = {
		322, 130,
		334, 137,
		347, 150,
		357, 165,
		364, 178,
		372, 194,
		378, 211,
		383, 231,
		389, 256,
		394, 280,
		397, 304,
		398, 329,
		399, 350,
		399, 374,
		398, 401,
		396, 428,
		393, 453,
		390, 475,
		384, 503,
		376, 526,
		370, 541,
		358, 558,
		350, 565,
		345, 565,
		321, 552,
		319, 541,
		326, 517,
		329, 499,
		330, 483,
		328, 469,
		321, 459,
		310, 450,
		296, 442,
		253, 419,
		253, 403,
		352, 403,
		352, 370,
		255, 370,
		255, 361,
		269, 351,
		290, 337,
		312, 322,
		330, 311,
		339, 301,
		342, 290,
		343, 275,
		342, 260,
		337, 246,
		329, 228,
		324, 218,
		322, 213,
		322, 130
	};

	
		// Left Half big structure
		int structure_left_chain[122] = {
		129, 129,
		129, 215,
		122, 228,
		118, 238,
		113, 250,
		111, 260,
		109, 271,
		109, 277,
		110, 283,
		110, 290,
		114, 300,
		117, 304,
		122, 309,
		130, 315,
		137, 319,
		145, 325,
		152, 329,
		160, 334,
		166, 338,
		174, 343,
		184, 349,
		192, 354,
		199, 358,
		199, 371,
		100, 371,
		100, 403,
		200, 403,
		200, 419,
		143, 451,
		138, 454,
		133, 458,
		127, 463,
		124, 469,
		122, 476,
		121, 483,
		122, 494,
		124, 507,
		126, 517,
		128, 526,
		131, 536,
		133, 548,
		105, 566,
		99, 564,
		94, 559,
		86, 548,
		81, 535,
		74, 516,
		69, 499,
		65, 482,
		61, 462,
		58, 437,
		55, 402,
		54, 363,
		58, 304,
		62, 272,
		69, 235,
		80, 202,
		93, 173,
		106, 154,
		116, 141,
		129, 129
	};
		// flipper_structure_left_chain
		int flipper_structure_left_chain[26] = {
			49, 760,
			49, 860,
			51, 865,
			137, 934,
			141, 931,
			145, 917,
			145, 911,
			62, 844,
			59, 838,
			60, 761,
			58, 755,
			51, 755,
			49, 760
		};
		// fliper_structure_right_chain
		int fliper_structure_right_chain[28] = {
			395, 761,
			395, 837,
			393, 843,
			312, 911,
			309, 915,
			311, 924,
			314, 936,
			319, 935,
			402, 867,
			405, 862,
			405, 761,
			404, 755,
			397, 755,
			395, 761
		};
		// Left Triangle
		int triangle_left_chain[18] = {
			136, 843,
			100, 758,
			93, 758,
			91, 765,
			91, 820,
			126, 854,
			134, 855,
			137, 850,
			136, 843
		};

		// Right Triangle
		int triangle_right_chain[16] = {
			361, 759,
			364, 765,
			364, 820,
			328, 855,
			319, 856,
			318, 846,
			355, 759,
			361, 759
		};


	back = App->physics->CreateChain(0, 0, background_chain, 165, b2_staticBody);

	flipper_left = App->physics->CreateChain(155, 925, flipper_left_chain, 25, b2_staticBody);
	//flipper_right = App->physics->CreateChain(0, 0, flipper_right_chain, 15, b2_staticBody);

	sensor = App->physics->CreateRectangleSensor(SCREEN_WIDTH / 2, SCREEN_HEIGHT, SCREEN_WIDTH, 50, this);
	structure_right = App->physics->CreateChain(0, 0, structure_right_chain, 103, b2_staticBody);
	structure_left = App->physics->CreateChain(0, 0, structure_left_chain, 121, b2_staticBody);
	flipper_structure_left = App->physics->CreateChain(0, 0, flipper_structure_left_chain, 25, b2_staticBody);
	flipper_structure_right = App->physics->CreateChain(0, 0, fliper_structure_right_chain, 27, b2_staticBody);

	triangle_right = App->physics->CreateChain(0, 0, triangle_left_chain, 17, b2_staticBody);
	triangle_left = App->physics->CreateChain(0, 0, triangle_right_chain, 15, b2_staticBody);

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
