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
	bool activation = false;

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
	sfx_flipper = App->audio->LoadFx("pinball/flipper.wav"); // Provisional


	// MAPA

	int	map[156] = {
		676, 747,
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
		634, 747,
		646, 999,
		688, 999
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

	int muerte[4] = {
		303, 1000,
		463, 1000
	};


	App->physics->CreateObj(0, 0, map, 156, 0, 0, 0, 0.2f, false, b_static);
	App->physics->CreateObj(0, 0, barras_cash, 16, 0, 0, 0, 0.2f, false, b_static);
	App->physics->CreateObj(0, 0, barras_cash_2, 16, 0, 0, 0, 0.2f, false, b_static);
	App->physics->CreateObj(0, 0, barras_sup, 16, 0, 0, 0, 0.2f, false, b_static);
	App->physics->CreateObj(0, 0, barras_sup_2, 16, 0, 0, 0, 0.2f, false, b_static);
	App->physics->CreateObj(0, 0, base_flip_der, 20, 0, 0, 0, 0.2f, false, b_static);
	App->physics->CreateObj(0, 0, base_flip_izq, 22, 0, 0, 0, 0.2f, false, b_static);
	App->physics->CreateObj(0, 0, cash, 192, 0, 0, 0, 0.2f, false, b_static);
	App->physics->CreateObj(0, 0, curva_der_arriba, 52, 0, 0, 0, 0.2f, false, b_static);
	App->physics->CreateObj(0, 0, tri_der, 30, 0, 0, 0, 0.2f, false, b_static);
	App->physics->CreateObj(0, 0, tri_izq, 30, 0, 0, 0, 0.2f, false, b_static);
	App->physics->CreateObj(0, 0, reb_der, 6, 0, 0, 0, 0.2f, false, b_static);
	App->physics->CreateObj(0, 0, reb_izq, 6, 0, 0, 0, 0.2f, false, b_static);

	//SENSOR MUERTE ABAJO
	//App->physics->CreateObj(0, 0, muerte, 4, 0, 0, 0, 0, true, b_static);



	// PUENTE
	if (!activation)
	{
		App->physics->CreateObj(0, 0, via_superior, 112, 0, 0, 0, 0.2f, false, b_static);
		App->physics->CreateObj(0, 0, via_inferior, 44, 0, 0, 0, 0.2f, false, b_static);
	}
	if (activation)
	{
		App->physics->CreateObj(0, 0, via_central, 76, 0, 0, 0, 0.2f, false, b_static);
	}

	App->physics->CreateObj(183, 98, NULL, 0, 55, 0, 0, 1.2f, false, b_static);
	App->physics->CreateObj(215, 272, NULL, 0, 35, 0, 0, 1.2f, false, b_static);
	App->physics->CreateObj(290, 273, NULL, 0, 35, 0, 0, 1.2f, false, b_static);
	App->physics->CreateObj(255, 310, NULL, 0, 30, 0, 0, 1.0f, false, b_static);
	App->physics->CreateObj(364, 218, NULL, 0, 35, 0, 0, 1.2f, false, b_static);
	App->physics->CreateObj(425, 266, NULL, 0, 35, 0, 0, 1.2f, false, b_static);
	App->physics->CreateObj(470, 208, NULL, 0, 35, 0, 0, 1.2f, false, b_static);

	flipper_izq = App->physics->CreateObj(300, 905, NULL, 0, 0, 100, 25, 0, false, b_dynamic);
	flipper_izq_wheel = App->physics->CreateObj(255, 905, NULL, 0, 20, 0, 0, 0, true, b_static);
	

	App->physics->CreateRevoluteJoint(flipper_izq, flipper_izq_wheel, -42, 0, 0, 0, 30, -20);

	flipper_der = App->physics->CreateObj(420, 905, NULL, 0, 0, 100, 25, 0, false, b_dynamic);
		
	flipper_der_wheel = App->physics->CreateObj(472, 905, NULL, 0, 20, 0, 0, 0, false, b_static);
	

	App->physics->CreateRevoluteJoint(flipper_der, flipper_der_wheel, 42, 0, 0, 0, 20, -30);

	lanzadera = App->physics->CreateObj(647, 810, NULL, 0, 0, 48, 25, 0, false, b_dynamic);
	eje_lanz = App->physics->CreateObj(630, 722, NULL, 0, 1, 0, 0, 0, false, b_static);
	App->physics->CreateLineJoint(lanzadera, eje_lanz, 20.0f, 1.0f);
	ball = false;
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
	// KEYBOARD
	if (!App->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN)
		App->renderer->Blit(background, 0, 0, NULL, 0, 0);

	if(App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
		circles.add(App->physics->CreateObj(App->input->GetMouseX(), App->input->GetMouseY(), NULL, 0, 20, 0, 0, 0, false, b_dynamic));

	if (!ball)
	{
		circles.add(App->physics->CreateObj(670, 730, NULL, 0, 20, 0, 0, 0, false, b_dynamic));
		ball = true;
	}
		

	if ((App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN) || App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
		App->audio->PlayFx(sfx_flipper);

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN)
		flipper_izq->Turn(-360);
	
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
		flipper_der->Turn(360);

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_UP)
		flipper_izq->Turn(1000);

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_UP)
		flipper_der->Turn(-1000);
	
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_UP)
		App->audio->PlayFx(sfx_launcher);

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT && pot < 20000)
	{
		pot += 100.0f;
	    lanzadera->Push(0, pot);
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

	if (!activation)
		App->renderer->Blit(foreground, 0, 0, NULL);

	return UPDATE_CONTINUE;
}

// TODO 8: Now just define collision callback for the circle and play bonus_fx audio
