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
	circle = box = rick = NULL;
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

	circle = App->textures->Load("pinball/Ball.png"); 
	box = App->textures->Load("pinball/crate.png");
	rick = App->textures->Load("pinball/rick_head.png");
	bonus_fx = App->audio->LoadFx("pinball/bonus.wav");
	background = App->textures->Load("pinball/PinballBackGround.png");


	GenBackground();
	// TODO: Homework - create a sensor

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
	App->renderer->Blit(background, 0, 0, NULL, 0, 0);

	if(App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		circles.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 8));
	}
	
	

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
		if(c->data->Contains(App->input->GetMouseX(), App->input->GetMouseY()))
			App->renderer->Blit(circle, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	c = boxes.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(box, x, y, NULL, 1.0f, c->data->GetRotation());
		if(ray_on)
		{
			int hit = c->data->RayCast(ray.x, ray.y, mouse.x, mouse.y, normal.x, normal.y);
			if(hit >= 0)
				ray_hit = hit;
		}
		c = c->next;
	}

	c = ricks.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(rick, x, y, NULL, 1.0f, c->data->GetRotation());
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

	return UPDATE_CONTINUE;
}

// TODO 8: Now just define collision callback for the circle and play bonus_fx audio


bool ModuleSceneIntro::GenBackground()
{
	int map[204] = {
		686, 988,
		651, 988,
		647, 413,
		632, 418,
		635, 989,
		598, 989,
		597, 951,
		590, 940,
		578, 938,
		413, 979,
		420, 989,
		282, 990,
		300, 980,
		146, 941,
		134, 947,
		130, 957,
		130, 975,
		123, 989,
		87, 988,
		93, 972,
		95, 747,
		95, 710,
		105, 687,
		126, 670,
		119, 660,
		109, 653,
		100, 640,
		99, 625,
		108, 611,
		121, 606,
		135, 609,
		146, 612,
		152, 612,
		156, 607,
		159, 600,
		168, 572,
		168, 563,
		162, 557,
		152, 557,
		144, 550,
		137, 543,
		136, 533,
		139, 522,
		142, 513,
		149, 505,
		154, 500,
		157, 494,
		149, 486,
		142, 477,
		106, 428,
		90, 399,
		76, 370,
		69, 346,
		65, 317,
		65, 286,
		67, 263,
		70, 249,
		76, 229,
		87, 203,
		103, 182,
		115, 163,
		121, 156,
		116, 145,
		98, 126,
		92, 106,
		93, 83,
		102, 64,
		117, 54,
		134, 47,
		152, 46,
		168, 50,
		183, 55,
		195, 66,
		207, 79,
		211, 87,
		217, 93,
		236, 88,
		258, 83,
		282, 80,
		316, 76,
		346, 74,
		370, 74,
		395, 74,
		418, 75,
		448, 77,
		474, 81,
		496, 85,
		521, 91,
		551, 102,
		569, 109,
		589, 120,
		608, 134,
		625, 148,
		638, 164,
		650, 181,
		660, 202,
		668, 224,
		672, 245,
		683, 368,
		683, 435,
		689, 781,
		686, 986
	};

	int barras_cash[16] = {
		205, 240,
		206, 254,
		208, 259,
		214, 259,
		215, 252,
		213, 240,
		211, 235,
		206, 236
	};

	int barras_cash_2[16] = {
		225 + 23, 245 + 3,
		226 + 23, 259 + 3,
		228 + 23, 264 + 3,
		234 + 23, 264 + 3,
		235 + 23, 257 + 3,
		233 + 23, 245 + 3,
		231 + 23, 240 + 3,
		226 + 23, 241 + 3
	};

	int barras_sup[12] = {
		378, 138,
		379, 167,
		387, 176,
		394, 168,
		393, 138,
		385, 131
	};

	int barras_sup_2[12] = {
		378 + 60, 138,
		379 + 60, 167,
		387 + 60, 176,
		394 + 60, 168,
		393 + 60, 138,
		385 + 60, 131
	};

	int base_flip_der[18] = {
		592, 715,
		590, 865,
		489, 901,
		495, 910,
		499, 914,
		498, 924,
		591, 895,
		594, 889,
		597, 714
	};

	int base_flip_izq[22] = {
		142, 732,
		142, 857,
		143, 866,
		245, 901,
		239, 906,
		233, 914,
		236, 926,
		146, 899,
		140, 894,
		137, 886,
		138, 732
	};

	int cash[189] = {
		251, 152,
		216, 166,
		188, 181,
		166, 198,
		146, 217,
		124, 251,
		115, 271,
		112, 297,
		113, 327,
		115, 342,
		120, 356,
		127, 372,
		139, 392,
		155, 413,
		188, 452,
		193, 452,
		193, 447,
		175, 427,
		163, 414,
		153, 398,
		138, 375,
		126, 352,
		122, 339,
		120, 325,
		119, 309,
		120, 290,
		121, 278,
		123, 271,
		130, 258,
		139, 243,
		158, 223,
		184, 203,
		208, 191,
		223, 187,
		241, 183,
		257, 185,
		264, 189,
		269, 195,
		274, 202,
		278, 215,
		282, 228,
		285, 240,
		288, 252,
		289, 262,
		289, 268,
		280, 283,
		299, 317,
		306, 324,
		315, 362,
		319, 378,
		317, 390,
		308, 398,
		295, 402,
		282, 399,
		268, 393,
		245, 392,
		225, 392,
		209, 385,
		199, 376,
		190, 362,
		188, 349,
		188, 337,
		190, 327,
		192, 318,
		176, 282,
		172, 262,
		169, 251,
		162, 252,
		158, 259,
		153, 267,
		150, 282,
		147, 302,
		148, 315,
		150, 327,
		154, 340,
		160, 352,
		165, 361,
		183, 382,
		235, 423,
		248, 432,
		291, 414,
		305, 408,
		315, 402,
		323, 394,
		326, 387,
		327, 375,
		286, 212,
		329, 164,
		330, 154,
		322, 142,
		307, 136,
		294, 137,
		285, 140,
		271, 144,
	};

	int curva_der_arriba[52] = {
		503, 171,
		529, 174,
		552, 178,
		574, 190,
		593, 209,
		610, 232,
		623, 258,
		630, 278,
		635, 294,
		637, 319,
		641, 325,
		649, 322,
		649, 303,
		645, 282,
		638, 252,
		629, 223,
		615, 195,
		598, 173,
		580, 159,
		557, 146,
		532, 138,
		514, 134,
		503, 134,
		498, 139,
		498, 152,
		500, 164
	};

	int tri_der[30] = {
		535, 745,
		485, 842,
		482, 849,
		483, 855,
		488, 860,
		495, 862,
		503, 860,
		549, 843,
		554, 838,
		557, 832,
		556, 748,
		553, 741,
		548, 738,
		543, 738,
		538, 741
	};

	int tri_izq[30] = {
		196, 748,
		246, 842,
		250, 850,
		249, 856,
		244, 861,
		238, 863,
		231, 862,
		184, 844,
		177, 839,
		175, 832,
		176, 749,
		177, 744,
		181, 741,
		187, 741,
		191, 744
	};

	int via_1[104] = {
		547, 566,
		515, 593,
		550, 650,
		558, 652,
		556, 610,
		553, 575,
		547, 555,
		540, 533,
		505, 444,
		474, 371,
		465, 348,
		463, 330,
		465, 301,
		476, 274,
		492, 261,
		514, 252,
		541, 250,
		561, 255,
		578, 267,
		592, 284,
		598, 310,
		597, 325,
		590, 344,
		582, 360,
		569, 379,
		552, 406,
		533, 430,
		546, 460,
		586, 386,
		599, 352,
		603, 326,
		604, 300,
		593, 272,
		571, 242,
		554, 228,
		536, 215,
		521, 208,
		510, 208,
		506, 211,
		508, 220,
		476, 258,
		456, 284,
		445, 322,
		450, 351,
		460, 377,
		447, 409,
		430, 436,
		445, 466,
		492, 415,
		517, 475,
		542, 540,
		547, 564
	};

	int via_centro[28] = {
		570, 526,
		520, 400,
		493, 332,
		492, 311,
		497, 295,
		508, 280,
		524, 273,
		544, 273,
		560, 281,
		569, 297,
		571, 313,
		566, 331,
		523, 398,
		568, 515
	};

	int via_der_abajo[18] = {
		587, 648,
		601, 649,
		604, 563,
		603, 487,
		600, 480,
		589, 490,
		572, 526,
		584, 571,
		587, 626
	};

	
	backgrounds.add(App->physics->CreateChain(0, 0, map, 204, 0.2));
	backgrounds.add(App->physics->CreateChain(0, 0, barras_cash, 16, 0.2));
	backgrounds.add(App->physics->CreateChain(0, 0, barras_cash_2, 16, 0.2));
	backgrounds.add(App->physics->CreateChain(0, 0, barras_sup, 12, 0.2));
	backgrounds.add(App->physics->CreateChain(0, 0, barras_sup_2, 12, 0.2));
	backgrounds.add(App->physics->CreateChain(0, 0, base_flip_der, 18, 0.2));
	backgrounds.add(App->physics->CreateChain(0, 0, base_flip_izq, 22, 0.2));
	backgrounds.add(App->physics->CreateChain(0, 0, cash, 189, 0.2));
	backgrounds.add(App->physics->CreateChain(0, 0, curva_der_arriba, 52, 0.2));
	backgrounds.add(App->physics->CreateChain(0, 0, tri_der, 30, 2));
	backgrounds.add(App->physics->CreateChain(0, 0, tri_izq, 30, 2));
	//backgrounds.add(App->physics->CreateChain(0, 0, via_1, 104, 0.2));
	//backgrounds.add(App->physics->CreateChain(0, 0, via_centro, 28, 0.2));
	backgrounds.add(App->physics->CreateChain(0, 0, via_der_abajo, 18, 0.2));

	backgrounds.add(App->physics->CreateCircleFix(149, 96, 61, 2));
	backgrounds.add(App->physics->CreateCircleFix(197, 300, 39, 1.5f));
	backgrounds.add(App->physics->CreateCircleFix(285, 304, 39, 1.5f));
	backgrounds.add(App->physics->CreateCircleFix(242, 347, 39, 1.5f));
	backgrounds.add(App->physics->CreateCircleFix(365, 242, 45, 1.5f));
	backgrounds.add(App->physics->CreateCircleFix(433, 296, 45, 1.5f));
	backgrounds.add(App->physics->CreateCircleFix(484, 236, 45, 1.5f));

	backgrounds.add(App->physics->CreateRectangle(670, 825, 40, 80, 10.0f));
	return true;
}