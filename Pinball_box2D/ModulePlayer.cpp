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

}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	ball_tx = App->textures->Load("pinball/Textures/Pinball_Ball.png");
	

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	// DEBUG MODE
	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		if (ball != nullptr)
		{
			ball->body->GetWorld()->DestroyBody(ball->body);
			ball = nullptr;
		}
		ball = App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 11);
		ball->body->SetBullet(true);
		ball->listener = this;
	}

	// Spawn ball
	if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		dead = true;
		App->scene_intro->unlocker_closed = false;

	}

	if (dead)
	{
		if (ball != nullptr)
		{
			ball->body->GetWorld()->DestroyBody(ball->body);
			ball = nullptr;
		}
		ball = App->physics->CreateCircle(SCREEN_WIDTH - 23, SCREEN_HEIGHT - 250, 11);
		ball->body->SetBullet(true);
		ball->listener = this;
		dead = false;

		lives--;

		if (lives <= 0)
		{
			game_over = true;
			App->audio->PlayFx(App->scene_intro->game_over_fx, 0);

		}
		if(!game_over)
			App->audio->PlayFx(App->scene_intro->dead_fx);

	
	}

	//Tp ball
	if (tp1)
	{
		if (ball != nullptr)
		{
			ball->body->GetWorld()->DestroyBody(ball->body);
			ball = nullptr;
		}
		ball = App->physics->CreateCircle(22, 775, 11);
		ball->body->SetBullet(true);
		ball->listener = this;

		tp1 = false;
	}
	if (tp2)
	{
		if (ball != nullptr)
		{
			ball->body->GetWorld()->DestroyBody(ball->body);
			ball = nullptr;
		}
		ball = App->physics->CreateCircle(420, 775, 11);
		ball->body->SetBullet(true);
		ball->listener = this;

		tp2 = false;
	}
	// Ball
	if (ball != nullptr)
	{
		int x, y;
		ball->GetPosition(x, y);
		App->renderer->Blit(ball_tx, x, y, &ball_rect, 1.0f, ball->GetRotation());
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

	return true;
}




