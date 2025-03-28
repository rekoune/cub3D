/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arekoune <arekoune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 10:28:32 by arekoune          #+#    #+#             */
/*   Updated: 2025/02/03 12:20:09 by arekoune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	check_map_file(char *str)
{
	int	dot_index;
	int	map_fd;

	dot_index = str_len(str, '\0') - 4;
	if (!str_comp(&str[dot_index], ".cub"))
		exit(ft_write("Error: invalid map extention\n", 1));
	map_fd = open(str, O_RDONLY);
	if (map_fd == -1)
	{
		perror("ERROR");
		exit(1);
	}
	return (map_fd);
}

bool	is_empty(char *line)
{
	int	i;

	i = 0;
	while (line && line[i] && line[i] == ' ')
		i++;
	if (line[i] == '\n' || line[i] == '\0')
	{
		free(line);
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

enum e_type	get_identifier(char *identifier)
{
	if (str_comp(identifier, "NO"))
		return (free(identifier), NO);
	else if (str_comp(identifier, "SO"))
		return (free(identifier), SO);
	else if (str_comp(identifier, "WE"))
		return (free(identifier), WE);
	else if (str_comp(identifier, "EA"))
		return (free(identifier), EA);
	else if (str_comp(identifier, "F"))
		return (free(identifier), F);
	else if (str_comp(identifier, "C"))
		return (free(identifier), C);
	free(identifier);
	return (false);
}
