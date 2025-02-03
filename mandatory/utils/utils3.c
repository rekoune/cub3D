/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arekoune <arekoune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:21:39 by haouky            #+#    #+#             */
/*   Updated: 2025/02/03 12:20:09 by arekoune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

mlx_image_t	*get_image(t_map *map, mlx_t *mlx, char *path)
{
	mlx_texture_t	*texture;
	mlx_image_t		*img;

	texture = mlx_load_png(path);
	if (!texture)
	{
		free_resources(map);
		exit(ft_write("Invalid texture\n", 1));
	}
	img = mlx_texture_to_image(mlx, texture);
	if (!img)
	{
		free_resources(map);
		mlx_delete_texture(texture);
		exit(ft_write("Getting the image form texture fails\n", 1));
	}
	mlx_delete_texture(texture);
	return (img);
}

double	*get_point(double *hitph, double *hitpv, t_map *map)
{
	if (hitpv[0] != -1 && (hitph[0] == -1 || distance(hitph,
				map->player.cord) > distance(hitpv, map->player.cord)))
	{
		map->ray.hit_line = 'v';
		return (hitpv);
	}
	else
	{
		map->ray.hit_line = 'h';
		return (hitph);
	}
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

void	draw_background(mlx_image_t *img, double *height_width, double *start,
		int color)
{
	while (start[0] < height_width[0])
	{
		start[1] = 0;
		while (start[1] < height_width[1])
		{
			mlx_put_pixel(img, start[1], start[0], color);
			start[1]++;
		}
		start[0]++;
	}
}

bool	str_comp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (false);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (s1[i] != s2[i])
		return (false);
	return (true);
}
