CC = cc
FLAGS = -Wall -Werror -Wextra #-O3
SANITAZE = #-g -fsanitize=address

SRC = mandatory/cub3D.c mandatory/utils3.c mandatory/move_p.c mandatory/utils2.c mandatory/raycast.c\
 mandatory/checking_map.c mandatory/utils.c mandatory/get_next_line.c mandatory/get_next_line_utils.c\
  mandatory/ft_split.c mandatory/linked_list.c mandatory/check_map_utils.c mandatory/cleaning.c \
  mandatory/check_map_content.c mandatory/mini_map.c mandatory/draw_3d.c

BOSRC = bonus/cub3D_bonus.c bonus/utils2_bonus.c bonus/raycast_bonus.c bonus/checking_map_bonus.c \
bonus/utils_bonus.c bonus/get_next_line_bonus.c bonus/get_next_line_utils_bonus.c bonus/ft_split_bonus.c \
bonus/linked_list_bonus.c bonus/check_map_utils_bonus.c bonus/cleaning_bonus.c bonus/check_map_content_bonus.c\
bonus/mini_map_bonus.c bonus/draw_3d_bonus.c bonus/animation.c bonus/move_player.c bonus/animation_img_ctl.c\
bonus/rendering_doors.c bonus/mini_map_utils_bonus.c bonus/raycast_help.c bonus/player_movement_bonus.c

OBJ = $(SRC:.c=.o)
BOBJ = $(BOSRC:.c=.o)

NAME = cub3D
BNAME = cub3D_bonus

MLX_LIB_PATH = ./MLX42/build
GLFW_LIB_PATH = $(shell brew --prefix glfw)/lib
MLX_LIB = -L$(MLX_LIB_PATH) -lMLX42
GLFW_LIB = -L$(GLFW_LIB_PATH) -lglfw

all: libmlx $(NAME)
bonus: libmlx $(BNAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(SANITAZE) $(OBJ) $(MLX_LIB) $(GLFW_LIB) -framework OpenGL -framework AppKit -o $(NAME)
$(BNAME): $(BOBJ)
	$(CC) $(FLAGS) $(SANITAZE) $(BOBJ) $(MLX_LIB) $(GLFW_LIB) -framework OpenGL -framework AppKit -o $(BNAME)

%.o: %.c
	$(CC) $(FLAGS)  -c $< -o $@

libmlx:
	@cmake MLX42 -B $(MLX_LIB_PATH) && make -C $(MLX_LIB_PATH) -j4

clean:
	rm -rf $(OBJ) $(BOBJ)

fclean: clean
	rm -rf $(NAME) $(BNAME) $(MLX_LIB_PATH)

re: fclean all