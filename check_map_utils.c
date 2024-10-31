/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arekoune <arekoune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 10:28:32 by arekoune          #+#    #+#             */
/*   Updated: 2024/10/31 10:28:50 by arekoune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_map_file(char *str)
{
	int	dot_index;
	int	map_fd;

	dot_index = str_len(str, '\0') - 4;
	if (!str_comp(&str[dot_index], ".cub"))
		exit(ft_write("ERROR: invalid map extention\n", 1));
	map_fd = open(str, O_RDONLY);
	if (map_fd == -1)
	{
		perror("ERROR");
		exit(1);
	}
	return (map_fd);
}

bool	is_empty(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] && str[i] == ' ')
		i++;
	if (str[i] == '\n' || str[i] == '\0')
	{
		free(str);
		return (true);
	}
	return (false);
}

bool	is_last(t_map *map)
{
	if (map->colors.ceiling[0] != -1 && map->colors.floor[0] != -1
		&& map->directions.east && map->directions.north && map->directions.west
		&& map->directions.south)
		return (true);
	return (false);
}

void	is_last_line(int map_fd)
{
	char	*line;

	line = get_next_line(map_fd);
	while (line)
	{
		if (!is_empty(line))
		{
			free(line);
			exit(ft_write("ERROR: Empty line in the map content\n", 1));
		}
		line = get_next_line(map_fd);
	}
}
