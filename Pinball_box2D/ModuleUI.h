#ifndef __MODULEUI_H__
#define __MODULEUI_H__

#include "Module.h"
#include "p2Point.h"

class ModuleUI : public Module
{
public:

	ModuleUI();
	~ModuleUI();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	enum POINTS {
		HUNDRED,
		HUNDREDX2,
		HUNDREDX3,
		HUNDREDX4,
		HUNDREDX6,
		HUNDREDX8,

		THOUSAND,
		THOUSANDX3,
		THOUSANDX5,

		MAX_POINTS
	};

	SDL_Texture * numbers_tx = nullptr;
	SDL_Texture * score_tx = nullptr;

	SDL_Rect number = { 0,0,45,64 };

	SDL_Rect points[POINTS];

	int score = 0;
};
#endif // !__MODULEUI_H__
