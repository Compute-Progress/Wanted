#ifndef SDLX_STRUCT_H
# define SDLX_STRUCT_H

#include "SDL2/SDL.h"

typedef struct SDLX_Display
{
    SDL_Window      *window;
    SDL_Renderer    *renderer;
    SDL_Texture     *background;
}   SDLX_Display;

#endif