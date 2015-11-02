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
	debug = true;
}

// Destructor
ModulePhysics::~ModulePhysics()
{
}



bool ModulePhysics::Start()
{
	LOG("Creating Physics 2D environment");

	world = new b2World(b2Vec2(GRAVITY_X, -GRAVITY_Y));
	// TODO 3: You need to make ModulePhysics class a contact listener




	int	map[154] = {
		671, 749,
		684, 749,
		692, 744,
		694, 733,
		690, 722,
		681, 716,
		669, 716,
		646, 337,
		637, 254,
		630, 208,
		618, 173,
		600, 143,
		574, 116,
		543, 97,
		500, 82,
		445, 72,
		390, 68,
		325, 70,
		267, 77,
		237, 87,
		221, 65,
		203, 51,
		175, 43,
		149, 52,
		128, 72,
		128, 100,
		140, 123,
		158, 143,
		138, 170,
		119, 203,
		110, 232,
		103, 270,
		103, 305,
		109, 337,
		120, 369,
		138, 400,
		153, 423,
		170, 448,
		172, 457,
		163, 466,
		154, 480,
		152, 495,
		159, 510,
		167, 517,
		180, 518,
		183, 525,
		170, 567,
		160, 569,
		147, 560,
		130, 560,
		119, 570,
		113, 583,
		112, 598,
		119, 612,
		127, 620,
		138, 629,
		132, 641,
		121, 652,
		113, 661,
		110, 673,
		102, 837,
		89, 1025,
		128, 1024,
		133, 946,
		143, 932,
		319, 980,
		265, 1031,
		459, 1031,
		405, 979,
		584, 926,
		594, 944,
		595, 1009,
		637, 1008,
		607, 376,
		617, 367,
		635, 758,
		672, 758
	};

	int barras_cash[16] = {
		226, 218,
		227, 229,
		229, 234,
		232, 234,
		233, 229,
		232, 217,
		230, 213,
		227, 214
	};

	int barras_cash_2[16] = {
		267, 239,
		270, 239,
		272, 235,
		270, 220,
		268, 216,
		263, 217,
		262, 221,
		264, 235
	};

	int barras_sup[16] = {
		375, 155,
		379, 158,
		385, 158,
		387, 154,
		386, 130,
		383, 125,
		377, 125,
		374, 130
	};

	int barras_sup_2[16] = {
		430, 156,
		437, 155,
		440, 148,
		438, 128,
		434, 121,
		427, 121,
		423, 129,
		425, 149
	};

	int base_flip_der[20] = {
		577, 679,
		581, 848,
		477, 887,
		491, 893,
		494, 903,
		488, 917,
		582, 882,
		587, 873,
		583, 680,
		581, 676
	};

	int base_flip_izq[24] = {
		152, 698,
		148, 846,
		151, 851,
		247, 888,
		240, 895,
		238, 902,
		238, 911,
		151, 884,
		145, 879,
		143, 871,
		147, 698,
		150, 695
	};

	int cash[192] = {
		260, 391,
		288, 379,
		311, 368,
		319, 362,
		325, 355,
		327, 348,
		327, 337,
		294, 190,
		329, 150,
		331, 146,
		332, 136,
		329, 129,
		322, 125,
		312, 124,
		294, 127,
		269, 135,
		248, 143,
		228, 153,
		206, 167,
		190, 180,
		173, 197,
		161, 213,
		147, 236,
		140, 261,
		140, 283,
		142, 305,
		147, 325,
		156, 343,
		168, 363,
		182, 383,
		193, 396,
		203, 410,
		207, 413,
		210, 409,
		199, 396,
		185, 377,
		169, 353,
		157, 331,
		150, 310,
		147, 288,
		147, 268,
		152, 243,
		159, 227,
		175, 206,
		196, 189,
		220, 174,
		240, 166,
		260, 163,
		273, 167,
		283, 176,
		287, 186,
		295, 219,
		297, 241,
		296, 252,
		304, 256,
		309, 269,
		309, 277,
		304, 285,
		310, 290,
		313, 305,
		316, 318,
		320, 332,
		321, 344,
		318, 353,
		310, 360,
		300, 362,
		291, 361,
		281, 356,
		273, 354,
		248, 354,
		231, 351,
		219, 344,
		210, 332,
		206, 319,
		205, 305,
		206, 292,
		209, 284,
		201, 280,
		196, 272,
		194, 262,
		200, 252,
		198, 243,
		196, 229,
		192, 226,
		186, 230,
		180, 241,
		175, 253,
		172, 269,
		172, 283,
		175, 300,
		179, 311,
		186, 324,
		198, 339,
		213, 354,
		227, 366,
		245, 380
	};

	int curva_der_arriba[52] = {
		486, 162,
		508, 163,
		533, 171,
		549, 184,
		564, 202,
		577, 224,
		586, 244,
		593, 268,
		596, 282,
		597, 295,
		606, 295,
		608, 283,
		604, 251,
		598, 225,
		592, 204,
		584, 186,
		573, 168,
		559, 153,
		544, 142,
		520, 129,
		499, 124,
		482, 123,
		476, 127,
		475, 137,
		477, 149,
		480, 158
	};

	int tri_der[30] = {
		523, 711,
		478, 819,
		476, 825,
		476, 831,
		479, 838,
		484, 842,
		492, 843,
		543, 819,
		548, 813,
		550, 807,
		546, 715,
		544, 710,
		540, 705,
		532, 704,
		526, 706
	};


	int tri_izq[30] = {
		204, 711,
		252, 820,
		252, 832,
		248, 840,
		242, 844,
		235, 843,
		188, 822,
		182, 816,
		180, 808,
		182, 718,
		183, 712,
		186, 706,
		191, 703,
		197, 704,
		202, 708
	};

	int reb_der[6] = {
		523, 711,
		496, 766,
		475, 820
	};


	int reb_izq[6] = {
		204, 711,
		231, 766,
		253, 820
	};

	int via_superior[112] = {
		485, 193,
		491, 190,
		497, 190,
		513, 197,
		531, 212,
		546, 227,
		558, 245,
		567, 266,
		570, 293,
		568, 326,
		558, 354,
		541, 386,
		530, 414,
		525, 428,
		513, 439,
		499, 446,
		493, 447,
		473, 450,
		490, 428,
		521, 382,
		556, 330,
		566, 312,
		538, 289,
		520, 323,
		510, 338,
		497, 356,
		454, 385,
		435, 432,
		431, 436,
		426, 432,
		431, 425,
		433, 413,
		430, 405,
		421, 402,
		418, 395,
		422, 391,
		427, 391,
		437, 371,
		442, 357,
		440, 348,
		442, 339,
		440, 327,
		434, 300,
		428, 297,
		430, 290,
		434, 285,
		440, 280,
		447, 267,
		445, 254,
		459, 233,
		469, 229,
		478, 227,
		485, 224,
		490, 215,
		491, 207,
		490, 197
	};


	int via_central[76] = {
		562, 602,
		580, 578,
		575, 536,
		566, 503,
		551, 460,
		520, 385,
		492, 320,
		481, 289,
		481, 272,
		487, 257,
		501, 252,
		516, 251,
		529, 258,
		537, 272,
		537, 286,
		530, 303,
		519, 321,
		507, 339,
		539, 358,
		554, 335,
		565, 313,
		572, 289,
		572, 268,
		568, 250,
		558, 234,
		543, 222,
		519, 214,
		496, 214,
		472, 223,
		456, 238,
		447, 257,
		442, 286,
		447, 310,
		458, 342,
		497, 434,
		528, 515,
		536, 544,
		538, 575
	};

	int via_inferior[44] = {
		518, 537,
		511, 543,
		504, 547,
		500, 555,
		500, 563,
		529, 609,
		536, 611,
		536, 554,
		532, 530,
		548, 511,
		566, 503,
		574, 527,
		581, 608,
		584, 612,
		579, 448,
		573, 443,
		567, 447,
		561, 461,
		551, 487,
		548, 503,
		535, 519,
		524, 531
	};


	App->physics->CreateChain(0, 0, map, 154, 0.2);
	App->physics->CreateChain(0, 0, barras_cash, 16, 0.2);
	App->physics->CreateChain(0, 0, barras_cash_2, 16, 0.2);
	App->physics->CreateChain(0, 0, barras_sup, 16, 0.2);
	App->physics->CreateChain(0, 0, barras_sup_2, 16, 0.2);
	App->physics->CreateChain(0, 0, base_flip_der, 20, 0.2);
	App->physics->CreateChain(0, 0, base_flip_izq, 22, 0.2);
	App->physics->CreateChain(0, 0, cash, 192, 0.2);
	App->physics->CreateChain(0, 0, curva_der_arriba, 52, 0.2);
	App->physics->CreateChain(0, 0, tri_der, 30, 0.2);
	App->physics->CreateChain(0, 0, tri_izq, 30, 0.2);
	//if (!activation){
	App->physics->CreateChain(0, 0, via_superior, 112, 0.2);
	App->physics->CreateChain(0, 0, via_inferior, 44, 0.2);
	//if (activation){
	App->physics->CreateChain(0, 0, via_central, 76, 0.2);

	App->physics->CreateChain(0, 0, reb_der, 6, 4.0f);
	App->physics->CreateChain(0, 0, reb_izq, 6, 4.0f);

	App->physics->CreateCircleFix(183, 98, 55, 2.0f);
	App->physics->CreateCircleFix(215, 272, 35, 2.0f);
	App->physics->CreateCircleFix(290, 273, 35, 1.2f);
	App->physics->CreateCircleFix(255, 310, 30, 1.0f);
	App->physics->CreateCircleFix(364, 218, 35, 1.2f);
	App->physics->CreateCircleFix(425, 266, 35, 1.2f);
	App->physics->CreateCircleFix(470, 208, 35, 1.2f);

	App->physics->CreateRectangle(670, 825, 40, 80, 10.0f, b_dynamic);

	flipper_izq = App->physics->CreateRectangle(300, 905, 100, 25, 0, b_dynamic);
	flipper_izq_wheel = App->physics->CreateCircleFix(255, 905, 20, 0);
	
	App->physics->CreateRevoluteJoint(flipper_izq, flipper_izq_wheel, -42, 0, 0, 0, 30, -20);

	flipper_der = App->physics->CreateRectangle(420, 905, 100, 25, 0, b_dynamic);
	flipper_der_wheel = App->physics->CreateCircleFix(472, 905, 20, 0);

	App->physics->CreateRevoluteJoint(flipper_der, flipper_der_wheel, 42, 0, 0, 0, 20, -30);

	lanzadera = App->physics->CreateRectangle(663, 820, 41, 50, 0.0f, b_dynamic);
	eje_lanz = App->physics->CreateCircleFix(640, 765, 10, 0);
	App->physics->CreateLineJoint(lanzadera, eje_lanz, 20.0f, 1.0f);

	return true;
}

