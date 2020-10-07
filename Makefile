NAME = fdf
FLAGS = -g -std=c++11# -Wall -Wextra -Werror
CC = clang++

INCLUDES = -I./include -I./libsdl/includes

HEADERS_DIRECTORY = include/
HEADERS_LIST =
HEADERS = $(wildcard include/*.h*)
DIRECTORY =  $(shell pwd)

SRCS_DIRECTORY = ./src/
SRCS_LIST = main.cpp Camera.cpp Transform.cpp Map.cpp

OBJS_DIRECTORY = objects/
OBJS_LIST = $(patsubst %.cpp, %.o, $(SRCS_LIST))
OBJS = $(addprefix $(OBJS_DIRECTORY), $(OBJS_LIST))

LIBRARIES = -lSDL2 -lSDL2_ttf `sdl2-config --cflags --libs`


.PHONY:

all: $(NAME)


$(NAME): $(OBJS) $(HEADERS)
	@$(CC) $(FLAGS)  $(INCLUDES) $(OBJS) ./libsdl/libsdl.a -o $(NAME) $(LIBRARIES)


$(OBJS_DIRECTORY):
	@mkdir -p $(OBJS_DIRECTORY)


$(OBJS_DIRECTORY)%.o : $(SRCS_DIRECTORY)%.cpp $(HEADERS)
	@mkdir -p $(@D)
	@$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@

$(OBJS_DIRECTORY)%.o : %.cpp $(HEADERS)
	@mkdir -p $(@D)
	@$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@
