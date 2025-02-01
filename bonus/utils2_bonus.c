/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haouky <haouky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:13:37 by haouky            #+#    #+#             */
/*   Updated: 2025/02/01 11:33:51 by haouky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

char	valid_element(char **map)
{
	char	p;
	int		i;
	int		j;

	i = 0;
	p = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if ((map[i][j] == 'N' || map[i][j] == 'W' || map[i][j] == 'E'
					|| map[i][j] == 'S') && !p)
				p = map[i][j];
			else if (map[i][j] != '1' && map[i][j] != '0' && map[i][j] != ' '
					&& map[i][j] != 'D')
				exit(ft_write("Error: Invalid element\n", 1));
			j++;
		}
		i++;
	}
	if (!p)
		exit(ft_write("Error: Invalid element\n", 1));
	return (p);
}

void	map_max_sz(char **map, int *size)
{
	int	y;
	int	tp;

	y = 0;
	tp = 0;
	size[1] = 0;
	while (map[y])
	{
		tp = str_len(map[y], 0);
		if (tp > size[1])
			size[1] = tp;
		y++;
	}
	size[0] = y;
}

double	normalize_angel(double angel)
{
	while (angel < 0)
		angel += 360;
	while (angel >= 360)
		angel -= 360;
	return (angel);
}
void	set_derction(double angel, int *der)
{
	if (angel > 180 && angel < 360)
		der[0] = -1;
	else
		der[0] = 1;
	if (angel > 90 && angel < 270)
		der[1] = -1;
	else
		der[1] = 1;
}

int	valid_point(double *hitp, char **map, int *size)
{
	if (isinf(hitp[0]) || isinf(hitp[1]) || (int)hitp[0] < 0 || (int)hitp[1] < 0
		|| (int)(hitp[0] / TAILE_SIZE) >= (size[0]) || (int)(hitp[1]
			/ TAILE_SIZE) > (size[1]))
		hitp[0] = -1;
	if (hitp[0] == -1 || map[(int)(hitp[0] / TAILE_SIZE)][(int)(hitp[1]
			/ TAILE_SIZE)] == '1')
	{
		return (0);
	}
	if (hitp[2] == -1 && map[(int)(hitp[0] / TAILE_SIZE)][(int)(hitp[1]
			/ TAILE_SIZE)] == 'D')
	{
		hitp[2] = hitp[0];
		hitp[3] = hitp[1];
	}
	return (1);
}
