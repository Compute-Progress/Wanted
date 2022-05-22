#include "../includes/wanted.h"

int main()
{
    SDLX_Display    *display;
    master          *game_master;

    SDLX_Start(
        WINDOW_NAME,
        WINDOW_X,
        WINDOW_Y,
        WINDOW_H,
        WINDOW_W,
        0
    );
    display = SDLX_Display_Get();
    game_master = game_init();

    while(game_master->state)
    {
        SDLX_Render_Reset(display);
        SDLX_RenderQueue_FlushAll();
        SDLX_InputLoop();
        SDLX_Input_Update();
        SDLX_TimedLoop(game_loop, game_master);
        SDLX_RenderAll(display);
        SDL_RenderPresent(display->renderer);
        SDLX_CapFPS();
    }
}