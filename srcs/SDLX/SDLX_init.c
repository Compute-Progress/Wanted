#include "SDLX/SDLX.h"

static SDLX_Display display;

void	SDLX_Close(void)
{
	SDL_DestroyWindow(display.window);
	SDL_Quit();
}

void 			SDLX_Background_Set(SDL_Texture *bg) {display.background = bg;}

static void		SDLX_Display_Set(char *name, int x, int y, int h, int w, int flags)
{
    SDL_Window *window;

	window = SDL_CreateWindow(
        name,
        x, y,
        w, h,
        flags
	);
    display.window = window;
    display.renderer = SDL_CreateRenderer(display.window, -1, 0);
    SDLX_RenderQueues_Init();
}

void	        SDLX_Start(char *name, int x, int y, int h, int w, int flags)
{
	if (!SDL_WasInit(0))
		SDL_Init(SDL_INIT_EVERYTHING);
	SDLX_Display_Set(name, x, y, h, w, flags);
    SDL_Log("AT START %p %p", display.window, display.renderer);
	atexit(SDLX_Close);
}

SDLX_Display	*SDLX_Display_Get(void) 
{
    if (!display.renderer)
        return NULL;

    return &display;
}
