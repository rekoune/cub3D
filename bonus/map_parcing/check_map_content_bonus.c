/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_content_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arekoune <arekoune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 07:45:44 by haouky            #+#    #+#             */
/*   Updated: 2025/02/03 11:53:36 by arekoune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D_bonus.h"

char	**getarray(t_map_lst *lst)
{
	char	**str;
	int		i;

	i = 0;
	str = malloc((ft_lstsize(lst) + 1) * sizeof(char *));
	if (!str)
		return (0);
	while (lst)
	{
		str[i++] = lst->content;
		lst = lst->next;
	}
	str[i] = NULL;
	return (str);
}

int	map_size(t_map_lst *map)
{
	int	i;

	i = 0;
	while (map)
	{
		i++;
		map = map->next;
	}
	return (i);
}

void	map_validation(char **map, int size, char p)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if ((map[i][j] == '0' || map[i][j] == p || map[i][j] == 'D') &&
			(i == 0 || i == size - 1 || j >= strr_len(map[i - 1]) || j >= 
			strr_len(map[i + 1]) || map[i - 1][j] == ' ' || map[i + 1][j] == 
			' ' || map[i][j - 1] == ' ' || map[i][j + 1] == ' '))
				exit(ft_write("Error: Map is not properly enclosed by walls\n",
						1));
			if (map[i][j] == 'D' && !(((map[i - 1][j] == '1' && map[i
							+ 1][j] == '1') && (map[i][j - 1] != '1' && map[i][j
							+ 1] != '1')) || ((map[i - 1][j] != '1' && map[i
							+ 1][j] != '1') && (map[i][j - 1] == '1' && map[i][j
							+ 1] == '1'))))
				exit(ft_write("Error: Door is not properly placed\n", 1));
			j++;
		}
		i++;
	}
}

bool	is_last(t_map *map)
{
	if (map->colors.ceiling[0] != -1 && map->colors.floor[0] != -1
		&& map->directions.east && map->directions.north && map->directions.west
		&& map->directions.south)
		return (true);
	return (false);
}
