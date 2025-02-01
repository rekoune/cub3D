/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_doors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arekoune <arekoune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:39:40 by arekoune          #+#    #+#             */
/*   Updated: 2025/02/01 13:47:48 by arekoune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

double	get_x_image(double hit_x, double hit_y, char flag)
{
	double	image_x;

	if (flag == 'v')
	{
		image_x = (hit_y / TAILE_SIZE) - floor(hit_y / TAILE_SIZE);
		return (image_x);
	}
	image_x = (hit_x / TAILE_SIZE) - floor(hit_x / TAILE_SIZE);
	return (image_x);
}

void	door_texturing(t_map *map, double *top_buttom, double door_height)
{
	int			image_x;
	int			image_y;
	int			**img_pixels;
	mlx_image_t	*img;
	int			i;

	i = (door_height - WI_HEIGHT) / 2;
	if (i < 0)
		i = 0;
	img = map->win_img.door;
	image_x = get_x_image(map->door.hit_cord[1], map->door.hit_cord[0],
			map->door.hit_line) * img->width;
	img_pixels = map->win_img.px_door;
	while (i < (door_height - (map->door.scop * map->door.door_height) / 100))
	{
		if (top_buttom[0] > WI_HEIGHT)
			break ;
		image_y = i / door_height * img->height;
		if (top_buttom[0] >= 0 && (top_buttom[0] > MINI_HEIGHT
				|| top_buttom[1] > MINI_WIDTH) && map->door.hit_cord[0] != -1)
			mlx_put_pixel(map->win_img.door_cover, top_buttom[1], top_buttom[0],
				img_pixels[image_y][image_x]);
		i++;
		top_buttom[0]++;
	}
}

void	check_door_timer(t_map *map)
{
	if (map->door.timer == 100)
	{
		if (map->door.open_door == true && map->door.scop < 100)
			map->door.scop += map->door.scop_size;
		else if (map->door.close_door == true && (int)map->door.scop > 0)
			map->door.scop -= map->door.scop_size;
		map->door.timer = 0;
	}
	map->door.timer++;
}

void	door_status(t_map *map, double dest, double ray_angle, double *start)
{
	double	dis_to_door;

	dis_to_door = distance(map->player.cord, map->door.hit_cord);
	if (map->door.hit_cord[0] == -1)
		dis_to_door = 100;
	dis_to_door *= cos(ray_angle * (M_PI / 180));
	map->door.door_height = ((WALL_HEIGHT / dis_to_door) * dest);
	if (dis_to_door <= 80)
	{
		map->door.open_door = true;
		map->door.close_door = false;
	}
	else if (dis_to_door >= 80 + 20)
	{
		map->door.close_door = true;
		map->door.open_door = false;
	}
	check_door_timer(map);
	start[0] = ((WI_HEIGHT / 2) - (map->door.door_height / 2))
		+ (map->door.scop * map->door.door_height) / 100;
	if (start[0] < 0)
		start[0] = 0;
	door_texturing(map, start, map->door.door_height);
}

void	draw_img(mlx_image_t *img, int height, int width, int color)
{
	int	i;
	int	j;

	j = 0;
	while (j < height)
	{
		i = 0;
		while (i < width)
		{
			mlx_put_pixel(img, i, j, color);
			i++;
		}
		j++;
	}
}
