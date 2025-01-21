/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haouky <haouky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:13:37 by haouky            #+#    #+#             */
/*   Updated: 2025/01/21 14:06:39 by haouky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
	{
		hitp[0] = -1;
	}
	if (hitp[0] == -1 || map[(int)(hitp[0] / TAILE_SIZE)][(int)(hitp[1]
			/ TAILE_SIZE)] == '1')
	{
		return (0);
	}
	return (1);
}

enum e_type	get_info_type(char *line, char **info)
{
	int		i;
	int		j;
	int		len;
	char	*identifier;

	i = 0;
	j = 0;
	len = 0;
	while (line[i] && line[i] == ' ')
		i++;
	j = i;
	while (line[j] && line[j++] != ' ')
		len++;
	while (line[j] && line[j] == ' ')
		j++;
	identifier = str_dup(line, i, len);
	*info = str_dup(line, j, str_len(&line[j], '\n'));
	return (get_identifier(identifier));
}
