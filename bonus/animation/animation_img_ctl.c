/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_img_ctl.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arekoune <arekoune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:39:49 by arekoune          #+#    #+#             */
/*   Updated: 2025/02/03 11:56:28 by arekoune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D_bonus.h"

mlx_image_t	**get_textures(t_map *map, char *path, int size)
{
	int			i;
	mlx_image_t	**img;
	char		*joined_path;
	char		*tmp;
	char		*n_str;

	img = malloc(sizeof(mlx_image_t *) * size + 1);
	i = 0;
	while (i < size)
	{
		n_str = get_digit(i);
		joined_path = str_join(path, n_str);
		tmp = joined_path;
		joined_path = str_join(joined_path, ".png");
		img[i] = get_image(map, map->mlx, joined_path);
		free(n_str);
		free(joined_path);
		free(tmp);
		i++;
	}
	img[i] = NULL;
	return (img);
}

void	add_images(mlx_t *mlx, mlx_image_t **imgs)
{
	int	i;

	i = 0;
	while (imgs[i])
	{
		mlx_image_to_window(mlx, imgs[i], 400, 640);
		imgs[i]->enabled = false;
		i++;
	}
}

void	add_animation_img(t_map *map)
{
	add_images(map->mlx, map->animation.shotting);
	add_images(map->mlx, map->animation.reloading);
	add_images(map->mlx, map->animation.running);
	add_images(map->mlx, map->animation.standing);
}

void	disable_images(mlx_image_t **images)
{
	int	i;

	i = 0;
	while (images[i])
		images[i++]->enabled = false;
}

void	disable_all_images(t_map *map)
{
	disable_images(map->animation.shotting);
	disable_images(map->animation.reloading);
	disable_images(map->animation.running);
	disable_images(map->animation.standing);
}
