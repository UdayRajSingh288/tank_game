#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL.h>
#include <tank_game.h>

static const char *app_name = "Tank Game";
static const char *app_ver = "1.0";
static const char *logname = "game_log.txt";
static const char *game_title_text = "TANK GAME";
static const char *singleplayer_button_text = "Singleplayer";
static const char *multiplayer_host_button_text = "Host server";
static const char *multiplayer_client_button_text = "Join server";
static const char *creator_button_text = "Creator";
static const char *quit_button_text = "Quit";
const char *sand_img = "sprites/sand.bmp";
const char *char_img = "sprites/char.bmp";

static inline int main_menu(SDL_Window *window, SDL_Renderer *renderer, FILE *logfp){
	SDL_Surface *surface;
	SDL_Texture *sand_tex, *char_tex;
	SDL_Event event;
	SDL_FRect t_rect, sp_rect, mphost_rect, mpclient_rect, cr_rect, qt_rect;
	SDL_FPoint mp;
	union rgb u;
	int w, h, bw, bh, x, r;
	bool sp_focus, mphost_focus, mpclient_focus, cr_focus, qt_focus;

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
	bh = h / 14;
	bw = w / 2;
	x = ((w - bw) / 2);
	t_rect.w = (float)bw;
	t_rect.h = (float)(2 * bh);
	t_rect.x = (float)x;
	t_rect.y = (float)bh;
	sp_rect.w = (float)bw;
	sp_rect.h = (float)bh;
	sp_rect.x = (float)x;
	sp_rect.y = (float)(4 * bh);
	mphost_rect.w = (float)bw;
	mphost_rect.h = (float)bh;
	mphost_rect.x = (float)x;
	mphost_rect.y = (float)(6 * bh);
	mpclient_rect.w = (float)bw;
	mpclient_rect.h = (float)bh;
	mpclient_rect.x = (float)x;
	mpclient_rect.y = (float)(8 * bh);
	cr_rect.w = (float)bw;
	cr_rect.h = (float)bh;
	cr_rect.x = (float)x;
	cr_rect.y = (float)(10 * bh);
	qt_rect.w = (float)bw;
	qt_rect.h = (float)bh;
	qt_rect.x = (float)x;
	qt_rect.y = (float)(12 * bh);
	sp_focus = false;
	mphost_focus = false;
	mpclient_focus = false;
	cr_focus = false;
	qt_focus = false;
	while (true){
		if (EXIT_FAILURE == draw_tiled_background(logfp, renderer, sand_tex, w, h, SAND_IMG_W, SAND_IMG_H)){
			fprintf(logfp, "draw_bg() error file game_main.c line %d\n", __LINE__);
			return ERROR_MM;
		}
		if (EXIT_FAILURE == draw_text(logfp, renderer, char_tex, game_title_text, &t_rect, TITLE_COLOR, TEXT_CENTER)){
			fprintf(logfp, "draw_text() error file game_main.c line %d\n", __LINE__);
			return ERROR_MM;
		}
		if (sp_focus){
			u.hex = BUTTON_UNFOCUSED_COLOR;
			if (false == SDL_SetRenderDrawColor(renderer, u.v[2], u.v[1], u.v[0], 0xff)){
				fprintf(logfp, "SDL_SetRenderDrawColor() error file game_main.c line %d\n%s\n", __LINE__, SDL_GetError());
				return ERROR_MM;
			}
			if (false == SDL_RenderFillRect(renderer, &sp_rect)){
				fprintf(logfp, "SDL_RenderFillRect() error file game_main.c line %d\n%s\n", __LINE__, SDL_GetError());
				return ERROR_MM;
			}
			if (EXIT_FAILURE == draw_text(logfp, renderer, char_tex, singleplayer_button_text, &sp_rect, BUTTON_FOCUSED_COLOR, TEXT_CENTER)){
				fprintf(logfp, "draw_text() error file game_main.c line %d\n", __LINE__);
				return ERROR_MM;
			}
		}
		else {
			u.hex = BUTTON_FOCUSED_COLOR;
			if (false == SDL_SetRenderDrawColor(renderer, u.v[2], u.v[1], u.v[0], 0xff)){
				fprintf(logfp, "SDL_SetRenderDrawColor() error file game_main.c line %d\n%s\n", __LINE__, SDL_GetError());
				return ERROR_MM;
			}
			if (false == SDL_RenderFillRect(renderer, &sp_rect)){
				fprintf(logfp, "SDL_RenderFillRect() error file game_main.c line %d\n%s\n", __LINE__, SDL_GetError());
				return ERROR_MM;
			}
			if (EXIT_FAILURE == draw_text(logfp, renderer, char_tex, singleplayer_button_text, &sp_rect, BUTTON_UNFOCUSED_COLOR, TEXT_CENTER)){
				fprintf(logfp, "draw_text() error file game_main.c line %d\n", __LINE__);
				return ERROR_MM;
			}
		}
		if (mphost_focus){
			u.hex = BUTTON_UNFOCUSED_COLOR;
			if (false == SDL_SetRenderDrawColor(renderer, u.v[2], u.v[1], u.v[0], 0xff)){
				fprintf(logfp, "SDL_SetRenderDrawColor() error file game_main.c line %d\n%s\n", __LINE__, SDL_GetError());
				return ERROR_MM;
			}
			if (false == SDL_RenderFillRect(renderer, &mphost_rect)){
				fprintf(logfp, "SDL_RenderFillRect() error file game_main.c line %d\n%s\n", __LINE__, SDL_GetError());
				return ERROR_MM;
			}
			if (EXIT_FAILURE == draw_text(logfp, renderer, char_tex, multiplayer_host_button_text, &mphost_rect, BUTTON_FOCUSED_COLOR, TEXT_CENTER)){
				fprintf(logfp, "draw_text() error file game_main.c line %d\n", __LINE__);
				return ERROR_MM;
			}
		}
		else {
			u.hex = BUTTON_FOCUSED_COLOR;
			if (false == SDL_SetRenderDrawColor(renderer, u.v[2], u.v[1], u.v[0], 0xff)){
				fprintf(logfp, "SDL_SetRenderDrawColor() error file game_main.c line %d\n%s\n", __LINE__, SDL_GetError());
				return ERROR_MM;
			}
			if (false == SDL_RenderFillRect(renderer, &mphost_rect)){
				fprintf(logfp, "SDL_RenderFillRect() error file game_main.c line %d\n%s\n", __LINE__, SDL_GetError());
				return ERROR_MM;
			}
			if (EXIT_FAILURE == draw_text(logfp, renderer, char_tex, multiplayer_host_button_text, &mphost_rect, BUTTON_UNFOCUSED_COLOR, TEXT_CENTER)){
				fprintf(logfp, "draw_text() error file game_main.c line %d\n", __LINE__);
				return ERROR_MM;
			}
		}
		if (mpclient_focus){
			u.hex = BUTTON_UNFOCUSED_COLOR;
			if (false == SDL_SetRenderDrawColor(renderer, u.v[2], u.v[1], u.v[0], 0xff)){
				fprintf(logfp, "SDL_SetRenderDrawColor() error file game_main.c line %d\n%s\n", __LINE__, SDL_GetError());
				return ERROR_MM;
			}
			if (false == SDL_RenderFillRect(renderer, &mpclient_rect)){
				fprintf(logfp, "SDL_RenderFillRect() error file game_main.c line %d\n%s\n", __LINE__, SDL_GetError());
				return ERROR_MM;
			}
			if (EXIT_FAILURE == draw_text(logfp, renderer, char_tex, multiplayer_client_button_text, &mpclient_rect, BUTTON_FOCUSED_COLOR, TEXT_CENTER)){
				fprintf(logfp, "draw_text() error file game_main.c line %d\n", __LINE__);
				return ERROR_MM;
			}
		}
		else {
			u.hex = BUTTON_FOCUSED_COLOR;
			if (false == SDL_SetRenderDrawColor(renderer, u.v[2], u.v[1], u.v[0], 0xff)){
				fprintf(logfp, "SDL_SetRenderDrawColor() error file game_main.c line %d\n%s\n", __LINE__, SDL_GetError());
				return ERROR_MM;
			}
			if (false == SDL_RenderFillRect(renderer, &mpclient_rect)){
				fprintf(logfp, "SDL_RenderFillRect() error file game_main.c line %d\n%s\n", __LINE__, SDL_GetError());
				return ERROR_MM;
			}
			if (EXIT_FAILURE == draw_text(logfp, renderer, char_tex, multiplayer_client_button_text, &mpclient_rect, BUTTON_UNFOCUSED_COLOR, TEXT_CENTER)){
				fprintf(logfp, "draw_text() error file game_main.c line %d\n", __LINE__);
				return ERROR_MM;
			}
		}
		if (cr_focus){
			u.hex = BUTTON_UNFOCUSED_COLOR;
			if (false == SDL_SetRenderDrawColor(renderer, u.v[2], u.v[1], u.v[0], 0xff)){
				fprintf(logfp, "SDL_SetRenderDrawColor() error file game_main.c line %d\n%s\n", __LINE__, SDL_GetError());
				return ERROR_MM;
			}
			if (false == SDL_RenderFillRect(renderer, &cr_rect)){
				fprintf(logfp, "SDL_RenderFillRect() error file game_main.c line %d\n%s\n", __LINE__, SDL_GetError());
				return ERROR_MM;
			}
			if (EXIT_FAILURE == draw_text(logfp, renderer, char_tex, creator_button_text, &cr_rect, BUTTON_FOCUSED_COLOR, TEXT_CENTER)){
				fprintf(logfp, "draw_text() error file game_main.c line %d\n", __LINE__);
				return ERROR_MM;
			}
		}
		else {
			u.hex = BUTTON_FOCUSED_COLOR;
			if (false == SDL_SetRenderDrawColor(renderer, u.v[2], u.v[1], u.v[0], 0xff)){
				fprintf(logfp, "SDL_SetRenderDrawColor() error file game_main.c line %d\n%s\n", __LINE__, SDL_GetError());
				return ERROR_MM;
			}
			if (false == SDL_RenderFillRect(renderer, &cr_rect)){
				fprintf(logfp, "SDL_RenderFillRect() error file game_main.c line %d\n%s\n", __LINE__, SDL_GetError());
				return ERROR_MM;
			}
			if (EXIT_FAILURE == draw_text(logfp, renderer, char_tex, creator_button_text, &cr_rect, BUTTON_UNFOCUSED_COLOR, TEXT_CENTER)){
				fprintf(logfp, "draw_text() error file game_main.c line %d\n", __LINE__);
				return ERROR_MM;
			}
		}
		if (qt_focus){
			u.hex = BUTTON_UNFOCUSED_COLOR;
			if (false == SDL_SetRenderDrawColor(renderer, u.v[2], u.v[1], u.v[0], 0xff)){
				fprintf(logfp, "SDL_SetRenderDrawColor() error file game_main.c line %d\n%s\n", __LINE__, SDL_GetError());
				return ERROR_MM;
			}
			if (false == SDL_RenderFillRect(renderer, &qt_rect)){
				fprintf(logfp, "SDL_RenderFillRect() error file game_main.c line %d\n%s\n", __LINE__, SDL_GetError());
				return ERROR_MM;
			}
			if (EXIT_FAILURE == draw_text(logfp, renderer, char_tex, quit_button_text, &qt_rect, BUTTON_FOCUSED_COLOR, TEXT_CENTER)){
				fprintf(logfp, "draw_text() error file game_main.c line %d\n", __LINE__);
				return ERROR_MM;
			}
		}
		else {
			u.hex = BUTTON_FOCUSED_COLOR;
			if (false == SDL_SetRenderDrawColor(renderer, u.v[2], u.v[1], u.v[0], 0xff)){
				fprintf(logfp, "SDL_SetRenderDrawColor() error file game_main.c line %d\n%s\n", __LINE__, SDL_GetError());
				return ERROR_MM;
			}
			if (false == SDL_RenderFillRect(renderer, &qt_rect)){
				fprintf(logfp, "SDL_RenderFillRect() error file game_main.c line %d\n%s\n", __LINE__, SDL_GetError());
				return ERROR_MM;
			}
			if (EXIT_FAILURE == draw_text(logfp, renderer, char_tex, quit_button_text, &qt_rect, BUTTON_UNFOCUSED_COLOR, TEXT_CENTER)){
				fprintf(logfp, "draw_text() error file game_main.c line %d\n", __LINE__);
				return ERROR_MM;
			}
		}
		if (false == SDL_WaitEvent(&event)){
			fprintf(logfp, "SDL_WaitEvent() error file game_main.c line %d\n%s\n", __LINE__, SDL_GetError());
			return ERROR_MM;
		}
		if (SDL_EVENT_MOUSE_MOTION == event.type){
			mp.x = event.motion.x;
			mp.y = event.motion.y;
			if (SDL_PointInRectFloat(&mp, &sp_rect)){
				sp_focus = true;
			}
			else {
				sp_focus = false;
			}
			if (SDL_PointInRectFloat(&mp, &mphost_rect)){
				mphost_focus = true;
			}
			else {
				mphost_focus = false;
			}
			if (SDL_PointInRectFloat(&mp, &mpclient_rect)){
				mpclient_focus = true;
			}
			else {
				mpclient_focus = false;
			}
			if (SDL_PointInRectFloat(&mp, &cr_rect)){
				cr_focus = true;
			}
			else {
				cr_focus = false;
			}
			if (SDL_PointInRectFloat(&mp, &qt_rect)){
				qt_focus = true;
			}
			else {
				qt_focus = false;
			}
		}
		if (SDL_EVENT_MOUSE_BUTTON_DOWN == event.type){
			if (sp_focus){
				r = SINGLEPLAYER_MM;
				break;
			}
			if (mphost_focus){
				r = MULTIPLAYER_HOST_MM;
				break;
			}
			if (mpclient_focus){
				r =  MULTIPLAYER_CLIENT_MM;
				break;
			}
			if (cr_focus){
				r =  CREATOR_MM;
				break;
			}
			if (qt_focus){
				r =  QUIT_MM;
				break;
			}
		}
		if (false == SDL_RenderPresent(renderer)){
			fprintf(logfp, "SDL_RenderPresent() error file game_main.c line %d\n%s\n", __LINE__, SDL_GetError());
			return ERROR_MM;
		}
	}
	SDL_DestroyTexture(sand_tex);
	SDL_DestroyTexture(char_tex);
	return r;
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
	printf("W = %d H = %d\n", display_mode->w, display_mode->h);
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
	if (ERROR_MM == rc){
		fprintf(logfp, "main_menu() error in file game_main.c line %d\n", __LINE__);
		fclose(logfp);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return EXIT_FAILURE;
	}
	switch (rc){
		case SINGLEPLAYER_MM:
			break;
		case MULTIPLAYER_HOST_MM:
			break;
		case MULTIPLAYER_CLIENT_MM:
			break;
		case CREATOR_MM:
	}
	fclose(logfp);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return EXIT_SUCCESS;
}