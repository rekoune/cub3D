CC = cc
FLAGS = -Wall -Werror -Wextra

SRC = cub3D.c
OBJ = $(SRC:.c=.o)

NAME = cub3D
MLX_LIB_PATH = ./MLX42/build
GLFW_LIB_PATH = /Users/arekoune/.brew/lib
MLX_LIB = -L$(MLX_LIB_PATH) -lMLX42
GLFW_LIB = -L$(GLFW_LIB_PATH) -lglfw

all: libmlx $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) $(MLX_LIB) $(GLFW_LIB) -framework OpenGL -framework AppKit -o $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -I$(MLX_LIB_PATH) -c $< -o $@

libmlx:
	@cmake MLX42 -B $(MLX_LIB_PATH) && make -C $(MLX_LIB_PATH) -j4

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all