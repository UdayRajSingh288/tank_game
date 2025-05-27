#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL.h>

/* This function draws a tiled texture on window */
int draw_bg(FILE *logfp, SDL_Renderer *renderer, SDL_Texture *tex, const int ww, const int wh, const int tw, const int th){
	SDL_FRect rect, src;
	int rw, rh;

	rect.w = (float)tw;
	rect.h = (float)th;
	rect.y = 0.0f;

	while (rect.y <= (float)wh){
		rect.x = 0.0f;
		while (rect.x <= (float)ww){
			if (false == SDL_RenderTexture(renderer, tex, NULL, &rect)){
				fprintf(logfp, "SDL_RenderTexture() error file reuse_funcs.c line %d\n%s\n", __LINE__, SDL_GetError());
				return EXIT_FAILURE;
			}
			rect.x += rect.w;
		}
		rect.y += rect.h;
	}
	rw = ww % tw;
	if (rw){
		rect.w = (float)rw;
		rect.h = (float)th;
		rect.y = 0.0f;
		rect.x = (float)((ww / tw) * tw);
		src.x = 0.0f;
		src.y = 0.0f;
		src.h = (float)th;
		src.w = (float)rw;
		while (rect.y <= (float)wh){
			if (false == SDL_RenderTexture(renderer, tex, &src, &rect)){
				fprintf(logfp, "SDL_RenderTexture() error file reuse_funcs.c line %d\n%s\n", __LINE__, SDL_GetError());
				return EXIT_FAILURE;
			}
			rect.y += rect.h;
		}
	}
	rh = wh % th;
	if (rh){
		rect.w = (float)tw;
		rect.h = (float)rh;
		rect.y = (float)((wh / th) * th);
		src.w = (float)tw;
		src.h = (float)rh;
		src.x = 0.0f;
		src.y = 0.0f;
		while (rect.x <= (float)ww){
			if (false == SDL_RenderTexture(renderer, tex, &src, &rect)){
				fprintf(logfp, "SDL_RenderTexture() error file reuse_funcs.c line %d\n%s\n", __LINE__, SDL_GetError());
				return EXIT_FAILURE;
			}
			rect.x += rect.w;
		}
	}
	if (rw && rh){
		rect.x = (float)((ww / tw) * tw);
		rect.y = (float)((wh / th) * th);
		rect.w = (float)rw;
		rect.h = (float)rh;
		src.x = 0.0f;
		src.y = 0.0f;
		src.w = (float)rw;
		src.h = (float)rh;
		if (false == SDL_RenderTexture(renderer, tex, &src, &rect)){
			fprintf(logfp, "SDL_RenderTexture() error file reuse_funcs.c line %d\n%s\n", __LINE__, SDL_GetError());
			return EXIT_FAILURE;
		}
	}
	return EXIT_SUCCESS;
}