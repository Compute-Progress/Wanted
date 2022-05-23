NAME = wanted

DEBUG_FLAGS = -fsanitize=address -g
FLAGS = 
INCLUDES = -I includes/ -I includes/SDL2/ -I includes/SDLX/

LIB_DIR = libs/
LIBRARIES= -l SDL2 -l SDL2_image -l SDL2_ttf -lm
# LIBRARIES = $(LIB_DIR)libSDL2.dylib $(LIB_DIR)libSDL2_image.dylib $(LIB_DIR)libSDL2_ttf.dylib
STATIC_LIB = 

SDLX_DIR = SDLX/
SRCS_DIR = srcs/

BIN_DIR = bin/

SDLX_NAMES =		\
		SDLX_debug	\
		SDLX_init	\
		SDLX_input	\
		SDLX_render	\
		SDLX_utils	\

SRC_FILES =			\
	$(addprefix $(SDLX_DIR), $(SDLX_NAMES))\
	game			\
	inits			\
	main			\
	movement		\
	placement		\

SRCS = $(addprefix $(SRCS_DIR),$(addsuffix .c, $(SRC_FILES)))

OBJS = $(addprefix $(BIN_DIR), $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(BIN_DIR) $(OBJS)
	gcc $(FLAGS) $(INCLUDES) -o $(NAME) $(OBJS) $(LIBRARIES) $(DEBUG_FLAGS)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(BIN_DIR)%.o: %.c
	mkdir -p $(BIN_DIR)$(dir $<)
	gcc $(FLAGS) $(INCLUDES) -c $< -o $@

run: re clean
	./$(NAME)

clean:
	rm -rf $(BIN_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all