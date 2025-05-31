#ifndef TANK_GAME_H
#define TANK_GAME_H

/* List of colors RGB values */
#define RANI_COLOR 0xFF00FF

/* Image sizes of used images */
#define SAND_IMG_W 256
#define SAND_IMG_H 256
#define CHAR_IMG_W 256
#define CHAR_IMG_H 128

/* Dimensions of a character in bitmap */
#define CHAR_W 16
#define CHAR_H 16

/* Number of characters in a row in the bitmap */
#define NUM_CHAR (CHAR_IMG_W / CHAR_W)

struct tank {
	char name[16];
	float x;
	float y;
	float speed;
	float angle;
	int health;
	int shells;
	int id;
};

struct shell {
	float x;
	float y;
	float angle;
	int ms;
	int tank_id;
};

typedef score int[2];

/* Functions that need to be visible globally are declared here */
int draw_bg(FILE *logfp, SDL_Renderer *renderer, SDL_Texture *tex, const int ww, const int wh, const int tw, const int th);


#endif