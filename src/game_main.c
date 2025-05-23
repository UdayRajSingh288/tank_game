#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL.h>


static const char *app_name = "Tank Game";
static const char *app_ver = "1.0";


static inline int game_init(SDL_Window **window, SDL_Renderer **renderer){
	SDL_DisplayID *display_ids;
	SDL_DisplayMode *display_mode;
	int displays;

	if (false == SDL_SetAppMetadata(app_name, app_ver, NULL)){
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_SetAppMetadata() error\n%s\n", SDL_GetError());
		return EXIT_FAILURE;
	}
	if (false == SDL_Init(SDL_INIT_VIDEO)){
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_Init() error\n%s\n", SDL_GetError());
		return EXIT_FAILURE;
	}
	display_ids = SDL_GetDisplays(&displays);
	if (NULL == display_ids){
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_GetDisplays() error\n%s\n", SDL_GetError());
		SDL_Quit();
		return EXIT_FAILURE;
	}
	printf("Found %d display/s\n", displays);
	display_mode = SDL_GetCurrentDisplayMode(display_ids[0]);
	SDL_free(display_ids);
	if (NULL == display_mode){
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_GetCurrentDisplayMode() error\n%s\n", SDL_GetError());
		SDL_Quit();
		return EXIT_FAILURE;
	}
	*window = SDL_CreateWindow(app_name, display_mode->w, display_mode->h, SDL_WINDOW_FULLSCREEN);
	if (NULL == *window){
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_CreateWindow() error\n%s\n", SDL_GetError());
		SDL_Quit();
		return EXIT_FAILURE;
	}
	*renderer = SDL_CreateRenderer(*window, NULL);
	if (NULL == *renderer){
		SDL_DestroyWindow(*window);
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_CreateRenderer() error\n%s\n", SDL_GetError());
		SDL_Quit();
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

int main(int argc, char *argv[]){
	SDL_Event event;
	SDL_Window *window;
	SDL_Renderer *renderer;
	bool game_running;

	if (game_init(&window, &renderer)){
		return EXIT_FAILURE;
	}

	game_running = true;
	while (game_running){
		if (SDL_PollEvent(&event)){
			if (SDL_EVENT_KEY_DOWN == event.type && SDLK_ESCAPE == event.key.key){
				game_running = false;
			}
		}
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return EXIT_SUCCESS;
}