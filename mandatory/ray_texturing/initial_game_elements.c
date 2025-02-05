/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arekoune <arekoune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 13:00:35 by haouky            #+#    #+#             */
/*   Updated: 2025/02/05 12:12:45 by arekoune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	find_palayer_cord(t_player *player, char **map)
{
	int	i;
	int	j;

	j = 0;
	while (map[j])
	{
		i = 0;
		while (map[j][i])
		{
			if (map[j][i] == 'N' || map[j][i] == 'S' || map[j][i] == 'W'
				|| map[j][i] == 'E')
			{
				player->cord[1] = i;
				player->cord[0] = j;
				return ;
			}
			i++;
		}
		j++;
	}
}

int	create_trgb(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	initial_images(t_map *map)
{
	map->win_img.win_img = mlx_new_image(map->mlx, WI_WIDTH, WI_HEIGHT);
	map->win_img.background = mlx_new_image(map->mlx, WI_WIDTH, WI_HEIGHT);
	map->win_img.north = get_image(map, map->mlx, map->directions.north);
	map->win_img.east = get_image(map, map->mlx, map->directions.east);
	map->win_img.west = get_image(map, map->mlx, map->directions.west);
	map->win_img.south = get_image(map, map->mlx, map->directions.south);
	map->win_img.px_north = get_2d_pixels(map->win_img.north);
	map->win_img.px_east = get_2d_pixels(map->win_img.east);
	map->win_img.px_south = get_2d_pixels(map->win_img.south);
	map->win_img.px_west = get_2d_pixels(map->win_img.west);
}

void	drawing_images(t_map *map)
{
	double	start[2];
	double	height[2];
	int		color;

	start[0] = 0;
	start[1] = 0;
	height[0] = WI_HEIGHT / 2;
	height[1] = WI_WIDTH;
	color = create_trgb(map->colors.ceiling[0], map->colors.ceiling[1], 
			map->colors.ceiling[2], 255);
	draw_background(map->win_img.background, height, start, color);
	start[1] = WI_HEIGHT / 2;
	height[0] = WI_HEIGHT;
	draw_background(map->win_img.background, height, start,
		create_trgb(map->colors.floor[0], map->colors.floor[1],
			map->colors.floor[2], 255));
}

void	draw_game_elements(mlx_t *mlx, t_map *map)
{
	initial_images(map);
	drawing_images(map);
	find_palayer_cord(&map->player, map->map_content);
	mlx_image_to_window(mlx, map->win_img.background, 0, 0);
	mlx_image_to_window(mlx, map->win_img.win_img, 0, 0);
}
