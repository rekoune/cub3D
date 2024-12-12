/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haouky <haouky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 10:29:34 by arekoune          #+#    #+#             */
/*   Updated: 2024/12/12 08:27:42 by haouky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	get_colors(t_map *map, char *info, enum e_type type)
{
	int		i;
	char	**rgb;
	
	rgb = ft_split(info, ',');
	free(info);
	if (str_count(rgb) != 3)
		exit(ft_write("Error: Invalid Color arguments\n", 1));
	i = -1;
	if (type == F)
		while (rgb[++i])
			map->colors.floor[i] = ft_atoi(rgb[i]);
	else if (type == C)
		while (rgb[++i])
			map->colors.ceiling[i] = ft_atoi(rgb[i]);
	free_2d(rgb, NULL);
}

bool	is_info(char *line, t_map *map)
{
	enum e_type type;
	char *info;

	type = get_info_type(line, &info);
	if (type == NO && map->directions.north == NULL)
		map->directions.north = info;
	else if (type == SO && map->directions.south == NULL)
		map->directions.south = info;
	else if (type == WE && map->directions.west == NULL)
		map->directions.west = info;
	else if (type == EA && map->directions.east == NULL)
		map->directions.east = info;
	else if ((type == F && map->colors.floor[0] == -1)
			|| (type == C && map->colors.ceiling[0] == -1))
		get_colors(map, info, type);
	else
	{
		free(info);
		return (false);
	}
	return (true);
}

int	set_map_elements(t_map *map, char *line, t_map_lst **map_lst)
{
	int	i;

	i = 0;
	while(line[i] && line[i] == ' ')
		i++;
	if (is_info(line, map))
		free(line);
	else if (line[i] == '1' && is_last(map))
	{
		add_back(map_lst, new_node(str_dup(line, 0, str_len(line,
							'\n'))));
		free(line);
		return (1);
	}
	else
	{
		free(line);
		exit(ft_write("Error: Invalid map elements\n", 1));
	}
	return (0);
}

t_map	*get_map_info(int map_fd, t_map_lst	**map_lst)
{
	char	*line;
	t_map	*map;
	int		flag;

	map = malloc(sizeof(t_map));
	map->directions.east = NULL;
	map->directions.north = NULL;
	map->directions.west = NULL;
	map->directions.south = NULL;
	map->colors.floor[0] = -1;
	map->colors.ceiling[0] = -1;
	flag = 0;
	line = get_next_line(map_fd);
	while (line)
	{
		if (!is_empty(line))
			flag = set_map_elements(map, line, map_lst);
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
	t_map_lst	*map_lst;
	char 	player;

	map_fd = check_map_file(map_file);
	map_lst = NULL;
	map = get_map_info(map_fd, &map_lst);
	map->map_content = getarray(map_lst);
	player = valid_element(map->map_content);
	map_validation(map->map_content, map_size(map_lst), player);
	if(player == 'N')
		map->player.angel = 270;
	else if(player == 'S')
		map->player.angel = 90;
	if(player == 'E')
		map->player.angel = 0;
	if(player == 'W')
		map->player.angel = 180;
	free_list(map_lst);
	close(map_fd);
	return (map);
}
