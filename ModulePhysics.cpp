#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePhysics.h"
#include "p2Point.h"
#include "math.h"

#ifdef _DEBUG
#pragma comment( lib, "Box2D/libx86/Debug/Box2D.lib" )
#else
#pragma comment( lib, "Box2D/libx86/Release/Box2D.lib" )
#endif

ModulePhysics::ModulePhysics(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	world = NULL;
	debug = false;
}

// Destructor
ModulePhysics::~ModulePhysics()
{
}



bool ModulePhysics::Start()
{
	LOG("Creating Physics 2D environment");

	world = new b2World(b2Vec2(GRAVITY_X, -GRAVITY_Y));

	world->SetContactListener(this);

	return true;
}

// 
update_status ModulePhysics::PreUpdate()
{
	world->Step(1.0f / 60.0f, 6, 2);

	for (b2Contact* c = world->GetContactList(); c; c = c->GetNext())
	{
		if (c->GetFixtureA()->IsSensor() && c->IsTouching())
		{
			PhysBody* pb1 = (PhysBody*)c->GetFixtureA()->GetBody()->GetUserData();
			PhysBody* pb2 = (PhysBody*)c->GetFixtureA()->GetBody()->GetUserData();
			if (pb1 && pb2 && pb1->listener)
				pb1->listener->OnCollision(pb1, pb2);
		}
	}

	return UPDATE_CONTINUE;
}


void ModulePhysics::CreateLineJoint(PhysBody* body_1, PhysBody* body_2, float freq, float damp)
{
	b2DistanceJointDef def;

	def.bodyA = body_1->body;
	def.bodyB = body_2->body;

	def.dampingRatio = damp;
	def.frequencyHz = freq;

	world->CreateJoint(&def);
}

void ModulePhysics::CreateRevoluteJoint(PhysBody* body_1, PhysBody* body_2, int x_pivot_1, int y_pivot_1, int x_pivot_2, int y_pivot_2, int max_angle, int min_angle)
{
	b2RevoluteJointDef def;

	def.bodyA = body_1->body;
	def.bodyB = body_2->body;

	def.localAnchorA.Set(PIXEL_TO_METERS(x_pivot_1), PIXEL_TO_METERS(y_pivot_1));
	def.localAnchorB.Set(PIXEL_TO_METERS(x_pivot_2), PIXEL_TO_METERS(y_pivot_2));

	if (max_angle != INT_MAX && min_angle != INT_MIN)
	{
		def.enableLimit = true;
		def.upperAngle = DEGTORAD * max_angle;
		def.lowerAngle = DEGTORAD * min_angle;
	}

	world->CreateJoint(&def);
}

PhysBody* ModulePhysics::CreateObj(int x, int y, int* points, int size, int radius, int width, int height, float rest, bool sensor, body_type type)
{
	b2BodyDef body;

	switch (type)
	{
	case b_static:
		body.type = b2_staticBody;
		break;

	case b_kinematic:
		body.type = b2_kinematicBody;
		break;

	default:
		body.type = b2_dynamicBody;
		break;
	}
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));
	b2Body* b = world->CreateBody(&body);

	if (radius != 0)
	{
		b2CircleShape shape;
		shape.m_radius = PIXEL_TO_METERS(radius/2);

		b2FixtureDef fixture;
		fixture.shape = &shape;
		fixture.density = 1.0f;
		fixture.restitution = rest;
		fixture.friction = 5;
		fixture.isSensor = sensor;
		b->CreateFixture(&fixture);

		PhysBody* pbody = new PhysBody();
		pbody->body = b;
		pbody->width = pbody->height = radius/2;
		return pbody;
	}

	else if (width != 0 && height != 0)
	{
		b2PolygonShape box;
		box.SetAsBox(PIXEL_TO_METERS(width) * 0.5f, PIXEL_TO_METERS(height) * 0.5f);

		b2FixtureDef fixture;
		fixture.shape = &box;
		fixture.density = 1.0f;
		fixture.restitution = rest;
		fixture.isSensor = sensor;
		b->CreateFixture(&fixture);

		PhysBody* pbody = new PhysBody();
		pbody->body = b;
		pbody->width = width * 0.5f;
		pbody->height = height * 0.5f;
		return pbody;
	}

	else if (size != 0)
	{
		b2ChainShape shape;
		b2Vec2* p = new b2Vec2[size / 2];

		for (uint i = 0; i < size / 2; ++i)
		{
			p[i].x = PIXEL_TO_METERS(points[i * 2 + 0]);
			p[i].y = PIXEL_TO_METERS(points[i * 2 + 1]);
		}

		shape.CreateLoop(p, size / 2);

		b2FixtureDef fixture;
		fixture.shape = &shape;
		fixture.restitution = rest;
		fixture.isSensor = sensor;
		b->CreateFixture(&fixture);
		delete p;

		PhysBody* pbody = new PhysBody();
		pbody->body = b;
		pbody->width = pbody->height = 0;
		return pbody;
	}

	
}



