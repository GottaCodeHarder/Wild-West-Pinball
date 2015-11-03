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
	circle = NULL;
	ray_on = false;
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

	circle = App->textures->Load("pinball/ball.png"); 

	background = App->textures->Load("pinball/PinballBackGround2.png");
	foreground = App->textures->Load("pinball/PinballForeground.png");

	flipper_d = App->textures->Load("pinball/Flipper Derecho.png");
	flipper_i = App->textures->Load("pinball/Flipper Izquierdo.png");

	//App->audio->PlayMusic("pinball/Soundtrack.mp3", 0.0f);
	
	// SENSOR
	green = App->textures->Load("pinball/verde.png");
	purple = App->textures->Load("pinball/morado.png");
	blue = App->textures->Load("pinball/azul.png");
	arrow_pink = App->textures->Load("pinball/rosa.png");

	sfx_bonus = App->audio->LoadFx("pinball/ding.wav");
	sfx_rebotadores = App->audio->LoadFx("pinball/rebotadores.wav");
	sfx_launcher = App->audio->LoadFx("pinball/launcher.wav");

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	if (!App->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN)
		App->renderer->Blit(background, 0, 0, NULL, 0, 0);

	if(App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		circles.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 10));
	}
	
	static float pot = 0.0f;

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT && pot < 40000)
	{
		pot += 500.0f;
		App->physics->lanzadera->Push(0, pot);
	}

	else
		pot = 0;

	// Prepare for raycast ------------------------------------------------------
	
	iPoint mouse;
	mouse.x = App->input->GetMouseX();
	mouse.y = App->input->GetMouseY();
	int ray_hit = ray.DistanceTo(mouse);

	fVector normal(0.0f, 0.0f);

	// All draw functions ------------------------------------------------------
	p2List_item<PhysBody*>* c = circles.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(circle, x, y, NULL, 1.0f, 0);
		c = c->next;
	}

	// ray -----------------
	if(ray_on == true)
	{
		fVector destination(mouse.x-ray.x, mouse.y-ray.y);
		destination.Normalize();
		destination *= ray_hit;

		App->renderer->DrawLine(ray.x, ray.y, ray.x + destination.x, ray.y + destination.y, 255, 255, 255);

		if(normal.x != 0.0f)
			App->renderer->DrawLine(ray.x + destination.x, ray.y + destination.y, ray.x + destination.x + normal.x * 25.0f, ray.y + destination.y + normal.y * 25.0f, 100, 255, 100);
	}
	App->renderer->Blit(foreground, 0, 0, NULL);

	return UPDATE_CONTINUE;
}

// TODO 8: Now just define collision callback for the circle and play bonus_fx audio