// 
update_status ModulePhysics::PreUpdate()
{
	world->Step(1.0f / 60.0f, 6, 2);

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		flipper_izq->Turn(-360);
	}

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		flipper_der->Turn(360);
	}

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_UP)
	{
		flipper_izq->Turn(720);
	}

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_UP)
	{
		flipper_der->Turn(-720);
	}


	// TODO: HomeWork
	/*
	for(b2Contact* c = world->GetContactList(); c; c = c->GetNext())
	{
	}
	*/

	return UPDATE_CONTINUE;
}

PhysBody* ModulePhysics::CreateCircleFix(int x, int y, int diam, float rest)
{
	b2BodyDef body;
	body.type = b2_staticBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);

	b2CircleShape shape;
	shape.m_radius = PIXEL_TO_METERS(diam) * 0.5f;

	b2FixtureDef fixture;
	fixture.shape = &shape;
	fixture.restitution = rest;
	b->CreateFixture(&fixture);

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	pbody->width = pbody->height = diam;

	return pbody;
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

PhysBody* ModulePhysics::CreateCircle(int x, int y, int radius)
{
	b2BodyDef body;
	body.type = b2_dynamicBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);

	b2CircleShape shape;
	shape.m_radius = PIXEL_TO_METERS(radius);
	b2FixtureDef fixture;
	fixture.shape = &shape;
	fixture.density = 1.0f;
	fixture.restitution = 0;
	fixture.friction = 5;
	b->CreateFixture(&fixture);

	// TODO 4: add a pointer to PhysBody as UserData to the body
	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	pbody->width = pbody->height = radius;

	return pbody;
}

