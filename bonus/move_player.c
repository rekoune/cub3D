/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arekoune <arekoune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 10:38:17 by arekoune          #+#    #+#             */
/*   Updated: 2025/01/23 10:39:53 by arekoune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void    mv_img(mlx_image_t *img,int y , int x)
{
	size_t i;

	i = 0;
	while(i < img->count)
	{
		img->instances[i].y -= y;
		img->instances[i].x -= x;
		if(img->instances[i].x >= MINI_WIDTH || img->instances[i].y >= MINI_HEIGHT)
				img->instances[i].enabled = 0;
		else
			img->instances[i].enabled = 1;
		i++;
	}
}

void    mouse_mv(t_map *map)
{
    int x;
	int y;
	mlx_get_mouse_pos(map->mlx, &x, &y);
	map->player.angel += (x - map->player.mouse) * DG * M_SEN;
	map->player.angel = normalize_angel(map->player.angel);
	map->player.mouse = x;
	// mlx_set_mouse_pos(map->mlx, (WI_WIDTH / 2), (WI_HEIGHT / 2));
}

void move_p(t_map *map, int sig,double angel)
{
	double radians;

	radians = angel * (M_PI / 180);
	map->player.next_p_cord[0] = cos(radians) * M_S ;
	map->player.next_p_cord[1] = sin(radians) * M_S ;
	if(check_wall(map, map->player.next_p_cord, sig))
	{
		map->player.cord[1] += round(map->player.next_p_cord[0]) * sig;
		map->player.cord[0] += round(map->player.next_p_cord[1]) * sig;
		mv_img(map->mini_img.flor, round(map->player.next_p_cord[1]) * sig, round(map->player.next_p_cord[0]) * sig);
		mv_img(map->mini_img.wall, round(map->player.next_p_cord[1]) * sig, round(map->player.next_p_cord[0]) * sig);
		mv_img(map->mini_img.door, round(map->player.next_p_cord[1]) * sig, round(map->player.next_p_cord[0]) * sig);
	}
}

void	player_movement(t_map *map)
{
	if(mlx_is_key_down(map->mlx, MLX_KEY_DOWN) || mlx_is_key_down(map->mlx, MLX_KEY_S))
		move_p(map, -1,map->player.angel);
	 if(mlx_is_key_down(map->mlx, MLX_KEY_UP) || mlx_is_key_down(map->mlx, MLX_KEY_W))
	{
		if (map->animation.timer == 0 || map->animation.flag == STANDING)
			map->animation.flag = RUNNING;
		move_p(map, 1,map->player.angel);
	}
	 if(mlx_is_key_down(map->mlx, MLX_KEY_D))
		move_p(map, 1,normalize_angel(map->player.angel + 90));
	 if(mlx_is_key_down(map->mlx, MLX_KEY_A))
		move_p(map, 1,normalize_angel(map->player.angel - 90))  ;
	 if(mlx_is_key_down(map->mlx, MLX_KEY_LEFT))
	{
		map->player.angel -= DG;
		map->player.angel = normalize_angel(map->player.angel);
	}
	 if(mlx_is_key_down(map->mlx, MLX_KEY_RIGHT))
	{
		map->player.angel += DG;
		map->player.angel = normalize_angel(map->player.angel);
	}
}

void	move_player(void *arg)
{
	t_map *map;

	map = arg;
	//mouse_mv(map);
	
	if(mlx_is_key_down(map->mlx, MLX_KEY_ESCAPE))
		exit(0);
	if (map->animation.timer == 0)
	{
		if (map->animation.flag == SHOTTING)
		{
			map->animation.shott_num--;
			draw_amo(map, map->animation.shott_num);
		}
		map->animation.flag = STANDING;
	}
	player_movement(map);
	animation_frames(map);
	animation(map);
	caster(map);
}
