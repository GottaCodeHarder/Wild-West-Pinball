#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"

class PhysBody;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

public:
	p2List<PhysBody*> circles;
	p2List<PhysBody*> boxes;
	p2List<PhysBody*> ricks;
	p2List<PhysBody*> backgrounds;

	PhysBody* sensor;
	bool sensed;

	SDL_Texture* circle;
	SDL_Texture* background;
	SDL_Texture* foreground;

	SDL_Texture* flipper_d;
	SDL_Texture* flipper_i;

	SDL_Texture* green; // sensores
	SDL_Texture* purple;
	SDL_Texture* blue;
	SDL_Texture* arrow_pink;
	SDL_Texture* launcher; // lanzadora

	uint sfx_bonus;
	uint sfx_rebotadores;
	uint sfx_launcher;
	p2Point<int> ray;
	bool ray_on;
};
