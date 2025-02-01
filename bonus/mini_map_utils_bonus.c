#include "cub3D_bonus.h"

void	move_imgs_inst(mlx_image_t *img, char dir, int px_num)
{
	size_t	i;

	i = 0;
	while (i < img->count)
	{
		if (dir == 'u')
			img->instances[i].y -= px_num;
		else if (dir == 'd')
			img->instances[i].y += px_num;
		else if (dir == 'r')
			img->instances[i].x += px_num;
		else if (dir == 'l')
			img->instances[i].x -= px_num;
		if (img->instances[i].x >= MINI_WIDTH
			|| img->instances[i].y >= MINI_HEIGHT)
			img->instances[i].enabled = 0;
		else
			img->instances[i].enabled = 1;
		i++;
	}
}

void	move_img_x(t_map *map)
{
	if (map->mini_img.player->instances->x > MINI_WIDTH / 2)
	{
		move_imgs_inst(map->mini_img.flor, 'l',
				map->mini_img.player->instances->x - (MINI_WIDTH / 2));
		move_imgs_inst(map->mini_img.wall, 'l',
				map->mini_img.player->instances->x - (MINI_WIDTH / 2));
		move_imgs_inst(map->mini_img.door, 'l',
				map->mini_img.player->instances->x - (MINI_WIDTH / 2));
		map->mini_img.player->instances->x -= map->mini_img.player->instances->x
			- (MINI_WIDTH / 2);
	}
	else
	{
		move_imgs_inst(map->mini_img.flor, 'r', (MINI_WIDTH / 2)
				- map->mini_img.player->instances->x);
		move_imgs_inst(map->mini_img.wall, 'r', (MINI_WIDTH / 2)
				- map->mini_img.player->instances->x);
		move_imgs_inst(map->mini_img.door, 'r', (MINI_WIDTH / 2)
				- map->mini_img.player->instances->x);
		map->mini_img.player->instances->x += (MINI_WIDTH / 2)
			- map->mini_img.player->instances->x;
	}
}

void	move_img_y(t_map *map)
{
	if (map->mini_img.player->instances->y > MINI_HEIGHT / 2)
	{
		move_imgs_inst(map->mini_img.flor, 'u',
				map->mini_img.player->instances->y - (MINI_HEIGHT / 2));
		move_imgs_inst(map->mini_img.wall, 'u',
				map->mini_img.player->instances->y - (MINI_HEIGHT / 2));
		move_imgs_inst(map->mini_img.door, 'u',
				map->mini_img.player->instances->y - (MINI_HEIGHT / 2));
		map->mini_img.player->instances->y -= map->mini_img.player->instances->y
			- (MINI_HEIGHT / 2);
	}
	else
	{
		move_imgs_inst(map->mini_img.flor, 'd', (MINI_HEIGHT / 2)
				- map->mini_img.player->instances->y);
		move_imgs_inst(map->mini_img.wall, 'd', (MINI_HEIGHT / 2)
				- map->mini_img.player->instances->y);
		move_imgs_inst(map->mini_img.door, 'd', (MINI_HEIGHT / 2)
				- map->mini_img.player->instances->y);
		map->mini_img.player->instances->y += (MINI_HEIGHT / 2)
			- map->mini_img.player->instances->y;
	}
}

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
