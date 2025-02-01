/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haouky <haouky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 08:34:05 by haouky            #+#    #+#             */
/*   Updated: 2025/02/01 14:08:06 by haouky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	nearest_p(t_map *map, double *hitph, double *hitpv)
{
	int	i;

	i = 0;
	if (hitpv[2] != -1 && (hitph[2] == -1 || distance(&hitph[2],
				map->player.cord) > distance(&hitpv[2], map->player.cord)))
		i = 1;
	map->door.hit_line = 'h';
	if (i == 1)
		map->door.hit_line = 'v';
	return (i);
}

double	*get_best_p(t_map *map, double *hitph, double *hitpv)
{
	int	i;

	i = nearest_p(map, hitph, hitpv);
	if (hitpv[0] != -1 && (hitph[0] == -1 || distance(hitph,
				map->player.cord) > distance(hitpv, map->player.cord)))
	{
		map->ray.hit_line = 'v';
		if (!i)
		{
			hitpv[2] = hitph[2];
			hitpv[3] = hitph[3];
		}
		return (hitpv);
	}
	else
	{
		map->ray.hit_line = 'h';
		if (i)
		{
			hitph[2] = hitpv[2];
			hitph[3] = hitpv[3];
		}
		return (hitph);
	}
}

double	*hitpoint(t_map *map, double angel, double *hitph, double *hitpv)
{
	int		der[2];
	double	yx;

	set_derction(angel, der);
	angel *= (M_PI / 180);
	victical_hit(hitpv, der, map->player, angel);
	yx = (TAILE_SIZE * der[1]) * tan(angel);
	while (valid_point(hitpv, map->map_content, map->map_max_size))
	{
		hitpv[0] += fabs(yx) * der[0];
		hitpv[1] += (TAILE_SIZE * der[1]);
	}
	horizontal_hit(hitph, der, map->player, angel);
	yx = (TAILE_SIZE * der[0]) / tan(angel);
	while (valid_point(hitph, map->map_content, map->map_max_size))
	{
		hitph[0] += (TAILE_SIZE * der[0]);
		hitph[1] += fabs(yx) * der[1];
	}
	return (get_best_p(map, hitph, hitpv));
}

void	raycaster(t_map *map, double angleshift, double *hitph, double *hitpv)
{
	double	player[2];
	double	xy[2];
	double	*hitp;

	hitp = hitpoint(map, normalize_angel(map->player.angel + angleshift), hitph,
			hitpv);
	map->ray.hit_x = hitp[1];
	map->ray.hit_y = hitp[0];
	map->door.hit_cord[1] = hitp[3];
	map->door.hit_cord[0] = hitp[2];
	if (distance(map->player.cord,
			map->door.hit_cord) > distance(map->player.cord, hitp))
		map->door.hit_cord[0] = -1;
	player[0] = map->mini_img.player->instances->y + (PLAYER_SIZE / 2);
	player[1] = map->mini_img.player->instances->x + (PLAYER_SIZE / 2);
	xy[0] = player[0] + (hitp[0] - map->player.cord[0]);
	xy[1] = player[1] + (hitp[1] - map->player.cord[1]);
	// draw_line(map->mini_img.cover, player, xy, create_trgb(255, 0, 0, 255));
	draw_3D(map, distance(map->player.cord, hitp), map->color_test, angleshift);
}

void	caster(t_map *map)
{
	double	hitph[4];
	double	hitpv[4];
	double	i;
	double	res;

	res = (PLAYER_VIEW / WI_WIDTH) * REC_WITH;
	i = (PLAYER_VIEW / 2) * -1;
	draw_img(map->win_img.win_img, WI_HEIGHT, WI_WIDTH, create_trgb(0, 0, 0,
			0));
	draw_img(map->win_img.door_cover, WI_HEIGHT, WI_WIDTH, create_trgb(0, 0, 0,
			0));
	draw_img(map->mini_img.cover, MINI_HEIGHT, MINI_WIDTH, create_trgb(0, 0, 0,
			0));
	while (i <= (PLAYER_VIEW / 2))
	{
		hitph[2] = -1;
		hitpv[2] = -1;
		raycaster(map, i, hitph, hitpv);
		i += res;
	}
}
