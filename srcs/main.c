#include "../includes/wanted.h"

int main()
{
    SDLX_Display *display;

    SDLX_Start(
        WINDOW_NAME,
        WINDOW_X,
        WINDOW_Y,
        WINDOW_H,
        WINDOW_W,
        0
    );

    display = SDLX_Display_Get();

    (void)display;
    while(1)
    {
        SDLX_InputLoop();
    }
}