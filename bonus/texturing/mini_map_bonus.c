/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arekoune <arekoune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:40:33 by arekoune          #+#    #+#             */
/*   Updated: 2025/02/03 14:13:05 by arekoune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D_bonus.h"

void	draw_background(t_map *map)
{
	int	floor_color;
	int	ceil_color;
	int	i;
	int	j;

	ceil_color = create_trgb(map->colors.ceiling[0], map->colors.ceiling[1],
			map->colors.ceiling[2], 255);
	floor_color = create_trgb(map->colors.floor[0], map->colors.floor[1],
			map->colors.floor[2], 255);
	j = 0;
	while (j < (int)map->win_img.background->height)
	{
		i = 0;
		if (j >= WI_HEIGHT / 2)
			ceil_color = floor_color;
		while (i < (int)map->win_img.background->width)
		{
			if (j > MINI_HEIGHT || i > MINI_WIDTH)
				mlx_put_pixel(map->win_img.background, i, j, ceil_color);
			i++;
		}
		j++;
	}
}

void	draw_elements(mlx_t *mlx, t_map *map)
{
	int	i;
	int	j;

	j = -1;
	while (map->map_content[++j])
	{
		i = 0;
		while (map->map_content[j][i])
		{
			if (map->map_content[j][i] == '1')
				mlx_image_to_window(mlx, map->mini_img.wall, i * TAILE_SIZE, j
					* TAILE_SIZE);
			else if (map->map_content[j][i] == 'D')
				mlx_image_to_window(mlx, map->mini_img.door, (i * TAILE_SIZE)
					+ 2, (j * TAILE_SIZE) + 2);
			else if (map->map_content[j][i] != '1'
					&& map->map_content[j][i] != ' ')
				mlx_image_to_window(mlx, map->mini_img.flor, i * TAILE_SIZE, j
					* TAILE_SIZE);
			i++;
		}
	}
	mlx_image_to_window(mlx, map->mini_img.player, map->player.cord[1]
		* TAILE_SIZE + (TAILE_SIZE / 2), map->player.cord[0] * TAILE_SIZE
		+ (TAILE_SIZE / 2));
}

void	initial_images(t_map *map)
{
	map->mini_img.flor = mlx_new_image(map->mlx, TAILE_SIZE, TAILE_SIZE);
	map->mini_img.wall = mlx_new_image(map->mlx, TAILE_SIZE, TAILE_SIZE);
	map->mini_img.door = mlx_new_image(map->mlx, TAILE_SIZE - 4, TAILE_SIZE
			- 4);
	map->mini_img.player = mlx_new_image(map->mlx, PLAYER_SIZE, PLAYER_SIZE);
	map->mini_img.cover = mlx_new_image(map->mlx, MINI_WIDTH, MINI_HEIGHT);
	map->win_img.win_img = mlx_new_image(map->mlx, WI_WIDTH, WI_HEIGHT);
	map->win_img.door_cover = mlx_new_image(map->mlx, WI_WIDTH, WI_HEIGHT);
	map->mini_img.buttom = mlx_new_image(map->mlx, MINI_WIDTH + TAILE_SIZE,
			TAILE_SIZE);
	map->mini_img.right = mlx_new_image(map->mlx, TAILE_SIZE, MINI_HEIGHT
			+ TAILE_SIZE);
	map->win_img.background = mlx_new_image(map->mlx, WI_WIDTH, WI_HEIGHT);
	map->win_img.north = get_image(map, map->mlx, map->directions.north);
	map->win_img.east = get_image(map, map->mlx, map->directions.east);
	map->win_img.west = get_image(map, map->mlx, map->directions.west);
	map->win_img.south = get_image(map, map->mlx, map->directions.south);
	map->win_img.door = get_image(map, map->mlx, "textures/door.png");
	map->control.img = get_image(map, map->mlx, "textures/control_page.png");
	map->win_img.px_north = get_2d_pixels(map->win_img.north);
	map->win_img.px_east = get_2d_pixels(map->win_img.east);
	map->win_img.px_south = get_2d_pixels(map->win_img.south);
	map->win_img.px_west = get_2d_pixels(map->win_img.west);
	map->win_img.px_door = get_2d_pixels(map->win_img.door);
}

void	drawing_images(t_map *map)
{
	draw_background(map);
	draw_img(map->mini_img.flor, TAILE_SIZE, TAILE_SIZE, create_trgb(255, 255,
			255, 255));
	draw_img(map->mini_img.door, TAILE_SIZE - 4, TAILE_SIZE - 4,
		create_trgb(139, 69, 19, 255));
	draw_img(map->mini_img.wall, TAILE_SIZE, TAILE_SIZE, create_trgb(0, 0, 0,
			255));
	draw_img(map->mini_img.player, PLAYER_SIZE, PLAYER_SIZE, create_trgb(0, 0,
			255, 255));
	draw_img(map->mini_img.buttom, TAILE_SIZE, MINI_WIDTH + TAILE_SIZE,
		create_trgb(map->colors.ceiling[0], map->colors.ceiling[1],
			map->colors.ceiling[2], 255));
	draw_img(map->mini_img.right, MINI_HEIGHT, TAILE_SIZE,
		create_trgb(map->colors.ceiling[0], map->colors.ceiling[1],
			map->colors.ceiling[2], 255));
}

void	draw_mini_map(mlx_t *mlx, t_map *map)
{
	map->animation = (t_animation){.reloading = NULL, .running = NULL,
		.shotting = NULL, .standing = NULL, .shott_num = 8, 
		.flag = 10, .timer = 0, .amo_img = NULL};
	map->control.enable = false;
	initial_images(map);
	animation_init(map);
	drawing_images(map);
	find_palayer_cord(&map->player, map->map_content);
	mlx_image_to_window(mlx, map->win_img.background, 0, 0);
	draw_elements(mlx, map);
	mlx_image_to_window(mlx, map->mini_img.cover, 0, 0);
	mlx_image_to_window(mlx, map->mini_img.buttom, 0, MINI_HEIGHT);
	mlx_image_to_window(mlx, map->mini_img.right, MINI_WIDTH, 0);
	mlx_image_to_window(mlx, map->win_img.win_img, 0, 0);
	mlx_image_to_window(mlx, map->win_img.door_cover, 0, 0);
	add_animation_img(map);
	mlx_put_string(map->mlx, "AMO :", WI_WIDTH - 120, 10);
	map->animation.amo_img = mlx_put_string(map->mlx, "8", WI_WIDTH - 50, 10);
	if (map->mini_img.player->instances->x != MINI_WIDTH / 2)
		move_img_x(map);
	if (map->mini_img.player->instances->y != MINI_HEIGHT / 2)
		move_img_y(map);
	mlx_image_to_window(mlx, map->control.img, 0, 0);
}
