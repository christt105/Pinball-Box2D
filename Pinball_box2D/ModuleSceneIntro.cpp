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
	background_tx = App->textures->Load("pinball/Pinball_ImprPant.png");

	bonus_fx = App->audio->LoadFx("pinball/bonus.wav");

	int background_chain[386] = {
		51, 515,
		51, 605,
		44, 608,
		39, 611,
		34, 614,
		28, 618,
		23, 622,
		18, 628,
		12, 635,
		8, 643,
		5, 650,
		5, 659,
		5, 817,
		48, 816,
		48, 798,
		169, 885,
		281, 885,
		395, 804,
		395, 819,
		442, 819,
		442, 647,
		441, 642,
		439, 636,
		436, 630,
		433, 625,
		430, 620,
		425, 615,
		419, 611,
		412, 607,
		402, 603,
		397, 602,
		391, 602,
		391, 518,
		396, 511,
		401, 504,
		406, 496,
		411, 486,
		415, 477,
		418, 471,
		421, 463,
		425, 453,
		430, 440,
		433, 429,
		436, 420,
		438, 410,
		440, 400,
		442, 386,
		444, 373,
		444, 361,
		445, 349,
		445, 300,
		445, 285,
		444, 271,
		443, 259,
		441, 244,
		439, 233,
		437, 222,
		435, 213,
		434, 204,
		431, 195,
		429, 185,
		427, 178,
		424, 168,
		420, 159,
		417, 152,
		425, 159,
		429, 164,
		433, 170,
		436, 176,
		439, 181,
		442, 187,
		445, 192,
		448, 198,
		451, 207,
		454, 214,
		456, 221,
		457, 227,
		459, 233,
		460, 239,
		461, 246,
		462, 252,
		462, 870,
		497, 870,
		497, 236,
		496, 229,
		495, 223,
		494, 219,
		493, 213,
		492, 207,
		490, 201,
		488, 195,
		485, 188,
		483, 183,
		481, 179,
		479, 174,
		477, 169,
		474, 161,
		471, 154,
		467, 146,
		463, 140,
		460, 134,
		456, 128,
		451, 122,
		446, 115,
		442, 110,
		438, 105,
		433, 100,
		426, 93,
		420, 87,
		413, 81,
		406, 76,
		398, 70,
		392, 65,
		385, 60,
		375, 55,
		367, 50,
		359, 46,
		351, 42,
		343, 39,
		336, 36,
		326, 33,
		316, 30,
		308, 28,
		300, 26,
		293, 25,
		288, 24,
		280, 23,
		273, 22,
		264, 22,
		210, 22,
		199, 22,
		190, 23,
		181, 24,
		172, 26,
		165, 28,
		159, 29,
		152, 31,
		145, 34,
		137, 37,
		128, 40,
		122, 43,
		113, 47,
		107, 51,
		101, 55,
		95, 59,
		87, 64,
		78, 72,
		73, 76,
		69, 80,
		65, 84,
		62, 89,
		56, 96,
		52, 100,
		48, 106,
		45, 111,
		42, 116,
		38, 120,
		34, 128,
		30, 136,
		26, 142,
		22, 151,
		20, 160,
		18, 170,
		15, 176,
		13, 184,
		12, 190,
		11, 196,
		9, 206,
		7, 215,
		6, 224,
		5, 236,
		4, 246,
		3, 258,
		2, 271,
		2, 280,
		2, 371,
		2, 381,
		3, 392,
		5, 405,
		6, 415,
		8, 424,
		9, 431,
		12, 440,
		14, 448,
		16, 457,
		20, 468,
		23, 476,
		26, 482,
		32, 491,
		37, 498,
		41, 504,
		45, 509,
		51, 515
	};

	back = App->physics->CreateChain(0, 0, background_chain, 100, b2_staticBody);

	//sensor = App->physics->CreateRectangleSensor(SCREEN_WIDTH / 2, SCREEN_HEIGHT, SCREEN_WIDTH, 50, this);

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	delete back;
	back = nullptr;

	App->textures->Unload(ball_tx);
	App->textures->Unload(background_tx);

	return true;
}

update_status ModuleSceneIntro::PreUpdate() {

	App->renderer->Blit(background_tx, 0, 0);

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
