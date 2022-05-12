#ifndef SDLX_H
# define SDLX_H
# include "SDLX_input.h"
# include "SDLX_macro.h"
# include "SDLX_structs.h"

/** 
 * Standard SDLX lib functions
 */

SDLX_Display	*SDLX_Display_Get(void);
void	        SDLX_Background_Set(SDL_Texture *bg);
void	        SDLX_Start(char *name, int x, int y, int h, int w, int flags);

/**
 * SDLX renderer functions and render queues functions
 */
void 		SDLX_RenderAll();
void 		SDLX_RenderOne(uint32_t id);
void        SDLX_Render_Reset();

void		SDLX_RenderQueue_Push(SDLX_Sprite *sprite);
void        SDLX_RenderQueue_Flush(uint32_t id);
uint32_t    SDLX_RenderQueue_Create(SDL_bool isSorted);

SDLX_RenderQueue	*SDLX_RenderQueue_Get(uint32_t id);

/**
 * SDLX sprite functions
 */

void		SDLX_Sprite_Create(SDLX_Sprite *dest, uint32_t layer, SDL_Texture *texture);

#endif