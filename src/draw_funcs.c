#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <SDL.h>
#include <tank_game.h>

int draw_tiled_background(FILE *logfp, SDL_Renderer *renderer, SDL_Texture *tex, const int window_width, const int window_height, const int texture_width, const int texture_height){
	SDL_FRect rect;
	rect.w = (float)texture_width;
	rect.h = (float)texture_height;
	rect.y = 0.0f;
	while (rect.y <= (float)window_height){
		rect.x = 0.0f;
		while (rect.x <= (float)window_width){
			if (false == SDL_RenderTexture(renderer, tex, NULL, &rect)){
				fprintf(logfp, "SDL_RenderTexture() error file draw_funcs.c line %d\n%s\n", __LINE__, SDL_GetError());
				return EXIT_FAILURE;
			}
			rect.x += rect.w;
		}
		rect.y += rect.h;
	}
	return EXIT_SUCCESS;
}


int draw_text(FILE *logfp, SDL_Renderer *renderer, SDL_Texture *char_tex, const char *str, const SDL_FRect *space, const int color, const int alignment){
	SDL_FRect dst, src;
	int slen, cs, r, c, i;
	union rgb u;

	slen = strlen(str);
	if ((slen * ((int)space->h)) <= (int)space->w){
		cs = (int)space->h;
	}
	else {
		cs = ((int)space->w) / slen;
	}
	slen = cs * slen;
	dst.y = space->y + (float)(((int)space->h - cs) / 2);
	dst.w = (float)cs;
	dst.h = (float)cs;
	src.w = (float)CHAR_W;
	src.h = (float)CHAR_H;
	switch (alignment){
		case TEXT_CENTER:
			dst.x = space->x + (float)(((int)space->w - slen) / 2);
			break;
		case TEXT_LEFT:
			dst.x = space->x;
			break;
		case TEXT_RIGHT:
			dst.x = space->x + (float)((int)space->w - slen);
			break;
		case TEXT_CENTER_TRANSL:
			dst.x = space->x + (float)(((int)space->w - slen) / 2);
	}
	u.hex = color;
	if (false == SDL_SetTextureColorMod(char_tex, u.v[2], u.v[1], u.v[0])){
		fprintf(logfp, "SDL_SetTextureColorMod() error file draw_funcs.c line %d\n%s\n", __LINE__, SDL_GetError());
		return EXIT_FAILURE;
	}
	for (i = 0; str[i]; ++i){
		r = str[i] / NUM_CHAR;
		c = str[i] % NUM_CHAR;
		src.x = (float)(c * CHAR_W);
		src.y = (float)(r * CHAR_H);
		if (false == SDL_RenderTexture(renderer, char_tex, &src, &dst)){
			fprintf(logfp, "SDL_RenderTexture() error file draw_funcs.c line %d\n%s\n", __LINE__, SDL_GetError());
			return EXIT_FAILURE;
		}
		dst.x += dst.w;
	}
	if (false == SDL_SetTextureColorMod(char_tex, 0xff, 0xff, 0xff)){
		fprintf(logfp, "SDL_SetTextureColorMod() error file draw_funcs.c line %d\n%s\n", __LINE__, SDL_GetError());
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}