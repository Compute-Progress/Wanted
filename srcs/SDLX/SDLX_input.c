#include "SDLX/SDLX_input.h"

static SDLX_Input _intern_input;

void SDLX_InputLoop(void)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			exit(0);
	}
}

void SDLX_Input_Update()
{
	_intern_input.mouse_state = SDL_GetMouseState(&_intern_input.mouse.x, &_intern_input.mouse.y);
}

SDLX_Input SDLX_Input_Get() { return _intern_input; }