/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arekoune <arekoune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 10:29:34 by arekoune          #+#    #+#             */
/*   Updated: 2024/10/31 11:04:12 by arekoune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	get_colors(t_map *map, char **element)
{
	int		i;
	char	*join;
	char	*tmp;
	char	**rgb;

	join = NULL;
	i = 1;
	while (element[i])
		join = str_join(join, element[i++]);
	tmp = join;
	join = str_dup(join, 0, str_len(join, '\0') - 1);
	free(tmp);
	rgb = ft_split(join, ',');
	free(join);
	if (str_count(rgb) != 3)
		exit(ft_write("ERROR: Invalid Color arguments\n", 1));
	i = -1;
	if (str_comp(element[0], "F"))
		while (rgb[++i])
			map->colors.floor[i] = ft_atoi(rgb[i]);
	else if (str_comp(element[0], "C"))
		while (rgb[++i])
			map->colors.ceiling[i] = ft_atoi(rgb[i]);
	free_2d(rgb, NULL);
}

bool	is_info(char **element, t_map *map)
{
	int	n_word;
	int	size;

	size = str_len(element[1], '\0') - 1;
	n_word = str_count(element);
	if (str_comp(element[0], "NO") && map->directions.north == NULL
		&& n_word == 2)
		map->directions.north = str_dup(element[1], 0, size);
	else if (str_comp(element[0], "SO") && map->directions.south == NULL
		&& n_word == 2)
		map->directions.south = str_dup(element[1], 0, size);
	else if (str_comp(element[0], "WE") && map->directions.west == NULL
		&& n_word == 2)
		map->directions.west = str_dup(element[1], 0, size);
	else if (str_comp(element[0], "EA") && map->directions.east == NULL
		&& n_word == 2)
		map->directions.east = str_dup(element[1], 0, size);
	else if ((str_comp(element[0], "F") && map->colors.floor[0] == -1)
		|| (str_comp(element[0], "C") && map->colors.ceiling[0] == -1))
		get_colors(map, element);
	else
		return (false);
	return (true);
}

int	set_map_elements(t_map *map, char *line)
{
	char	**element;

	element = ft_split(line, ' ');
	if (is_info(element, map))
		free_2d(element, line);
	else if (element[0][0] == '1' && is_last(map))
	{
		add_back(&map->map_lst, new_node(str_dup(line, 0, str_len(line,
						'\n'))));
		free_2d(element, line);
		return (1);
	}
	else
	{
		free_2d(element, line);
		exit(ft_write("ERROR: Invalid map\n", 1));
	}
	return (0);
}

t_map	*get_map_info(int map_fd)
{
	char	*line;
	t_map	*map;
	int		flag;

	map = malloc(sizeof(t_map));
	map->directions.east = NULL;
	map->directions.north = NULL;
	map->directions.west = NULL;
	map->directions.south = NULL;
	map->map_lst = NULL;
	map->colors.floor[0] = -1;
	map->colors.ceiling[0] = -1;
	flag = 0;
	line = get_next_line(map_fd);
	while (line)
	{
		if (!is_empty(line))
			flag = set_map_elements(map, line);
		else if (flag == 1)
			is_last_line(map_fd);
		line = get_next_line(map_fd);
	}
	return (map);
}

t_map	*checking_map(char *map_file)
{
	int			map_fd;
	t_map		*map;

	map_fd = check_map_file(map_file);
	map = get_map_info(map_fd);
	// hamza here you call the function that checking the map content
	//do it on the file check_map_content
	return (map);
}
