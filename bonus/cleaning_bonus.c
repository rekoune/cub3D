/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arekoune <arekoune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:39:59 by arekoune          #+#    #+#             */
/*   Updated: 2025/01/30 12:45:24 by arekoune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	free_2d(char **str, char *str2)
{
	int	i;

	i = 0;
	if (str2)
		free(str2);
	while (str && str[i])
		free(str[i++]);
	free(str);
}

void	free_list(t_map_lst *map)
{
	t_map_lst	*node;

	while (map)
	{
		node = map->next; 
		free(map);
		map = node;
	}
}

void free_2d_int(int **array, int size)
{
	int i;

	i = 0;
	while(i < size)
		free(array[i++]);
	free(array);
}

void	free_resources(t_map *map)
{
	free_2d(map->map_content, NULL);
	free(map->directions.east);
	free(map->directions.west);
	free(map->directions.north);
	free(map->directions.south);
	if ( map->win_img.px_east)
		free_2d_int(map->win_img.px_east, map->win_img.east->height);
	if ( map->win_img.px_north)
		free_2d_int(map->win_img.px_north, map->win_img.north->height);
	if ( map->win_img.px_west)
		free_2d_int(map->win_img.px_west, map->win_img.west->height);
	if ( map->win_img.px_south)
		free_2d_int(map->win_img.px_south, map->win_img.south->height);
	if (map->win_img.px_door && map->win_img.door)
		free_2d_int(map->win_img.px_door, map->win_img.door->height);
	if (map->animation.running)
		free(map->animation.running);
	if (map->animation.reloading)
		free(map->animation.reloading);
	if (map->animation.standing)	
		free(map->animation.standing);
	if (map->animation.shotting)
		free(map->animation.shotting);
	free(map);
}
