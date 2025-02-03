/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arekoune <arekoune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:39:52 by arekoune          #+#    #+#             */
/*   Updated: 2025/02/03 12:11:57 by arekoune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D_bonus.h"

char	*get_digit(long nb)
{
	char	str[12];
	char	*s;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (nb == 0)
		str[i++] = '0';
	while (nb)
	{
		str[i++] = (nb % 10) + 48;
		nb = nb / 10;
	}
	str[i] = '\0';
	s = malloc((str_len(str, '\0') + 1) * sizeof(char));
	i--;
	while (i >= 0)
	{
		s[j] = str[i];
		j++;
		i--;
	}
	s[j] = '\0';
	return (s);
}

void	animation_init(t_map *map)
{
	map->animation.shotting = get_textures(map,
			"bonus/animation/animation_textures/shotting/", 9);
	map->animation.reloading = get_textures(map,
			"bonus/animation/animation_textures/reloading/", 24);
	map->animation.running = get_textures(map,
			"bonus/animation/animation_textures/running/", 5);
	map->animation.standing = get_textures(map,
			"bonus/animation/animation_textures/standing/", 17);
}

void	animate_it(t_map *map, mlx_image_t **images, int num_frames,
		int frame_time)
{
	(void)num_frames;
	if (map->animation.timer % frame_time == 0)
	{
		disable_all_images(map);
		if (map->animation.timer == frame_time * num_frames)
			images[0]->enabled = true;
		else
			images[map->animation.timer / frame_time]->enabled = true;
	}
}

void	draw_amo(t_map *map, int shott_num)
{
	char	*str;

	str = get_digit(shott_num);
	if (map->animation.amo_img != NULL)
		draw_img(map->animation.amo_img, map->animation.amo_img->height,
			map->animation.amo_img->width, 0);
	map->animation.amo_img = mlx_put_string(map->mlx, str, WI_WIDTH - 50, 10);
	free(str);
}

void	animation(t_map *map)
{
	int			num_frames;
	int			frame_time;
	static int	old_flag;

	frame_time = 3;
	num_frames = 0;
	if (old_flag != map->animation.flag)
	{
		old_flag = map->animation.flag;
		map->animation.timer = 0;
	}
	if (map->animation.flag == STANDING)
		animate_it(map, map->animation.standing, num_frames = 17, frame_time);
	else if (map->animation.flag == RUNNING)
		animate_it(map, map->animation.running, num_frames = 5, 4);
	else if (map->animation.flag == SHOTTING)
		animate_it(map, map->animation.shotting, num_frames = 9, frame_time);
	else if (map->animation.flag == RELOADING)
		animate_it(map, map->animation.reloading, num_frames = 24, frame_time);
	if (map->animation.timer == num_frames * frame_time)
		map->animation.timer = -1;
	map->animation.timer++;
}
