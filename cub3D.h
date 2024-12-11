#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42/include/MLX42/MLX42.h"
# include "get_next_line.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>

# define WI_HEIGHT  1000
# define WI_WIDTH  1500
# define MINI_HEIGHT  150
# define MINI_WIDTH  300
# define TAILE_SIZE 20
# define PLAYER_SIZE 5
# define M_S 3
# define DG 3
typedef struct s_directions
{
	char				*north;
	char				*south;
	char				*west;
	char				*east;
}						t_directions;

typedef struct s_colors
{
	int					floor[3];
	int					ceiling[3];
}						t_colors;

typedef struct s_map_lst
{
	char				*content;
	struct s_map_lst	*next;
}						t_map_lst;

typedef struct s_mini_img{
	mlx_image_t		*wall;
	mlx_image_t		*flor;
	mlx_image_t		*player;
	mlx_image_t		*cover;
	
}	t_mini_img;

typedef struct s_player{
	double	x;
	double	y;
	int		angel;
	double	next_p_cord[2];
}	t_player;

typedef struct s_map
{
	t_directions		directions;
	t_colors			colors;
	t_mini_img			mini_img;
	t_player			player2;
	mlx_t				*mlx;
	char				**map_content;
}						t_map;

enum					e_type
{
	SO,
	NO,
	WE,
	EA,
	F,
	C,
};

//checking_map.c
t_map					*checking_map(char *map_file);

//utils.c
bool					str_comp(char *s1, char *s2);
int						str_len(char *str, char c);
int						ft_write(char *str, int rtrn);
char					*str_dup(char *str, int start, int size);
char					*str_join(char *s1, char *s2);
int						str_count(char **str);
long					ft_atoi(char *str);
void					free_2d(char **str, char *str2);
void					free_resources(t_map *map);
void					free_list(t_map_lst *map);

//ft_split.c
char					**ft_split(char *s, char c);

//linked_list.c
void					add_back(t_map_lst **head, t_map_lst *new_node);
t_map_lst				*new_node(char *str);
int						ft_lstsize(t_map_lst *lst);

//check_map_utils.c
int						check_map_file(char *str);
bool					is_empty(char *str);
bool					is_last(t_map *map);
void					is_last_line(int map_fd);
enum e_type				get_info_type(char *line, char **info);

//check_map_content.c
void					map_validation(char **map, int size, char p);
char					**getarray(t_map_lst *lst);
int						map_size(t_map_lst *map);
char 					valid_element(char **map);

//mini_map.c
void					draw_mini_map(mlx_t *mlx, t_map *map);
void					move_imgs_inst(mlx_image_t *img, char dir, int	px_num);
int						create_trgb(int r, int g, int b, int a);

#endif