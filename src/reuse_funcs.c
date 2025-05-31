#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <SDL.h>

/* This enum provides the flag values that can be provided to draw_text() */
enum {TEXT_CENTER, TEXT_LEFT, TEXT_RIGHT, TEXT_CENTER_TRANSL};


/*
The function below draws a tiled texture on window.
Arguments: Log file pointer, renderer pointer, texture pointer, window width px, window height px,
image width px, height height px
*/

int draw_bg(FILE *logfp, SDL_Renderer *renderer, SDL_Texture *tex, const int ww, const int wh, const int tw, const int th){
	SDL_FRect rect;
/*
	SDL_FRect src;
	int rw, rh;
*/
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
/*
	So the code below is just my mistake.
	But I learned that if I give SDL_RenderTexture() a destination SDL_FRect
	that falls outside the actual window then it works fine without errors.
	And also the loop above was not my intention, I was trying to print the
	tiled texture as many times on the screen as it can fit completely.
	Oh well, it worked out fine. Good thing I decided to test my code.
*/
/*
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
*/
	return EXIT_SUCCESS;
}


/*
The function below prints text.
Given an SDL_FRect representing the space for text to be drawnn,
this functions prints the string in maximum height possible.
Alignment and color of text can also be specified.
*/
int draw_text(FILE *logfp, SDL_Renderer *renderer, SDL_Texture *char_tex, char *str, SDL_FRect *space, const int color, const int alg){
	SDL_FRect dst, src;
	int slen, cs;

	slen = strlen(str);
	if ((slen * ((int)space->h) <= (int)space->w){
		cs = (int)space->h;
	}
	else {
		cs = ((int)space->w) / slen;
	}
	switch (alg){
		case TEXT_CENTER:
		case TEXT_LEFT:
		case TEXT_RIGHT:
		case TEXT_CENTER_TRANSL:
	}
}