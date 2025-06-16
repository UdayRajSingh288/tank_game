#ifndef TANK_GAME_H
#define TANK_GAME_H

/* List of colors RGB values */
#define RANI_COLOR 0xFF00FF
#define TITLE_COLOR 0x1B4266
#define BUTTON_UNFOCUSED_COLOR 0x3BE2D9
#define BUTTON_FOCUSED_COLOR 0x291B49

/* Image sizes of used images */
#define SAND_IMG_W 256
#define SAND_IMG_H 256
#define CHAR_IMG_W 256
#define CHAR_IMG_H 128

/* Bitmap character information */
#define CHAR_W 16			/* Width of character */
#define CHAR_H 16			/* Height of character */
#define NUM_CHAR (CHAR_IMG_W / CHAR_W)	/* Number of characters in a row */

/* Return values for function main_menu() */
enum {
	SINGLEPLAYER_MM,		/* Open single player menu */
	MULTIPLAYER_HOST_MM,		/* Open multiplayer host menu */
	MULTIPLAYER_CLIENT_MM,		/* Open multiplayer client menu */
	CREATOR_MM,			/* Quit game */
	QUIT_MM,			/* ERROR */
	ERROR_MM
};

/* Flag values for 'alignment' parameter in function draw_text() */
enum {
	TEXT_CENTER,			/* Text be center aligned */
	TEXT_LEFT,			/* Text be left aligned */
	TEXT_RIGHT,			/* Text be right aligned */
	TEXT_CENTER_TRANSL		/* Text be center aligned and translucent */
};

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

union rgb {
	char s;
	char r;
	char g;
	char b;
	int hex;
};

typedef int score[2];

int draw_tiled_background(FILE *logfp, SDL_Renderer *renderer, SDL_Texture *tex, const int ww, const int wh, const int tw, const int th);
int draw_text(FILE *logfp, SDL_Renderer *renderer, SDL_Texture *char_tex, const char *str, const SDL_FRect *space, const int color, const int alignment);

#endif