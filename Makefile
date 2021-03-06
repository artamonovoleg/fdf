NAME = fdf
FLAGS = -g -std=c++11# -Wall -Wextra -Werror
CC = g++

HEADERS_DIR = include/

SRCS_DIR = src/
SRCS_LIST = main.cpp Camera.cpp Map.cpp Transform.cpp Renderer.cpp Gui.cpp Controller.cpp
SRCS =  $(addprefix $(SRCS_DIR), $(SRCS_LIST))

OBJS_DIR = objects/
OBJS_LIST = $(patsubst %.cpp, %.o, $(SRCS_LIST))
OBJS = $(addprefix $(OBJS_DIR), $(OBJS_LIST))

LIBSDL_DIR = libsdl/
LIBSDL = $(addprefix $(LIBSDL_DIR), libsdl.a)

.PHONY: all clean

all: $(NAME)

$(NAME): $(OBJS_DIR) $(OBJS) $(LIBSDL)
	$(CC) $(FLAGS) $(OBJS) $(LIBSDL) -I.$(HEADERS_DIR) -lSDL2 -lSDL2_ttf -o $(NAME)

$(OBJS_DIR):
	mkdir $(OBJS_DIR)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.cpp
	$(CC) $(FLAGS) -I./$(HEADERS_DIR) -I./$(LIBSDL_DIR)includes -c $< -o $@

$(LIBSDL):
	make -C $(LIBSDL_DIR)

clean:
	rm -rf $(OBJS_DIR) $(LIBSDL) $(NAME)