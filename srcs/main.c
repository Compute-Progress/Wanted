#include "../includes/wanted.h"

typedef int (*loops)(void *);

int main()
{
    SDLX_Display    *display;
    master          *game_master;
    loops           gameLoops[4] = {
        start_loop,
        game_loop,
        end_loop,
        transition_screen,
    };

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

    while(game_master->state >= 0)
    {
        SDLX_Render_Reset(display);
        SDLX_RenderQueue_FlushAll();
        SDLX_InputLoop();
        SDLX_Input_Update();
        SDLX_TimedLoop(gameLoops[game_master->state], game_master);
        SDLX_RenderAll(display);
        SDL_RenderPresent(display->renderer);
        SDLX_CapFPS();
    }
}