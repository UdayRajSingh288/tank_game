#ifndef TANK_GAME_H
#define TANK_GAME_H

#define TANK_ACCL 1.0F
#define PROJ_SPEED 50.0F
#define RANI_COLOR 0xFF00FF

struct tank {
	float x;
	float y;
	float speed;
	float angle;
	int id;
	int shells;
};

struct shell {
	float x;
	float y;
	float speed;
	float angle;
	int ms;
};


int draw_bg(FILE *logfp, SDL_Renderer *renderer, SDL_Texture *tex, const int ww, const int wh, const int tw, const int th);

#endif