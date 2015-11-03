#pragma once
#include "Module.h"
#include "Globals.h"
#include "Box2D/Box2D/Box2D.h"

#define GRAVITY_X 0.0f
#define GRAVITY_Y -7.0f

#define PIXELS_PER_METER 50.0f // if touched change METER_PER_PIXEL too
#define METER_PER_PIXEL 0.02f // this is 1 / PIXELS_PER_METER !

#define METERS_TO_PIXELS(m) ((int) floor(PIXELS_PER_METER * m))
#define PIXEL_TO_METERS(p)  ((float) METER_PER_PIXEL * p)

enum body_type
{
	b_dynamic,
	b_static,
	b_kinematic
};

// Small class to return to other modules to track position and rotation of physics bodies
class PhysBody
{
public:
	PhysBody(b2Body* body, const SDL_Rect& rect, body_type type);
	PhysBody();
	~PhysBody();

	void GetPosition(int& x, int &y) const;
	float GetRotation() const;
	bool Contains(int x, int y) const;
	int RayCast(int x1, int y1, int x2, int y2, float& normal_x, float& normal_y) const;

	double GetAngle() const;
	void SetLinearSpeed(int x, int y);
	void SetAngularSpeed(float speed);
	void Push(float x, float y);
	void Turn(int degrees);
	void SetPosition(int x, int y);

public:
	int width, height;
	b2Body* body;
	Module* listener;
	SDL_Texture* graphic;
	uint music;


private:
	SDL_Rect rect;
	body_type type;
};

// Module --------------------------------------
// TODO 3: Make module physics inherit from b2ContactListener
// then override void BeginContact(b2Contact* contact)
class ModulePhysics : public Module
{
public:
	ModulePhysics(Application* app, bool start_enabled = true);
	~ModulePhysics();

	bool Start();
	update_status PreUpdate();
	update_status PostUpdate();
	bool CleanUp();

	PhysBody* CreateObj(int x, int y, int* points, int size, int radius, int width, int height, float rest, bool sensor, body_type type);
	

	void CreateLineJoint(PhysBody* body_1, PhysBody* body_2, float freq, float damp);
	void CreateRevoluteJoint(PhysBody* body_1, PhysBody* body_2, int x_pivot_1 = 0, int y_pivot_1 = 0, int x_pivot_2 = 0, int y_pivot_2 = 0, int max_angle = INT_MAX, int min_angle = INT_MIN);

private:

	bool debug;
	b2World* world;
};