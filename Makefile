CC = cc
FLAGS = -Wall -Werror -Wextra #-O3
SANITAZE = #-g -fsanitize=address

SRC = mandatory/cub3D.c mandatory/utils/utils3.c mandatory/ray_texturing/move_p.c mandatory/utils/utils2.c mandatory/ray_texturing/raycast.c\
 mandatory/map_parcing/checking_map.c mandatory/utils/utils.c mandatory/GNL/get_next_line.c mandatory/GNL/get_next_line_utils.c\
  mandatory/utils/ft_split.c mandatory/utils/linked_list.c mandatory/map_parcing/check_map_utils.c mandatory/utils/cleaning.c \
  mandatory/map_parcing/check_map_content.c mandatory/ray_texturing/mini_map.c mandatory/ray_texturing/draw_3d.c

BOSRC = bonus/cub3D_bonus.c bonus/utils/utils2_bonus.c bonus/raycasting/raycast_bonus.c bonus/map_parcing/checking_map_bonus.c \
bonus/utils/utils_bonus.c bonus/GNL/get_next_line_bonus.c bonus/GNL/get_next_line_utils_bonus.c bonus/utils/ft_split_bonus.c \
bonus/utils/linked_list_bonus.c bonus/map_parcing/check_map_utils_bonus.c bonus/utils/cleaning_bonus.c bonus/map_parcing/check_map_content_bonus.c\
bonus/texturing/mini_map_bonus.c bonus/texturing/draw_3d_bonus.c bonus/animation/animation.c bonus/movements/move_player.c bonus/animation/animation_img_ctl.c\
bonus/texturing/rendering_doors.c bonus/texturing/mini_map_utils_bonus.c bonus/raycasting/raycast_help.c bonus/movements/player_movement_bonus.c

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