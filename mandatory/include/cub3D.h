/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arekoune <arekoune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:08:39 by haouky            #+#    #+#             */
/*   Updated: 2025/02/03 12:18:31 by arekoune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "../inlcude/get_next_line.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WI_HEIGHT 1000
# define WI_WIDTH 1500.0
# define TAILE_SIZE 32
# define PLAYER_SIZE 4
# define WALL_HEIGHT 32
# define PLAYER_VIEW 60.0
# define REC_WITH 1.0
# define M_S 4
# define DG 2
# define M_SEN 0.05

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

typedef struct s_win_img
{
	mlx_image_t			*win_img;
	mlx_image_t			*background;
	mlx_image_t			*north;
	mlx_image_t			*south;
	mlx_image_t			*west;
	mlx_image_t			*east;
	int					**px_north;
	int					**px_south;
	int					**px_west;
	int					**px_east;
}						t_win_img;

typedef struct s_player
{
	double				cord[2];
	double				angel;
	double				next_p_cord[2];
}						t_player;

typedef struct s_ray
{
	double				hit_x;
	double				hit_y;
	int					dir;
	char				hit_line;
}						t_ray;

typedef struct s_map
{
	t_directions		directions;
	t_colors			colors;
	t_player			player;
	mlx_t				*mlx;
	t_win_img			win_img;
	t_ray				ray;
	char				**map_content;
	int					map_max_size[2];
	int					color_test;
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

// move_p.c
void					move_player(void *arg);

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

//utils3.c
double					*get_point(double *hitph, double *hitpv, t_map *map);

//utils2.c
void					map_max_sz(char **map, int *size);
void					draw_line(mlx_image_t *img, double *start, double *end,
							int color);
double					distance(double *start, double *end);
double					normalize_angel(double angel);
void					set_derction(double angel, int *der);
int						valid_point(double *hitp, char **map, int *size);
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
enum e_type				get_info_type(char *line, char **info);
enum e_type				get_identifier(char *identifier);

//check_map_content.c
void					map_validation(char **map, int size, char p);
char					**getarray(t_map_lst *lst);
int						map_size(t_map_lst *map);
char					valid_element(char **map);

//mini_map.c
void					draw_mini_map(mlx_t *mlx, t_map *map);
void					move_imgs_inst(mlx_image_t *img, char dir, int px_num);
int						create_trgb(int r, int g, int b, int a);
double					distance(double *start, double *end);
void					draw_rectangle(mlx_image_t *img, double *start,
							double height, int color);
void					draw_3d(t_map *map, double dis_to_wall, int color,
							double p);
void					draw_img(mlx_image_t *img, int height, int width,
							int color);
void					draw_background(mlx_image_t *img, double *height_width,
							double *start, int color);
//raycast
void					caster(t_map *map);
mlx_image_t				*get_image(t_map *map, mlx_t *mlx, char *path);
int						**get_2d_pixels(mlx_image_t *img);

#endif