// 
update_status ModulePhysics::PostUpdate()
{
	if(App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	if(!debug)
		return UPDATE_CONTINUE;

	// Bonus code: this will iterate all objects in the world and draw the circles
	// You need to provide your own macro to translate meters to pixels
	for(b2Body* b = world->GetBodyList(); b; b = b->GetNext())
	{
		for(b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext())
		{
			switch(f->GetType())
			{
				// Draw circles ------------------------------------------------
				case b2Shape::e_circle:
				{
					b2CircleShape* shape = (b2CircleShape*)f->GetShape();
					b2Vec2 pos = f->GetBody()->GetPosition();
					App->renderer->DrawCircle(METERS_TO_PIXELS(pos.x), METERS_TO_PIXELS(pos.y), METERS_TO_PIXELS(shape->m_radius), 255, 255, 255);
				}
				break;

				// Draw polygons ------------------------------------------------
				case b2Shape::e_polygon:
				{
					b2PolygonShape* polygonShape = (b2PolygonShape*)f->GetShape();
					int32 count = polygonShape->GetVertexCount();
					b2Vec2 prev, v;

					for(int32 i = 0; i < count; ++i)
					{
						v = b->GetWorldPoint(polygonShape->GetVertex(i));
						if(i > 0)
							App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 255, 100, 100);

						prev = v;
					}

					v = b->GetWorldPoint(polygonShape->GetVertex(0));
					App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 255, 100, 100);
				}
				break;

				// Draw chains contour -------------------------------------------
				case b2Shape::e_chain:
				{
					b2ChainShape* shape = (b2ChainShape*)f->GetShape();
					b2Vec2 prev, v;

					for(int32 i = 0; i < shape->m_count; ++i)
					{
						v = b->GetWorldPoint(shape->m_vertices[i]);
						if(i > 0)
							App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 100, 255, 100);
						prev = v;
					}

					v = b->GetWorldPoint(shape->m_vertices[0]);
					App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 100, 255, 100);
				}
				break;

				// Draw a single segment(edge) ----------------------------------
				case b2Shape::e_edge:
				{
					b2EdgeShape* shape = (b2EdgeShape*)f->GetShape();
					b2Vec2 v1, v2;

					v1 = b->GetWorldPoint(shape->m_vertex0);
					v1 = b->GetWorldPoint(shape->m_vertex1);
					App->renderer->DrawLine(METERS_TO_PIXELS(v1.x), METERS_TO_PIXELS(v1.y), METERS_TO_PIXELS(v2.x), METERS_TO_PIXELS(v2.y), 100, 100, 255);
				}
				break;
			}
		}
	}

	return UPDATE_CONTINUE;
}


// Called before quitting
bool ModulePhysics::CleanUp()
{
	LOG("Destroying physics world");

	// Delete the whole physics world!
	delete world;

	return true;
}

void PhysBody::GetPosition(int& x, int &y) const
{
	b2Vec2 pos = body->GetPosition();
	x = METERS_TO_PIXELS(pos.x) - (width);
	y = METERS_TO_PIXELS(pos.y) - (height);
}

float PhysBody::GetRotation() const
{
	return RADTODEG * body->GetAngle();
}

bool PhysBody::Contains(int x, int y) const
{
	// TODO 1: Write the code to return true in case the point
	// is inside ANY of the shapes contained by this body

	return false;
}

int PhysBody::RayCast(int x1, int y1, int x2, int y2, float& normal_x, float& normal_y) const
{
	// TODO 2: Write code to test a ray cast between both points provided. If not hit return -1
	// if hit, fill normal_x and normal_y and return the distance between x1,y1 and it's colliding point
	int ret = -1;

	return ret;
}


PhysBody::PhysBody(b2Body* body, const SDL_Rect& rect, body_type type) : body(body), rect(rect), type(type), listener(NULL)
{}

PhysBody::~PhysBody()
{
	body->GetWorld()->DestroyBody(body);
	body = NULL;
	listener = NULL;
}

double PhysBody::GetAngle() const
{
	return RADTODEG * body->GetAngle();
}

void PhysBody::SetLinearSpeed(int x, int y)
{
	body->SetLinearVelocity(b2Vec2(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y)));
}

void PhysBody::SetAngularSpeed(float speed)
{
	body->SetAngularVelocity(speed * DEGTORAD);
}

void PhysBody::Push(float x, float y)
{
	body->ApplyForceToCenter(b2Vec2(x, y), true);
}

void PhysBody::Turn(int degrees)
{
	body->ApplyAngularImpulse(DEGTORAD * degrees, true);
}

void PhysBody::SetPosition(int x, int y)
{
	body->SetTransform(b2Vec2(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y)), 0.0f);
}

void ModulePhysics::BeginContact(b2Contact* contact)
{
	PhysBody* physA = (PhysBody*)contact->GetFixtureA()->GetBody()->GetUserData();
	PhysBody* physB = (PhysBody*)contact->GetFixtureB()->GetBody()->GetUserData();

	if (physA && physA->listener != NULL)
		physA->listener->OnCollision(physA, physB);

	if (physB && physB->listener != NULL)
		physB->listener->OnCollision(physB, physA);
}