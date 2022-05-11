#ifndef SDLX_H
# define SDLX_H
# include "SDLX_structs.h"
# include "SDLX_input.h"

/** 
 * Standard SDLX lib functions
*/

SDLX_Display	*SDLX_Display_Get(void);
void	        SDLX_Background_Set(SDL_Texture *bg);
void	        SDLX_Start(char *name, int x, int y, int h, int w, int flags);

#endif