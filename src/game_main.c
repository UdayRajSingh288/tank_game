#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL.h>
#include <tank_game.h>

static const char *app_name = "Tank Game";
static const char *app_ver = "1.0";
static const char *logname = "game_log.txt";
const char *sand_img = "sprites/sand.bmp";
const char *char_img = "sprites/char.bmp";


/* Return codes for function main_menu() */
enum {SINGLEPLAYER_MM, MULTIPLAYER_HOST_MM, MULTIPLAYER_CLIENT_MM, CREATOR_MM, QUIT_MM, ERROR_MM};

/* This function draws main menu */
static inline int main_menu(SDL_Window *window, SDL_Renderer *renderer, FILE *logfp){
	SDL_Surface *surface;
	SDL_Texture *sand_tex, *char_tex;
	int w, h;

	surface = SDL_LoadBMP(sand_img);
	if (NULL == surface){
		fprintf(logfp, "SDL_LoadBMP() error file game_main.c line %d\n%s\n", __LINE__, SDL_GetError());
		return ERROR_MM;
	}
	sand_tex = SDL_CreateTextureFromSurface(renderer, surface);
	if (NULL == sand_tex){
		fprintf(logfp, "SDL_CreateTextureFromSurface() error file game_main.c line %d\n%s\n", __LINE__, SDL_GetError());
		return ERROR_MM;
	}
	SDL_DestroySurface(surface);
	surface = SDL_LoadBMP(char_img);
	if (NULL == surface){
		fprintf(logfp, "SDL_LoadBMP() error file game_main.c line %d\n%s\n", __LINE__, SDL_GetError());
		return ERROR_MM;
	}
	if (false == SDL_SetSurfaceColorKey(surface, true, RANI_COLOR)){
		fprintf(logfp, "SDL_SetSurfaceColorKey() error file game_main.c line %d\n%s\n", __LINE__, SDL_GetError());
		return ERROR_MM;
	}
	char_tex = SDL_CreateTextureFromSurface(renderer, surface);
	if (NULL == char_tex){
		fprintf(logfp, "SDL_CreateTextureFromSurface() error file game_main.c line %d\n%s\n", __LINE__, SDL_GetError());
		return ERROR_MM;
	}
	SDL_DestroySurface(surface);
	if (false == SDL_GetWindowSize(window, &w, &h)){
		fprintf(logfp, "SDL_GetWindowSize() error file game_main.c line %d\n%s\n", __LINE__, SDL_GetError());
		return ERROR_MM;
	}
	if (EXIT_FAILURE == draw_bg(logfp, renderer, sand_tex, w, h, 256, 256)){
		fprintf(logfp, "draw_bg() error file game_main.c line %d\n", __LINE__);
		return ERROR_MM;
	}
}


static inline int game_init(SDL_Window **window, SDL_Renderer **renderer, FILE **logfp){
	SDL_DisplayID *display_ids;
	const SDL_DisplayMode *display_mode;
	int displays;

	*logfp = fopen(logname, "w");
	if (NULL == *logfp){
		printf("fopen() error\n");
		return EXIT_FAILURE;
	}
	if (false == SDL_SetAppMetadata(app_name, app_ver, NULL)){
		fprintf(*logfp, "SDL_SetAppMetadata() error file game_main.c line %d\n%s\n", __LINE__, SDL_GetError());
		fclose(*logfp);
		return EXIT_FAILURE;
	}
	if (false == SDL_Init(SDL_INIT_VIDEO)){
		fprintf(*logfp, "SDL_Init() error file game_main.c line %d\n%s\n", __LINE__, SDL_GetError());
		fclose(*logfp);
		return EXIT_FAILURE;
	}
	display_ids = SDL_GetDisplays(&displays);
	if (NULL == display_ids){
		fprintf(*logfp, "SDL_GetDisplays() error file game_main.c line %d\n%s\n", __LINE__, SDL_GetError());
		fclose(*logfp);
		SDL_Quit();
		return EXIT_FAILURE;
	}
	fprintf(*logfp, "Found %d display/s\n", displays);
	display_mode = SDL_GetCurrentDisplayMode(display_ids[0]);
	SDL_free(display_ids);
	if (NULL == display_mode){
		fprintf(*logfp, "SDL_GetCurrentDisplayMode() error file game_main.c line %d\n%s\n", __LINE__, SDL_GetError());
		fclose(*logfp);
		SDL_Quit();
		return EXIT_FAILURE;
	}
	*window = SDL_CreateWindow(app_name, display_mode->w, display_mode->h, SDL_WINDOW_FULLSCREEN);
	if (NULL == *window){
		fprintf(*logfp, "SDL_CreateWindow() error file game_main.c line %d\n%s\n", __LINE__, SDL_GetError());
		fclose(*logfp);
		SDL_Quit();
		return EXIT_FAILURE;
	}
	*renderer = SDL_CreateRenderer(*window, NULL);
	if (NULL == *renderer){
		fprintf(*logfp, "SDL_CreateRenderer() error file game_main.c line %d\n%s\n", __LINE__, SDL_GetError());
		fclose(*logfp);
		SDL_DestroyWindow(*window);
		SDL_Quit();
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

int main(int argc, char *argv[]){
	SDL_Event event;
	SDL_Window *window;
	SDL_Renderer *renderer;
	FILE *logfp;
	int rc;

	if (game_init(&window, &renderer, &logfp)){
		return EXIT_FAILURE;
	}

	rc = main_menu(window, renderer, logfp);

	fclose(logfp);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return EXIT_SUCCESS;
}