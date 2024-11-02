/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arekoune <arekoune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 10:28:32 by arekoune          #+#    #+#             */
/*   Updated: 2024/11/02 18:39:24 by arekoune         ###   ########.fr       */
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

enum e_type get_info_type(char *line, char **info)
{
	int	i;
	int	j;
	int	len;
	char	*identifier;

	i = 0;
	j = 0;
	len = 0;
	while(line[i] && line[i] == ' ')
		i++;
	j = i;
	while(line[j] && line[j++] != ' ')
		len++;
	while(line[j] && line[j] == ' ')
		j++;
	identifier = str_dup(line, i, len);
	*info = str_dup(line, j, str_len(&line[j], '\n'));
	if (str_comp(identifier, "NO"))
		return(free(identifier), NO);
	else if (str_comp(identifier, "SO"))
		return(free(identifier), SO);
	else if (str_comp(identifier, "WE"))
		return(free(identifier), WE);
	else if (str_comp(identifier, "EA"))
		return(free(identifier), EA);
	else if (str_comp(identifier, "F"))
		return(free(identifier), F);
	else if (str_comp(identifier, "C"))
		return(free(identifier), C);
	return(false);
}

// int main ()
// {
// 	char *str;
	
// 	enum e_type type = get_info_type("              so                        HONA   HAMADA", &str);
// 	printf("%s\n", str);
// }
