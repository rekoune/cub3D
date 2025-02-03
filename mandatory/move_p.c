/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_p.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arekoune <arekoune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:10:46 by haouky            #+#    #+#             */
/*   Updated: 2025/02/03 12:20:09 by arekoune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	check_wall(t_map *map, double *op, int sig)
{
	if (map->map_content[(int)(map->player.cord[0] - (PLAYER_SIZE / 2) + (op[1]
				* sig)) / TAILE_SIZE][(int)(map->player.cord[1] + (PLAYER_SIZE
				/ 2) + (op[0] * sig)) / TAILE_SIZE] == '1'
		|| map->map_content[(int)(map->player.cord[0] + (PLAYER_SIZE / 2)
			+ (op[1] * sig)) / TAILE_SIZE][(int)(map->player.cord[1]
			+ (PLAYER_SIZE / 2) + (op[0] * sig)) / TAILE_SIZE] == '1'
		|| map->map_content[(int)(map->player.cord[0] - (PLAYER_SIZE / 2)
			+ (op[1] * sig)) / TAILE_SIZE][(int)(map->player.cord[1]
			- (PLAYER_SIZE / 2) + (op[0] * sig)) / TAILE_SIZE] == '1'
		|| map->map_content[(int)(map->player.cord[0] + (PLAYER_SIZE / 2)
			+ (op[1] * sig)) / TAILE_SIZE][(int)(map->player.cord[1]
			- (PLAYER_SIZE / 2) + (op[0] * sig)) / TAILE_SIZE] == '1')
		return (0);
	return (1);
}

void	move_p(t_map *map, int sig, double angel)
{
	double	radians;

	radians = angel * (M_PI / 180);
	map->player.next_p_cord[0] = cos(radians) * M_S;
	map->player.next_p_cord[1] = sin(radians) * M_S;
	if (check_wall(map, map->player.next_p_cord, sig))
	{
		map->player.cord[1] += round(map->player.next_p_cord[0]) * sig;
		map->player.cord[0] += round(map->player.next_p_cord[1]) * sig;
	}
}

void	move_player(void *arg)
{
	t_map	*map;

	map = arg;
	if (mlx_is_key_down(map->mlx, 264) || mlx_is_key_down(map->mlx, MLX_KEY_S))
		move_p(map, -1, map->player.angel);
	else if (mlx_is_key_down(map->mlx, MLX_KEY_UP) 
		|| mlx_is_key_down(map->mlx, MLX_KEY_W))
		move_p(map, 1, map->player.angel);
	else if (mlx_is_key_down(map->mlx, MLX_KEY_D))
		move_p(map, 1, normalize_angel(map->player.angel + 90));
	else if (mlx_is_key_down(map->mlx, MLX_KEY_A))
		move_p(map, 1, normalize_angel(map->player.angel - 90));
	else if (mlx_is_key_down(map->mlx, MLX_KEY_LEFT))
	{
		map->player.angel -= DG;
		map->player.angel = normalize_angel(map->player.angel);
	}
	else if (mlx_is_key_down(map->mlx, MLX_KEY_RIGHT))
	{
		map->player.angel += DG;
		map->player.angel = normalize_angel(map->player.angel);
	}
	else if (mlx_is_key_down(map->mlx, MLX_KEY_ESCAPE))
		exit(0);
	caster(map);
}
