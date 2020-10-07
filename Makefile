NAME = fdf

CXX = clang++
FLAGS = -O3 -std=c++11 -Wall -Wextra

HEADERS_DIR = ./include
HEADERS_LIST = Map.hpp Transform.hpp Camera.hpp Point.hpp
HEADERS = $(patsubst %, $(HEADERS_DIR)/%, $(HEADERS_LIST))

SRCS_DIR = ./src
SRCS_LIST = main.cpp Map.cpp Transform.cpp Camera.cpp
SRCS = $(patsubst %, $(SRCS_DIR)/%, $(SRCS_LIST))

OBJS_DIR = ./objects
OBJS_LIST = $(patsubst %.cpp, %.o, $(SRCS_LIST))
OBJS = $(patsubst %, $(OBJS_DIR)/%, $(OBJS_LIST))

LIBSDL_DIR = ./libsdl
LIBS = -lSDL2 -lSDL2_ttf `sdl2-config --cflags --libs`

.PHONY: all

all: $(NAME)

$(NAME): $(OBJS_DIR) $(OBJS)
	$(CXX) $(FLAGS) $(OBJS) ./libsdl/libsdl.a -I./include -I./libsdl/includes -lSDL2_ttf -lSDL2 -o fdf

$(OBJS_DIR)%.o : $(SRCS_DIR)%.cpp $(HEADERS)
	@$(CXX) $(FLAGS) -c $< -o $@

$(OBJS_DIR)%.o : %.cpp $(HEADERS)
	@$(CC) $(FLAGS) -c $< -o $@