/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3D.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arekoune <arekoune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:20:08 by haouky            #+#    #+#             */
/*   Updated: 2025/02/01 12:24:30 by arekoune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	**get_2d_pixels(mlx_image_t *img)
{
	int	**pixels_2d;
	int	i;
	int	j;
	int	count;
	int	*pixel;

	i = 0;
	count = 0;
	if (!img)
		return (NULL);
	pixels_2d = malloc(sizeof(int *) * img->height);
	while (i < (int) img->height)
	{
		j = 0;
		pixel = malloc(sizeof(int) * img->width);
		while (j < (int) img->width)
		{
			pixel[j++] = create_trgb(img->pixels[count], 
					img->pixels[count + 1], img->pixels[count + 2], 
					img->pixels[count + 3]);
			count += 4;
		}
		pixels_2d[i++] = pixel;
	}
	return (pixels_2d);
}

double	get_x_image(t_ray ray)
{
	double	image_x;

	if (ray.hit_line == 'v')
	{
		image_x = (ray.hit_y / TAILE_SIZE) - floor(ray.hit_y / TAILE_SIZE);
		return (image_x);
	}
	image_x = (ray.hit_x / TAILE_SIZE) - floor(ray.hit_x / TAILE_SIZE);
	return (image_x);
}

mlx_image_t	*get_dir_img(t_map *map, int ***img_pixels, double ray_angle)
{
	if (map->ray.hit_line == 'h' && sin((ray_angle + 
				map->player.angel) * (M_PI / 180)) < 0)
	{
		*img_pixels = map->win_img.px_north;
		return (map->win_img.north);
	}
	else if (map->ray.hit_line == 'h' && sin((ray_angle + 
				map->player.angel) * (M_PI / 180)) > 0)
	{
		*img_pixels = map->win_img.px_south;
		return (map->win_img.south);
	}
	else if (map->ray.hit_line == 'v' && cos((ray_angle + 
				map->player.angel) * (M_PI / 180)) > 0)
	{
		*img_pixels = map->win_img.px_east;
		return (map->win_img.east);
	}
	else if (map->ray.hit_line == 'v' && cos((ray_angle + 
				map->player.angel) * (M_PI / 180)) < 0)
	{
		*img_pixels = map->win_img.px_west;
		return (map->win_img.west);
	}
	return (NULL);
}

void	texturing(t_map *map, double *top_buttom, 
			double wall_height, double ray_angle)
{
	int			image_x;
	int			image_y;
	int			**img_pixels;
	mlx_image_t	*img;
	int			i;

	i = (wall_height - WI_HEIGHT) / 2;
	if (i < 0)
		i = 0;
	img = get_dir_img(map, &img_pixels, ray_angle);
	image_x = get_x_image(map->ray) * img->width;
	while (i < wall_height)
	{
		if (top_buttom[0] > WI_HEIGHT)
			break ;
		image_y = i / wall_height * img->height;
		if (top_buttom[0] >= 0)
			mlx_put_pixel(map->win_img.win_img, top_buttom[1], 
				top_buttom[0], img_pixels[image_y][image_x]);
		i++;
		top_buttom[0]++;
	}
}

void	draw_3d(t_map *map, double dis_to_wall, int color, double p)
{
	double			wall_heigth;
	double			dest;
	double			start[2];
	static double	i;

	if (p == (PLAYER_VIEW / 2) * -1)
		i = 0;
	dest = (double)(WI_WIDTH / 2) / tan((PLAYER_VIEW / 2) * M_PI / 180);
	dis_to_wall *= cos(p * (M_PI / 180));
	wall_heigth = (WALL_HEIGHT / dis_to_wall) * dest;
	start[0] = (WI_HEIGHT / 2) - (wall_heigth / 2); 
	if (start[0] < 0)
		start[0] = 0;
	start[1] = i;
	i += REC_WITH;
	texturing(map, start, wall_heigth, p);
	(void) color;
}
