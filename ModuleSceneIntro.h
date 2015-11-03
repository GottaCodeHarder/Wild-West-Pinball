#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "p2DynArray.h"
#include "Globals.h"

class PhysBody;

enum lightTypes
{
	green = 1,
	purple,
	blue,
	arrow_pink
};

class ModuleSceneIntro;

struct Sign
{
	Sign() : body(NULL), texture(NULL), on(false), fx(0)
	{}

	Sign(ModuleSceneIntro* physics, int x, int y, lightTypes type);

	lightTypes type;
	PhysBody* body;
	SDL_Texture* texture;
	bool on;
	uint fx;
	int x, y;
};

class ModuleSceneIntro : public Module, public b2ContactListener
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

	PhysBody* morir;

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

	p2DynArray<Sign> signs;

	uint sfx_bonus;
	uint sfx_spawn;
	uint sfx_launcher;
	uint sfx_charge;
	uint sfx_flipper;

	p2Point<int> ray;
	bool ray_on;
	float pot = 0.0f;
};
