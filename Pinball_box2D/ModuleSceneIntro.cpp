#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"
#include "ModulePlayer.h"
#include "ModuleWindow.h"
#include "ModuleUI.h"
#include "p2Point.h"


ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	background_tx = NULL;
	sensed = false;

	circle_robound1_rect.x = 190;
	circle_robound1_rect.y = 17;
	circle_robound1_rect.w = circle_robound1_rect.h = 45;

	circle_robound2_rect.x = 260;
	circle_robound2_rect.y = 17;
	circle_robound2_rect.w = circle_robound2_rect.h = 45;

	tp_rect.x = 468;
	tp_rect.y = 28;
	tp_rect.w = tp_rect.h = 22;
	
	unlocker_rect.x = 522;
	unlocker_rect.y = 16;
	unlocker_rect.w = 26;
	unlocker_rect.h = 85;

	pink_off_rect.x = 571;
	pink_off_rect.y = 39;
	pink_off_rect.w = pink_off_rect.h = 15;
	
	pink_on_rect.x = 597;
	pink_on_rect.y = 36;
	pink_on_rect.w = pink_on_rect.h = 23;
	
	tp_rebound_rect.x = 633;
	tp_rebound_rect.y = 36;
	tp_rebound_rect.w = 52;
	tp_rebound_rect.h = 25;


}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;


	App->renderer->camera.x = App->renderer->camera.y = 0;

	background_tx = App->textures->Load("pinball/Textures/Background.png");
	layout_tx = App->textures->Load("pinball/Textures/Layout.png");
	layout_alpha_tx = App->textures->Load("pinball/Textures/Layout_alpha.png");
	circle_robound_tx = App->textures->Load("pinball/Textures/Circle_rebound.png");
	kicker.kicker_tx = App->textures->Load("pinball/Textures/kicker.png");

	App->audio->PlayMusic("pinball/Audio/Scene.ogg");
	Mix_VolumeMusic(MIX_MAX_VOLUME / 4);

	bonus_fx = App->audio->LoadFx("pinball/Audio/SFx/bonus.wav");
	kicker_fx = App->audio->LoadFx("pinball/Audio/SFx/kicker.wav");
	circle_fx = App->audio->LoadFx("pinball/Audio/SFx/CircleRebounder.wav");
	triangle_fx = App->audio->LoadFx("pinball/Audio/SFx/Triangle.wav");
	dead_fx = App->audio->LoadFx("pinball/Audio/SFx/Lost_ball.wav");

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
		320, 924,
		320, 936,
		320, 935,
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

	//Top barriers
	int capsule_1_top_chain[18] = {
		171, 106,
		175, 102,
		183, 102,
		186, 106,
		186, 156,
		182, 161,
		176, 161,
		171, 156,
		171, 106
	};
	int capsule_2_top_chain[18] = {
		221, 109,
		225, 102,
		233, 102,
		238, 108,
		238, 156,
		233, 162,
		226, 162,
		221, 156,
		221, 109
	};
	int capsule_3_top_chain[18] = {
		270, 109,
		274, 102,
		282, 102,
		286, 108,
		286, 155,
		281, 161,
		275, 161,
		270, 155,
		270, 109
	};

	//Chains
	back = App->physics->CreateChain(0, 0, background_chain, 165, b2_staticBody);
	structure_right = App->physics->CreateChain(0, 0, structure_right_chain, 103, b2_staticBody);
	structure_left = App->physics->CreateChain(0, 0, structure_left_chain, 121, b2_staticBody);
	flipper_structure_left = App->physics->CreateChain(0, 0, flipper_structure_left_chain, 25, b2_staticBody);
	flipper_structure_right = App->physics->CreateChain(0, 0, fliper_structure_right_chain, 27, b2_staticBody);
	triangle_right = App->physics->CreateChain(0, 0, triangle_left_chain, 17, b2_staticBody);
	triangle_left = App->physics->CreateChain(0, 0, triangle_right_chain, 15, b2_staticBody);
	capsule1 = App->physics->CreateChain(0, 0, capsule_1_top_chain, 17, b2_staticBody);
	capsule2 = App->physics->CreateChain(0, 0, capsule_2_top_chain, 17, b2_staticBody);
	capsule3 = App->physics->CreateChain(0, 0, capsule_3_top_chain, 17, b2_staticBody);

	triangle_left->listener = this;
	triangle_right->listener = this;

	//Circle
	circle1 = App->physics->CreateCircleStatic(225, 210, 20);
	circle2 = App->physics->CreateCircleStatic(285, 270, 20);
	circle3 = App->physics->CreateCircleStatic(170, 270, 20);
	circle1->listener = this;
	circle2->listener = this;
	circle3->listener = this;

	//tp 
	tp_1 = App->physics->CreateRectangleSensor(121, 390, 15, 15);
	tp_2 = App->physics->CreateRectangleSensor(331, 390, 15, 15);
	tp_1->listener = this;
	tp_2->listener = this;

	//Rebound tp
	rebound_tp1 = App->physics->CreateCircleStatic(28, 950, 20);
	rebound_tp2 = App->physics->CreateCircleStatic(425, 950, 20);
	rebound_tp1->listener = this;
	rebound_tp2->listener = this;

	//Pink lights sensors
	pink_1 = App->physics->CreateRectangleSensor(153, 135, 15, 10);
	pink_2 = App->physics->CreateRectangleSensor(203, 135, 15, 10);
	pink_3 = App->physics->CreateRectangleSensor(253, 135, 15, 10);
	pink_4 = App->physics->CreateRectangleSensor(303, 135, 15, 10);
	pink_1->listener = this;
	pink_2->listener = this;
	pink_3->listener = this;
	pink_4->listener = this;

	

	//Kicker
	kicker.launch = App->physics->CreateRectangleSensor(488, 936, 24, 15);
	kicker.stop = App->physics->CreateRectangle(488, 938, 24, 20, b2_dynamicBody);
	kicker.joint = App->physics->CreatePrismaticJoint(kicker.launch->body, kicker.stop->body, { 0, 0 }, { 0, 0 }); // 0, 0 equals A and B anchors

	//Unlocker
	unlocker = App->physics->CreateRectangleSensor( 400, 120, 20, 20);
	unlocker->listener = this;

	//Rectangle Sensor
	sensor = App->physics->CreateRectangleSensor(SCREEN_WIDTH / 2, SCREEN_HEIGHT + 20, SCREEN_WIDTH, 50);
	sensor->listener = this;

	


	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	back = nullptr;

	App->textures->Unload(background_tx);
	App->textures->Unload(layout_tx);
	App->textures->Unload(layout_alpha_tx);
	App->textures->Unload(kicker.kicker_tx);
	App->textures->Unload(circle_robound_tx);


	return true;
}

