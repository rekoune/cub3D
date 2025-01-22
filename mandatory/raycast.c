/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haouky <haouky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 08:34:05 by haouky            #+#    #+#             */
/*   Updated: 2025/01/22 09:56:05 by haouky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	horizontal_hit(double *hitp, int *der, t_player player, double angel)
{
	if (der[0] == -1)
		hitp[0] = floor(player.cord[0] / TAILE_SIZE) * TAILE_SIZE - 0.00000001;
	else if (der[0] == 1)
		hitp[0] = floor(player.cord[0] / TAILE_SIZE) * TAILE_SIZE + TAILE_SIZE
			+ 0.00000001;
	if (der[1] == 1)
		hitp[1] = player.cord[1] + fabs(((hitp[0] - player.cord[0])
					/ tan(angel))) - 0.00000001;
	else
		hitp[1] = player.cord[1] - fabs(((hitp[0] - player.cord[0])
					/ tan(angel))) + 0.00000001;
}

void	victical_hit(double *hitp, int *der, t_player player, double angel)
{
	if (der[1] == -1)
		hitp[1] = floor(player.cord[1] / TAILE_SIZE) * TAILE_SIZE - 0.00000001;
	else if (der[1] == 1)
		hitp[1] = floor(player.cord[1] / TAILE_SIZE) * TAILE_SIZE + TAILE_SIZE
			+ 0.00000001;
	if (der[0] == 1)
		hitp[0] = player.cord[0] + fabs((player.cord[1] - hitp[1]) * tan(angel))
			- 0.00000001;
	else
		hitp[0] = player.cord[0] - fabs((player.cord[1] - hitp[1]) * tan(angel))
			+ 0.00000001;
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
	return (get_point(hitph, hitpv, map));
}

void	raycaster(t_map *map, double angleshift, double *hitph, double *hitpv)
{
	double	*hitp;

	hitp = hitpoint(map, normalize_angel(map->player.angel + angleshift), hitph,
			hitpv);
	map->ray.hit_x = hitp[1];
	map->ray.hit_y = hitp[0];
	draw_3d(map, distance(map->player.cord, hitp), map->color_test, angleshift);
}

void	caster(t_map *map)
{
	double	hitph[2];
	double	hitpv[2];
	double	i;
	double	px_2_px;

	px_2_px = (PLAYER_VIEW / WI_WIDTH) * REC_WITH;
	i = (PLAYER_VIEW / 2) * -1;
	draw_img(map->win_img.win_img, WI_HEIGHT, WI_WIDTH, create_trgb(0, 0, 0,
			0));
	while (i <= (PLAYER_VIEW / 2))
	{
		raycaster(map, i, hitph, hitpv);
		i += px_2_px;
	}
}
