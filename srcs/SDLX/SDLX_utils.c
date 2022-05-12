#include "SDLX/SDLX.h"


void		SDLX_Sprite_Create(SDLX_Sprite *dest, uint32_t layer, SDL_Texture *texture)
{
	if (dest == NULL)
		return ;
	dest->texture = texture;
	dest->primary_Layer = layer;
	dest->src = &(dest->_src);
	dest->dst = &(dest->_dst);
	dest->angle = 0;
	dest->center = NULL;
	dest->flip = SDL_FLIP_NONE;
}

SDL_Texture	*SDLX_Texture_Load(char *path, SDLX_Display *display)
{
	return 	SDL_CreateTextureFromSurface(display->renderer, IMG_Load(path));
}