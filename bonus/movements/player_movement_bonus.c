/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arekoune <arekoune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 12:07:52 by haouky            #+#    #+#             */
/*   Updated: 2025/02/05 11:17:39 by arekoune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D_bonus.h"

int	get_a(t_map *map, double y, double x, char c)
{
	if (map->map_content[(int)(map->player.cord[0] + y) / TAILE_SIZE]
		[(int)(map->player.cord[1] + x) / TAILE_SIZE] == c)
		return (1);
	return (0);
}

int	check_wall(t_map *map, double *op, int sig)
{
	if ((get_a (map, (op[1] * sig) - (PLAYER_SIZE / 2), 
				(op[0] * sig) + (PLAYER_SIZE / 2), '1') 
			|| get_a(map, (op[1] * sig) + (PLAYER_SIZE / 2), 
				(op[0] * sig) + (PLAYER_SIZE / 2), '1')
			|| get_a(map, (op[1] * sig) + (PLAYER_SIZE / 2), 
				(op[0] * sig) - (PLAYER_SIZE / 2), '1')
			|| get_a(map, (op[1] * sig) - (PLAYER_SIZE / 2), 
				(op[0] * sig) - (PLAYER_SIZE / 2), '1'))
		|| ((get_a(map, (op[1] * sig) - (PLAYER_SIZE / 2), 
					(op[0] * sig) - (PLAYER_SIZE / 2), 'D')
				|| get_a(map, (op[1] * sig) + (PLAYER_SIZE / 2), 
					(op[0] * sig) - (PLAYER_SIZE / 2), 'D')
				|| get_a(map, (op[1] * sig) - (PLAYER_SIZE / 2), 
					(op[0] * sig) + (PLAYER_SIZE / 2), 'D')
				|| get_a(map, (op[1] * sig) + (PLAYER_SIZE / 2), 
					(op[0] * sig) + (PLAYER_SIZE / 2), 'D')) 
			&& (map->door.scop < 90 && !get_a(map, 0, 0, 'D'))))
		return (0);
	return (1);
}

void	control_page(t_map *map)
{
	if (map->control.enable)
	{
		map->control.enable = false;
		map->control.img->enabled = true;
	}
	else
	{
		mlx_get_mouse_pos(map->mlx, &map->player.mouse_x, &map->player.mouse);
		map->player.mouse = map->player.mouse_x;
		map->control.enable = true;
		map->control.img->enabled = false;
	}
}

void	show_control(mlx_key_data_t key, void *param)
{
	t_map	*map;

	map = param;
	if (key.key == MLX_KEY_TAB && key.action)
		control_page(map);
	else if (key.key == MLX_KEY_ESCAPE && key.action)
		exit(ft_write("Game Over !!\n", 0));
	else if (key.key == MLX_KEY_M && key.action)
	{
		map->player.mouseactive *= -1;
		mlx_get_mouse_pos(map->mlx, &map->player.mouse_x, &map->player.mouse);
		map->player.mouse = map->player.mouse_x;
	}
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
