/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haouky <haouky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 12:07:52 by haouky            #+#    #+#             */
/*   Updated: 2025/02/01 13:07:57 by haouky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	get_a(t_map *map, double y, double x, char c)
{
	if (map->map_content[(int)(map->player.cord[0] + y) / TAILE_SIZE]
		[(int)(map->player.cord[1] + x) / TAILE_SIZE] == c)
		return (1);
	return (0);
}

int	check_wall(t_map *map, double *op, int sig)
{
	printf("*%f*\n", map->door.scop);
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
			&& map->door.scop < 70))
		return (0);
	return (1);
}
