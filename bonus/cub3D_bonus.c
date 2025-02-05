/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arekoune <arekoune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:40:04 by arekoune          #+#    #+#             */
/*   Updated: 2025/02/05 12:09:56 by arekoune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3D_bonus.h"

int	main(int ac, char **av)
{
	t_map	*map;

	if (ac != 2)
		return (printf("ERROR : Invalid arguments\n"), 1);
	map = checking_map(av[1]);
	map->win_img.door = NULL;
	map->mlx = mlx_init(WI_WIDTH, WI_HEIGHT, "cub3D_bonus", false);
	draw_mini_map(map->mlx, map);
	map->player.cord[1] = map->player.cord[1] * TAILE_SIZE + (TAILE_SIZE / 2)
		+ (PLAYER_SIZE / 2);
	map->player.cord[0] = map->player.cord[0] * TAILE_SIZE + (TAILE_SIZE / 2)
		+ (PLAYER_SIZE / 2);
	map_max_sz(map->map_content, map->map_max_size);
	map->player.mouseactive = 2;
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
