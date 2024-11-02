/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_content.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haouky <haouky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 07:45:44 by haouky            #+#    #+#             */
/*   Updated: 2024/11/02 11:54:51 by haouky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	**getarray(t_map_lst *lst)
{
	char		**str;
	int			i;
	t_map_lst	*tmp;

	i = 0;
	str = malloc((ft_lstsize(lst) + 1) * sizeof(char *));
	if (!str)
		return (0);
	while (lst)
	{
		str[i] = lst->content;
		i++;
		tmp = lst;
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

void	map_validation(char **map, int size)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j] && map[i][j] != '\n')
		{
			if (((i == 0 || j == 0 || !map[i][j + 1] || i == size - 1)
				&& map[i][j] == '0'))
				exit(ft_write("ERROR: Invalid map\n", 1));
			if (map[i][j] == '0' && (map[i - 1][j] == ' ' || map[i
					+ 1][j] == ' ' || map[i][j - 1] == ' ' || map[i][j
					+ 1] == ' '))
				exit(ft_write("ERROR: Invalid map\n", 1));
			j++;
		}
		i++;
	}
}
