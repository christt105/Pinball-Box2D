#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "p2SString.h"
#include "Globals.h"

class PhysBody;
class b2PrismaticJoint;
class b2Vec2;


struct Kicker {
	PhysBody* launch;
	PhysBody* stop;
	b2PrismaticJoint* joint;
	SDL_Texture* kicker_tx = nullptr;
	float force = 0.0f;
};

struct Arrow {
	PhysBody* arrow1;
	PhysBody* arrow2;
	PhysBody* arrow3;
	PhysBody* arrow4;
	PhysBody* arrow5;
	PhysBody* arrow6;
	PhysBody* arrow7;
	PhysBody* arrow8;
	PhysBody* arrow9;
	PhysBody* arrow10;
	bool light1 = false;
	bool light2 = false;
	bool light3 = false;
	bool light4 = false;
	bool light5 = false;
	bool light6 = false;
	bool light7 = false;
	bool light8 = false;
	bool light9 = false;
	bool light10 = false;
	SDL_Rect arrow_rect;
	SDL_Rect arrow_on_rect;
	bool arrow_time = false;
};




class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	bool CleanUp();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

public:

	
	PhysBody*			back = nullptr;
	PhysBody*			flipper_left = nullptr;
	PhysBody*			flipper_right = nullptr;
	PhysBody*			structure_right = nullptr;
	PhysBody*			structure_left = nullptr;
	PhysBody*			flipper_structure_left = nullptr;
	PhysBody*			flipper_structure_right = nullptr;
	PhysBody*			triangle_right = nullptr;
	PhysBody*			triangle_left = nullptr;
	PhysBody*			capsule1 = nullptr;
	PhysBody*			capsule2 = nullptr;
	PhysBody*			capsule3 = nullptr;
	PhysBody*			circle1 = nullptr;
	PhysBody*			circle2 = nullptr;
	PhysBody*			circle3 = nullptr;
	PhysBody*			rebound_tp1 = nullptr;
	PhysBody*			rebound_tp2 = nullptr;
	PhysBody*			tp_1 = nullptr;
	PhysBody*			tp_2 = nullptr;
	PhysBody*			pink_1 = nullptr;
	PhysBody*			pink_2 = nullptr;
	PhysBody*			pink_3 = nullptr;
	PhysBody*			pink_4 = nullptr;


public: 

	Kicker kicker;
	Kicker impulse_1;
	Kicker impulse_2;

	Arrow arrow;

	PhysBody*			sensor = nullptr;

	PhysBody*			unlocker = nullptr;
	PhysBody*			unlocker_rectangle = nullptr;
	bool				unlocker_closed = false;

	bool				sensed;

	SDL_Texture*		background_tx = nullptr;
	SDL_Texture*		layout_tx = nullptr;
	SDL_Texture*		layout_alpha_tx = nullptr;
	SDL_Texture*		circle_robound_tx;
	SDL_Texture*		press_space_tx;

	SDL_Rect			circle_robound1_rect;
	SDL_Rect			circle_robound2_rect;
	SDL_Rect			tp_rect;
	SDL_Rect			unlocker_rect;
	SDL_Rect			pink_off_rect;
	SDL_Rect			pink_on_rect;
	SDL_Rect			tp_rebound_rect;

	float				angle_rot = 0.0F;
	
	uint				bonus_fx;
	uint				kicker_fx;
	uint				circle_fx;
	uint				triangle_fx;
	uint				dead_fx;
	uint				game_over_fx;
	uint				tp_rebounder_fx;
	uint				unlocker_closed_fx;
	uint				center_launch_fx;
	uint				pink_light_fx;

	bool				pink1 = false;
	bool				pink2 = false;
	bool				pink3 = false;
	bool				pink4 = false;

	uint				init_time = 0; 
	uint				current_time = 0; 
	bool				timer = true;
};
