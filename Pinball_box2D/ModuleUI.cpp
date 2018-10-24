#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleUI.h"
#include "ModuleFonts.h"

ModuleUI::ModuleUI(Application* app, bool start_enabled) : Module(app, start_enabled)
{}

ModuleUI::~ModuleUI() {}

bool ModuleUI::Start()
{
	LOG("Loading UI");

	score_tx = App->textures->Load("pinball/Textures/high_score.png");

	font = App->fonts->Load("pinball/Textures/numbers.png", "1234567890", 1);

	score = 0;

	return true;
}

bool ModuleUI::CleanUp()
{
	LOG("Unloading user interface")

	App->textures->Unload(score_tx);
	App->fonts->UnLoad(font);

	return true;
}

update_status ModuleUI::Update() {

	if (score > high_score)
		high_score = score;

	App->fonts->BlitText(0, 0, font, "1234567890");

	return UPDATE_CONTINUE;
}
