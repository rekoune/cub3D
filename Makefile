CC = cc
FLAGS = -Wall -Werror -Wextra 
SANITAZE = -g -fsanitize=address

SRC = cub3D.c checking_map.c utils.c get_next_line.c get_next_line_utils.c ft_split.c linked_list.c check_map_utils.c cleaning.c check_map_content.c mini_map.c
OBJ = $(SRC:.c=.o)

NAME = cub3D
MLX_LIB_PATH = ./MLX42/build
GLFW_LIB_PATH = $(shell brew --prefix glfw)/lib
MLX_LIB = -L$(MLX_LIB_PATH) -lMLX42
GLFW_LIB = -L$(GLFW_LIB_PATH) -lglfw

all: libmlx $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) $(MLX_LIB) $(GLFW_LIB) -framework OpenGL -framework AppKit -o $(NAME)

%.o: %.c
	$(CC) $(FLAGS)  -c $< -o $@

libmlx:
	@cmake MLX42 -B $(MLX_LIB_PATH) && make -C $(MLX_LIB_PATH) -j4

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all