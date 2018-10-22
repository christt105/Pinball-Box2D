#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"
#include "ModulePlayer.h"



ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	ball_tx = nullptr;

	ball_rect.x = 47;
	ball_rect.y = 6;
	ball_rect.w = ball_rect.h = 24;

	circle_robound1_rect.x = 190;
	circle_robound1_rect.y = 17;
	circle_robound1_rect.w = circle_robound1_rect.h = 45;

	circle_robound2_rect.x = 260;
	circle_robound2_rect.y = 17;
	circle_robound2_rect.w = circle_robound2_rect.h = 45;
	
	
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	ball_tx = App->textures->Load("pinball/Textures/Pinball_Ball.png");
	circle_robound_tx = App->textures->Load("pinball/Textures/Circle_rebound.png");

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	
	// Spawn ball
	if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		dead = true;
	}

	if (dead)
	{
		if (ball != nullptr)
		{
			ball->body->GetWorld()->DestroyBody(ball->body);
			ball = nullptr;
		}
		ball = App->physics->CreateCircle(SCREEN_WIDTH - 23, SCREEN_HEIGHT - 230, 11);
		ball->listener = this;

		dead = false;
	}

	// Ball
	if (ball != nullptr)
	{
		int x, y;
		ball->GetPosition(x, y);
		App->renderer->Blit(ball_tx, x, y, &ball_rect, 1.0f, ball->GetRotation());
	}

	// Rebound Circles
	App->renderer->Blit(circle_robound_tx, 202, 187, &circle_robound1_rect);
	App->renderer->Blit(circle_robound_tx, 262, 247, &circle_robound2_rect);
	App->renderer->Blit(circle_robound_tx, 147, 247, &circle_robound2_rect);

	// DEBUG MODE
	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		bodies.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 11));
		bodies.getLast()->data->listener = this;
	}
	// All draw functions ------------------------------------------------------
	p2List_item<PhysBody*>* b = bodies.getFirst();
	
	while (b != nullptr)
	{
		int x, y;
		b->data->GetPosition(x, y);
		App->renderer->Blit(ball_tx, x, y, &ball_rect, 1.0f, b->data->GetRotation());
		b = b->next;
	}

	return UPDATE_CONTINUE;
}


// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(ball_tx);
	App->textures->Unload(circle_robound_tx);

	return true;
}