PhysBody* ModulePhysics::CreateRectangle(int x, int y, int width, int height, float rest, body_type type)
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
	b2PolygonShape box;
	box.SetAsBox(PIXEL_TO_METERS(width) * 0.5f, PIXEL_TO_METERS(height) * 0.5f);

	b2FixtureDef fixture;
	fixture.shape = &box;
	fixture.density = 1.0f;
	fixture.restitution = rest;
	b->CreateFixture(&fixture);

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	pbody->width = width * 0.5f;
	pbody->height = height * 0.5f;

	return pbody;
}

PhysBody* ModulePhysics::CreateChain(int x, int y, int* points, int size, float rest)
{
	b2BodyDef body;
	body.type = b2_staticBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);

	b2ChainShape shape;
	b2Vec2* p = new b2Vec2[size / 2];

	for(uint i = 0; i < size / 2; ++i)
	{
		p[i].x = PIXEL_TO_METERS(points[i * 2 + 0]);
		p[i].y = PIXEL_TO_METERS(points[i * 2 + 1]);
	}

	shape.CreateLoop(p, size / 2);

	b2FixtureDef fixture;
	fixture.shape = &shape;
	fixture.restitution = rest;
	b->CreateFixture(&fixture);

	delete p;

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	pbody->width = pbody->height = 0;

	return pbody;
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

// TODO 3

// TODO 7: Call the listeners that are not NULL

PhysBody::PhysBody(b2Body* body, const SDL_Rect& rect, body_type type) : body(body), rect(rect), type(type), listener(NULL)
{}

PhysBody::PhysBody(){};

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