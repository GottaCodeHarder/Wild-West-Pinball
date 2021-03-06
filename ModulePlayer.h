#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

class PhysBody;

struct Object
{
	SDL_Texture* graphic;
	PhysBody* body;
	uint fx;


	Object() : graphic(NULL), body(NULL)
	{}
};

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	Object ball;
	Object flipper_izq;
	Object flipper_der;
	Object lanzadera;

	PhysBody* eje_lanz;
	PhysBody* flipper_izq_wheel;
	PhysBody* flipper_der_wheel;

	int pot;
	uint hp = 3;
	uint best_score = 0;
	uint score = 0;

	bool Start();
	bool alive;
	update_status Update();
	bool CleanUp();

	uint sfx_teleport;

	int b_x, b_y;
	int der_x, der_y;
	int izq_x, izq_y;
	int lan_x, lan_y;

	void Respawn();


public:

};