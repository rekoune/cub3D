/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arekoune <arekoune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:40:04 by arekoune          #+#    #+#             */
/*   Updated: 2025/02/03 12:08:40 by arekoune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3D_bonus.h"

void	leaks(void)
{
	system("leaks -q cub3D_bonus");
}

void	draw_line(mlx_image_t *img, double *start, double *end, int color)
{
	int		dy;
	int		dx;
	int		steps;
	float	x_inc;
	float	y_inc;
	int		i;
	float	y;
	float	x;

	dy = end[0] - start[0];
	dx = end[1] - start[1];
	steps = 0;
	x_inc = 0;
	y_inc = 0;
	i = 0;
	y = start[0];
	x = start[1];
	if (abs(dx) > abs(dy))
		steps = abs(dx);
	else
		steps = abs(dy);
	x_inc = (float)dx / (float)steps;
	y_inc = (float)dy / (float)steps;
	while (i < steps && y >= 0 && y < MINI_HEIGHT && x >= 0 && x < MINI_WIDTH)
	{
		mlx_put_pixel(img, round(x), round(y), color);
		x += x_inc;
		y += y_inc;
		i++;
	}
}

double	distance(double *start, double *end)
{
	double	distance;
	double	dx;
	double	dy;

	dy = end[0] - start[0];
	dx = end[1] - start[1];
	distance = sqrt(pow(dx, 2) + pow(dy, 2));
	return (distance);
}

void	animation_frames(t_map *map)
{
	if (mlx_is_key_down(map->mlx, MLX_KEY_RIGHT_CONTROL) 
		|| mlx_is_key_down(map->mlx, MLX_KEY_LEFT_CONTROL) 
		|| mlx_is_mouse_down(map->mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		if (map->animation.shott_num != 0 && (map->animation.flag == STANDING
				|| map->animation.flag == RUNNING))
		{
			map->animation.flag = SHOTTING;
			draw_amo(map, map->animation.shott_num);
		}
	}
	if (mlx_is_key_down(map->mlx, MLX_KEY_R))
	{
		map->animation.flag = RELOADING;
		map->animation.shott_num = 8;
		draw_amo(map, map->animation.shott_num);
	}
	if (map->animation.shott_num == 0)
	{
		map->animation.flag = RELOADING;
		map->animation.shott_num = 8;
		draw_amo(map, map->animation.shott_num);
	}
}

void show_control (mlx_key_data_t key,  void *param)
{
	t_map *map;

	map = param;
	if (key.key == MLX_KEY_TAB && key.action)
		control_page(map);
	else if	(key.key == MLX_KEY_M && key.action)
		map->player.mouseactive *= -1;
	
}

int	main(int ac, char **av)
{
	t_map	*map;

	// atexit(leaks);
	if (ac != 2)
		return (printf("ERROR : Invalid arguments\n"), 1);
	map = checking_map(av[1]);
	map->win_img.door = NULL;
	map->mlx = mlx_init(WI_WIDTH, WI_HEIGHT, "cub3D", false);
	draw_mini_map(map->mlx, map);
	map->player.cord[1] = map->player.cord[1] * TAILE_SIZE + (TAILE_SIZE / 2)
		+ (PLAYER_SIZE / 2);
	map->player.cord[0] = map->player.cord[0] * TAILE_SIZE + (TAILE_SIZE / 2)
		+ (PLAYER_SIZE / 2);
	map_max_sz(map->map_content, map->map_max_size);
	map->player.mouseactive = 1;
	map->door.scop = 0;
	map->door.scop_size = 0.1;
	map->door.timer_flag = false;
	map->door.close_door = false;
	map->door.open_door = true;
	map->door.timer = 0;
	mlx_loop_hook(map->mlx, &move_player, map);
	mlx_key_hook(map->mlx, &show_control, map);
	mlx_loop(map->mlx);
	mlx_set_mouse_pos(map->mlx, (WI_WIDTH / 2), (WI_HEIGHT / 2));
	free_resources(map);
}
