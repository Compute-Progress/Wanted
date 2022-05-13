#include "SDLX/SDLX.h"

static SDLX_Time _intern_time;

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

int SDLX_TimedLoop(int (*game_loop)(void *), void *args)
{

	Uint32 	current;
	int		i;

	static double consumable;

	current = SDL_GetTicks();
	_intern_time.last_frame = current;
	consumable += current - _intern_time.last_frame;
	_intern_time.delta_time /= UPDATE_LEN_MS;
	i = 0;
	while (consumable > 0 && i < MAX_UPDATE_PER_FRAME)
	{
		// Maybe a preferable approach would be to time the length of the update
		// and either :
		//			- Average it and use an N update / sec
		//			- Deduct it from consumbale, set it as delta time
		_intern_time.delta_time = MIN(consumable, UPDATE_LEN_MS);
		game_loop(args);
		consumable -= UPDATE_LEN_MS;
		++i;
	}

	return i;
}

void SDLX_CapFPS()
{
	static Uint32 start;
	int delay;

	if (!start)
		start = SDL_GetTicks();
	delay = start - SDL_GetTicks();
	delay = MAX(FRAME_TIME - delay , 0);
	SDL_Delay(delay);
	start = SDL_GetTicks();
}