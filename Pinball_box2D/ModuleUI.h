#ifndef __MODULEUI_H__
#define __MODULEUI_H__

#include "Module.h"
#include "p2Point.h"

class ModuleUI : public Module
{
public:

	ModuleUI(Application* app, bool start_enabled = true);
	~ModuleUI();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	/*enum POINTS {
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
	};*/

	//SDL_Texture * numbers_tx = nullptr;
	SDL_Texture * score_tx = nullptr;

	SDL_Rect number = { 0,0,45,64 };

	//SDL_Rect points[POINTS::MAX_POINTS]; //Rects of little numbers that appears next ball like +100 or +3000 that increase puntuation

	int font = -1;

	int		score = 0;
	char	score_text[15];
	int		high_score = 0;
	char	high_score_text[15];
};
#endif // !__MODULEUI_H__
