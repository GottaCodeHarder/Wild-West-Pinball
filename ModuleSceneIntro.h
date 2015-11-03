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
	bool activation;

	PhysBody* flipper_izq;
	PhysBody* flipper_der;
	PhysBody* flipper_izq_wheel;
	PhysBody* flipper_der_wheel;
	PhysBody* lanzadera;
	PhysBody* eje_lanz;

	bool ball;

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
	uint sfx_flipper;

	p2Point<int> ray;
	bool ray_on;
	float pot = 0.0f;
};
