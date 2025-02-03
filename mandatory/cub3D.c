/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arekoune <arekoune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:07:10 by haouky            #+#    #+#             */
/*   Updated: 2025/02/03 12:22:09 by arekoune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3D.h"

void	leaks(void)
{
	system("leaks -q cub3D");
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

int	main(int ac, char **av)
{
	t_map	*map;

	atexit(leaks);
	if (ac != 2)
		return (printf("ERROR : Invalid arguments\n"), 1);
	map = checking_map(av[1]);
	map->mlx = mlx_init(WI_WIDTH, WI_HEIGHT, "cub3D", false);
	draw_mini_map(map->mlx, map);
	map->player.cord[1] = map->player.cord[1] * TAILE_SIZE + (TAILE_SIZE / 2)
		+ (PLAYER_SIZE / 2);
	map->player.cord[0] = map->player.cord[0] * TAILE_SIZE + (TAILE_SIZE / 2)
		+ (PLAYER_SIZE / 2);
	map_max_sz(map->map_content, map->map_max_size);
	caster(map);
	mlx_loop_hook(map->mlx, &move_player, map);
	mlx_loop(map->mlx);
	free_resources(map);
}
