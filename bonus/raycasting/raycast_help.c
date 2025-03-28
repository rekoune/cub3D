/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_help.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arekoune <arekoune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 10:56:23 by haouky            #+#    #+#             */
/*   Updated: 2025/02/03 14:20:39 by arekoune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D_bonus.h"

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
