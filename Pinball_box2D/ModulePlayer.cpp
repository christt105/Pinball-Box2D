#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"
#include "ModulePlayer.h"
#include "ModuleUI.h"

#define PIXEL_BALL 43


ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{

	
	ball_tx = nullptr;

	ball_rect.x = PIXEL_BALL;
	ball_rect.y = 0;
	ball_rect.w = ball_rect.h = 22;

	live_rect.x = 694;
	live_rect.y = 24;
	live_rect.w = live_rect.h = 38;


}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	ball_tx = App->textures->Load("pinball/Textures/Pinball_Ball.png");
	game_over_tx = App->textures->Load("pinball/Textures/game_over.png");
	ball = App->physics->CreateCircle(SCREEN_WIDTH - 23, SCREEN_HEIGHT - 250, 11);
	lives = 5;
	ball->body->SetBullet(true);
	ball->listener = this;

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
	//Change ball skin
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		ball_rect.x = PIXEL_BALL*counter;
		ball_rect.y = PIXEL_BALL*counter2;
		
		counter++;
		if (counter >= 4)
		{
			counter = 0;
			counter2++;
		}
		if (counter2 >= 3)
		{
			counter2 = 0;
		}
	}
	//Lives blit
	if (lives >= 2) 		App->renderer->Blit(App->scene_intro->circle_robound_tx, 350, 972, &live_rect);
	if (lives >= 3) 		App->renderer->Blit(App->scene_intro->circle_robound_tx, 375, 972, &live_rect);
	if (lives >= 4) 		App->renderer->Blit(App->scene_intro->circle_robound_tx, 400, 972, &live_rect);
	if (lives >= 5) 		App->renderer->Blit(App->scene_intro->circle_robound_tx, 425, 972, &live_rect);
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
		
		dead = false;

		lives--;
		
		if (lives <= 0)
		{
			game_over = true;
			App->ui->score = 0;
			lives = 5;
			App->audio->PlayFx(App->scene_intro->game_over_fx, 0);

		}
		if (!game_over)
		{
			App->audio->PlayFx(App->scene_intro->dead_fx);
			ball = App->physics->CreateCircle(SCREEN_WIDTH - 23, SCREEN_HEIGHT - 250, 11);
			ball->body->SetBullet(true);
			ball->listener = this;
		}
	}

	if(game_over)
		App->renderer->Blit(game_over_tx, 0, 0);

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && game_over)
	{
		games_lost++;
		game_over = false;
		lives = 5;
		App->audio->PlayFx(App->scene_intro->dead_fx);
		ball = App->physics->CreateCircle(SCREEN_WIDTH - 23, SCREEN_HEIGHT - 250, 11);
		ball->body->SetBullet(true);
		ball->listener = this;
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




