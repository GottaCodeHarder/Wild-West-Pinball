#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");
	//BALL
	ball.body = App->physics->CreateObj(670, 730, NULL, 0, 20, 0, 0, 0, false, b_dynamic);
	ball.graphic = App->textures->Load("pinball/ball.png");

	//FLIPPER DER
	flipper_der.graphic = App->textures->Load("pinball/Flipper Derecho.png");
	flipper_der.body = App->physics->CreateObj(420, 905, NULL, 0, 0, 100, 25, 0, false, b_dynamic);
	flipper_der_wheel = App->physics->CreateObj(472, 905, NULL, 0, 20, 0, 0, 0, false, b_static);
	App->physics->CreateRevoluteJoint(flipper_der.body, flipper_der_wheel, 42, 0, 0, 0, 20, -30);
	flipper_der.fx = App->audio->LoadFx("pinball/flipper.wav");
	//FLIPER IZQ
	flipper_izq.graphic = App->textures->Load("pinball/Flipper Izquierdo.png");
	flipper_izq.body = App->physics->CreateObj(300, 905, NULL, 0, 0, 100, 25, 0, false, b_dynamic);
	flipper_izq_wheel = App->physics->CreateObj(255, 905, NULL, 0, 20, 0, 0, 0, true, b_static);
	App->physics->CreateRevoluteJoint(flipper_izq.body, flipper_izq_wheel, -42, 0, 0, 0, 30, -20);
	flipper_izq.fx = App->audio->LoadFx("pinball/flipper.wav");
	//BUMPER
	lanzadera.body = App->physics->CreateObj(647, 810, NULL, 0, 0, 48, 25, 0, false, b_dynamic);
	eje_lanz = App->physics->CreateObj(630, 722, NULL, 0, 1, 0, 0, 0, false, b_static);
	App->physics->CreateLineJoint(lanzadera.body, eje_lanz, 20.0f, 1.0f);


	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{

	if (!alive)
	{
		ball.body->SetPosition(675, 735);
		alive = true;
	}


	if ((App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN) || App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
		App->audio->PlayFx(flipper_der.fx);

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN)
		flipper_izq.body->Turn(-360);

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
		flipper_der.body->Turn(360);

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_UP)
		flipper_izq.body->Turn(1000);

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_UP)
		flipper_der.body->Turn(-1000);

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_UP)
		App->audio->PlayFx(flipper_der.fx);

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT && pot < 20000)
	{
		pot += 100.0f;
		lanzadera.body->Push(0, pot);
	}
	else
		pot = 0;


	
	ball.body->GetPosition(b_x, b_y);
	flipper_der.body->GetPosition(der_x, der_y);
	flipper_izq.body->GetPosition(izq_x, izq_y);

	App->renderer->Blit(ball.graphic, b_x, b_y, NULL, 1.0f, 0);
	App->renderer->Blit(flipper_der.graphic, der_x - 8, der_y - 26, NULL, 1.0f, flipper_der.body->GetRotation() + 21, -10);
	App->renderer->Blit(flipper_izq.graphic, izq_x - 8, izq_y - 26, NULL, 1.0f, flipper_izq.body->GetRotation() - 21, +10);

	if (App->scene_intro->activation == false)
		App->renderer->Blit(App->scene_intro->foreground, 0, 0, NULL);

	return UPDATE_CONTINUE;
}



