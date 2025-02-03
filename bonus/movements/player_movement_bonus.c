/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haouky <haouky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 12:07:52 by haouky            #+#    #+#             */
/*   Updated: 2025/02/03 12:52:12 by haouky           ###   ########.fr       */
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
		map->control.enable = true;
		map->control.img->enabled = false;
	}
}
