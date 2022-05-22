#ifndef SDLX_MACRO
# define SDLX_MACRO

# define DEFAULT_QUEUES_COUNT 2
# define DEFAULT_QUEUE_SIZE 5
# define FPS 60
# define FRAME_TIME 1000 / FPS
# define UPDATE_LEN_MS 10
# define MAX_UPDATE_PER_FRAME 30

# ifndef MAX
#  define MAX(a, b)\
	({ 	__typeof__ (a) _a = (a);\
		__typeof__ (b) _b = (b);\
		(_a > _b) ? (a) : (b);})\

# endif

# ifndef MIN
#  define MIN(a, b)			\
({ 	__typeof__ (a) _a = (a);\
	__typeof__ (b) _b = (b);\
	(_a < _b) ? (a) : (b);})\

# endif

#endif
