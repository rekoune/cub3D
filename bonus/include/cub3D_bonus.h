/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arekoune <arekoune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:49:27 by haouky            #+#    #+#             */
/*   Updated: 2025/02/05 11:00:35 by arekoune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "../../MLX42/include/MLX42/MLX42.h"
# include "get_next_line_bonus.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WI_HEIGHT 1000
# define WI_WIDTH 1500.0
# define MINI_HEIGHT 200
# define MINI_WIDTH 400
# define TAILE_SIZE 32
# define PLAYER_SIZE 4
# define ESPC 12
# define WALL_HEIGHT 32
# define PLAYER_VIEW 60.0
# define REC_WITH 1
# define M_S 4
# define DG 2
# define M_SEN 0.05

# define STANDING 0
# define RUNNING 1
# define SHOTTING 2
# define RELOADING 3

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

typedef struct s_mini_img
{
	mlx_image_t			*wall;
	mlx_image_t			*flor;
	mlx_image_t			*player;
	mlx_image_t			*cover;
	mlx_image_t			*right;
	mlx_image_t			*buttom;
	mlx_image_t			*door;
}						t_mini_img;

typedef struct s_win_img
{
	mlx_image_t			*win_img;
	mlx_image_t			*background;
	mlx_image_t			*door_cover;
	mlx_image_t			*north;
	mlx_image_t			*south;
	mlx_image_t			*west;
	mlx_image_t			*east;
	mlx_image_t			*door;
	int					**px_north;
	int					**px_south;
	int					**px_west;
	int					**px_east;
	int					**px_door;
}						t_win_img;

typedef struct s_player
{
	double				cord[2];
	double				angel;
	double				next_p_cord[2];
	int					mouse;
	int					mouse_x;
	int					mouseactive;
}						t_player;

typedef struct s_ray
{
	double				hit_x;
	double				hit_y;
	int					dir;
	char				hit_line;
}						t_ray;

typedef struct s_door
{
	double				hit_cord[2];
	double				door_height;
	char				hit_line;
	int					timer;
	double				scop;
	double				scop_size;
	bool				timer_flag;
	bool				close_door;
	bool				open_door;
}						t_door;

typedef struct s_animation
{
	mlx_image_t			**standing;
	mlx_image_t			**running;
	mlx_image_t			**shotting;
	mlx_image_t			**reloading;
	mlx_image_t			*amo_img;
	int					flag;
	int					timer;
	int					shott_num;
}						t_animation;

typedef struct s_control{
	mlx_image_t			*img;
	bool				enable;
	int					timer;
}	t_control;

typedef struct s_map
{
	t_directions		directions;
	t_colors			colors;
	t_mini_img			mini_img;
	t_player			player;
	mlx_t				*mlx;
	t_win_img			win_img;
	t_ray				ray;
	t_door				door;
	t_animation			animation;
	t_control			control;
	char				**map_content;
	int					map_max_size[2];
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

t_map					*checking_map(char *map_file);
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
void					map_max_sz(char **map, int *size);
void					draw_line(mlx_image_t *img, double *start, double *end,
							int color);
double					distance(double *start, double *end);
double					normalize_angel(double angel);
void					set_derction(double angel, int *der);
int						valid_point(double *hitp, char **map, int *size);
char					**ft_split(char *s, char c);
void					add_back(t_map_lst **head, t_map_lst *new_node);
t_map_lst				*new_node(char *str);
int						ft_lstsize(t_map_lst *lst);
int						check_map_file(char *str);
bool					is_empty(char *str);
bool					is_last(t_map *map);
enum e_type				get_info_type(char *line, char **info);
void					map_validation(char **map, int size, char p);
char					**getarray(t_map_lst *lst);
int						map_size(t_map_lst *map);
char					valid_element(char **map);
void					draw_mini_map(mlx_t *mlx, t_map *map);
void					move_imgs_inst(mlx_image_t *img, char dir, int px_num);
int						create_trgb(int r, int g, int b, int a);
double					distance(double *start, double *end);
void					draw_3d(t_map *map, double dis_to_wall, double p);
void					draw_img(mlx_image_t *img, int height, int width,
							int color);
void					caster(t_map *map);
mlx_image_t				*get_image(t_map *map, mlx_t *mlx, char *path);
int						**get_2d_pixels(mlx_image_t *img);

void					animation(t_map *map);
void					animation_init(t_map *map);
void					draw_amo(t_map *map, int shott_num);
void					move_player(void *arg);
int						check_wall(t_map *map, double *op, int sig);
void					animation_frames(t_map *map);
char					*get_digit(long nb);
void					horizontal_hit(double *hitp,
							int *der, t_player player, double angel);
void					victical_hit(double *hitp,
							int *der, t_player player, double angel);
void					add_animation_img(t_map *map);
mlx_image_t				**get_textures(t_map *map, char *path, int size);
void					disable_all_images(t_map *map);
void					door_status(t_map *map, double dest, double ray_angle,
							double *start);
double					get_x_image(double hit_x, double hit_y, char flag);
void					mv_img(mlx_image_t *img, int y, int x);
void					find_palayer_cord(t_player *player, char **map);
void					move_img_x(t_map *map);
void					move_img_y(t_map *map);
void					control_page(t_map *map);
void					show_control(mlx_key_data_t key, void *param);

#endif