update_status ModuleSceneIntro::PreUpdate() {

	App->renderer->Blit(background_tx, 0, 0);
	App->renderer->Blit(layout_alpha_tx, 0, 0);
	App->renderer->Blit(circle_robound_tx, 403, 925, &tp_rebound_rect);
	App->renderer->Blit(circle_robound_tx, 8, 923, &tp_rebound_rect);
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
	int x, y;


	// Title info
	iPoint map_coordinates_pixel(App->input->GetMouseX(), App->input->GetMouseY());
	p2SString title("Pixel: %d, %d", map_coordinates_pixel.x + App->renderer->camera.x, map_coordinates_pixel.y + App->renderer->camera.y);
	App->window->SetTitle(title.GetString());

	// Rebound Circles
	App->renderer->Blit(circle_robound_tx, 202, 187, &circle_robound1_rect, 1.0F, angle_rot);
	App->renderer->Blit(circle_robound_tx, 262, 247, &circle_robound2_rect, 1.0F, angle_rot);
	App->renderer->Blit(circle_robound_tx, 147, 247, &circle_robound2_rect, 1.0F, angle_rot);

	angle_rot-=0.5F;
	//Unlocker
	if(unlocker_closed)
		App->renderer->Blit(circle_robound_tx, 413, 113, &unlocker_rect);

	//Pink lights
	if (pink1)
		App->renderer->Blit(circle_robound_tx, 145, 125, &pink_on_rect);
	else
		App->renderer->Blit(circle_robound_tx, 145, 125, &pink_off_rect);
	if (pink2)
		App->renderer->Blit(circle_robound_tx, 195, 125, &pink_on_rect);
	else
		App->renderer->Blit(circle_robound_tx, 195, 125, &pink_off_rect);
	if(pink3)
		App->renderer->Blit(circle_robound_tx, 245, 125, &pink_on_rect);
	else
		App->renderer->Blit(circle_robound_tx, 245, 125, &pink_off_rect);
	if(pink4)
		App->renderer->Blit(circle_robound_tx, 295, 125, &pink_on_rect);
	else
		App->renderer->Blit(circle_robound_tx, 295, 125, &pink_off_rect);

	if (pink1 && pink2 && pink3 && pink4 && timer)
	{
		init_time = SDL_GetTicks(); //Timer
		timer = false;
	}
	if (pink1 && pink2 && pink3 && pink4)
	{
		current_time = SDL_GetTicks() - init_time; //Timer
		if (current_time > 1000)
		{
			pink1 = pink2 = pink3 = pink4 = false;
			timer = true;
			App->ui->score += 10000;
		}
	}
	
	//Tp
	App->renderer->Blit(circle_robound_tx, 108, 378, &tp_rect, 1.0F, angle_rot);
	App->renderer->Blit(circle_robound_tx, 322, 378, &tp_rect, 1.0F, angle_rot);
	App->renderer->Blit(circle_robound_tx, 20, 750, &tp_rect, 1.0F, angle_rot);
	App->renderer->Blit(circle_robound_tx, 410, 750, &tp_rect, 1.0F, angle_rot);


	//Kicker
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT) //Keep pressing
	{
		kicker.joint->SetMotorSpeed(-2);
		kicker.force += 1.0f;
		if (kicker.force > 100)
		{
			kicker.force = 100;
		}
	}
	else if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_UP) //Stop pressing
	{
		kicker.joint->SetMotorSpeed(kicker.force);
		kicker.force = 0;
		App->audio->PlayFx(kicker_fx, 0);

	}
	else if (kicker.joint->GetMotorSpeed() < 1) 
	{
		kicker.stop->body->SetTransform({ kicker.stop->body->GetPosition().x, kicker.launch->body->GetPosition().y }, 0);
	}
	
	if (kicker.stop->body->GetPosition().y < kicker.launch->body->GetPosition().y) //launch down stop
	{
		kicker.joint->SetMotorSpeed(0);
		kicker.stop->body->SetTransform({ kicker.stop->body->GetPosition().x, kicker.launch->body->GetPosition().y }, 0);
	}

	kicker.stop->GetPosition(x, y);
	App->renderer->Blit(kicker.kicker_tx, x, y);

	//Unlock
	if(unlocker_closed)
		if (unlocker_rectangle == nullptr)
		{
			unlocker_rectangle = App->physics->CreateRectangle(420, 140, 2, 70, b2_staticBody);
			
			LOG("A NEW UNLOCKER CREATED");
		}

	if (!unlocker_closed && unlocker_rectangle != nullptr)
	{
		unlocker_rectangle->body->GetWorld()->DestroyBody(unlocker_rectangle->body);
		unlocker_rectangle = nullptr;
		LOG("-- UNLOCKER DESTROYED ");

	}
	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	int x, y;

	if (bodyA == sensor)
	{
		App->player->dead = true;
		unlocker_closed = false;
		App->audio->PlayFx(dead_fx);

		LOG("DEAD");
	}

	if (bodyA == unlocker)
	{
		unlocker_closed = true;
		
	}
	
	if (bodyA == tp_1)
	{
		App->player->tp1 = true;
		LOG("TP 1");
	}
	if (bodyA == tp_2)
	{
		App->player->tp2 = true;
		LOG("TP 2");
	}
	
	if (bodyA == pink_1 && !pink1)
	{
		pink1 = true;		
		App->ui->score += 100;
	}
	if (bodyA == pink_2 && !pink2)
	{
		pink2 = true;
		App->ui->score += 100;
	}
	if (bodyA == pink_3 && !pink3)
	{
		pink3 = true;
		App->ui->score += 100;
	}
	if (bodyA == pink_4 && !pink4)
	{
		pink4 = true;
		App->ui->score += 100;
	}

	if (bodyA == circle1 || bodyA == circle2 || bodyA == circle3 || bodyA == rebound_tp1 || bodyA == rebound_tp2) {
		b2Vec2 force(bodyB->body->GetWorldCenter() - bodyA->body->GetWorldCenter());
		force *= 3;
		bodyB->body->ApplyLinearImpulse(force, bodyB->body->GetWorldCenter(), true);
		App->ui->score += 100;
		App->audio->PlayFx(circle_fx);
	}
	if (bodyA == rebound_tp1 || bodyA == rebound_tp2) {
		b2Vec2 force(bodyB->body->GetWorldCenter() - bodyA->body->GetWorldCenter());
		force *= 10;
		bodyB->body->ApplyLinearImpulse(force, bodyB->body->GetWorldCenter(), true);
		App->ui->score += 100;
		App->audio->PlayFx(circle_fx);
	}

	if (bodyA == triangle_left) {
		bodyB->body->ApplyLinearImpulse(b2Vec2(-2, -2), bodyB->body->GetWorldCenter(), true);
		App->ui->score += 100;
		App->audio->PlayFx(triangle_fx);
	}
	if (bodyA == triangle_right) {
		bodyB->body->ApplyLinearImpulse(b2Vec2(2, -2), bodyB->body->GetWorldCenter(), true);
		App->ui->score += 100;
		App->audio->PlayFx(triangle_fx);
	}
}
