/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_content.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haouky <haouky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 07:45:44 by haouky            #+#    #+#             */
/*   Updated: 2024/12/10 12:06:22 by haouky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
			else if (map[i][j] != '1' && map[i][j] != '0' && map[i][j] != ' ')
				exit(ft_write("Error: Invalid element\n", 1));
			j++;
		}
		i++;
	}
	if (!p)
		exit(ft_write("Error: Invalid element\n", 1));
	return (p);
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
			if (((j == 0 || !map[i][j + 1] || i == size - 1)
				&& (map[i][j] == '0' || map[i][j] == p)))
				exit(ft_write("Error: Map is not properly enclosed by walls\n",
						1));
			if ((map[i][j] == '0' || map[i][j] == p) && (j >= strr_len(map[i
						- 1]) || j >= strr_len(map[i + 1]) || map[i
					- 1][j] == ' ' || map[i + 1][j] == ' ' || map[i][j
					- 1] == ' ' || map[i][j + 1] == ' '))
				exit(ft_write("Error: Map is not properly enclosed by walls\n",
						1));
			j++;
		}
		i++;
	}
}
