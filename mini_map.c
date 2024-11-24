#include "cub3D.h"

void draw_img(mlx_image_t *img, int height, int width, int	color)
{
	int	i;
	int	j;

	j = 0;
	while(j < height)
	{
		i = 0;
		while(i < width)
		{
			mlx_put_pixel(img, i, j, color);
			i++;
		}
		j++;
	}
}

void	find_palayer_cord(t_player *player, char **map)
{
	int	i;
	int	j;

	j = 0;
	while(map[j])
	{
		i = 0;
		while(map[j][i])
		{
			if(map[j][i] == 'N')
			{
				player->x = i;
				player->y = j;
				return;
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

void	move_imgs_inst(mlx_image_t *img, char dir, int	px_num)
{
	size_t i;

	i = 0;
	while(i < img->count)
	{
		if (dir == 'u')
			img->instances[i].y -= px_num;
		else if (dir == 'd')
			img->instances[i].y += px_num;
		else if (dir == 'r')
			img->instances[i].x += px_num;
		else if (dir == 'l')
			img->instances[i].x -= px_num;
		if(img->instances[i].x >= MINI_WIDTH || img->instances[i].y >= MINI_HEIGHT)
				img->instances[i].enabled = 0;
		else
			img->instances[i].enabled = 1;
		i++;
	}
}

void	draw_elements(mlx_t *mlx, t_map *map)
{
	int i;
	int j;

	j = 0;
	while(map->map_content[j])
	{
		i = 0;
		while(map->map_content[j][i])
		{
			if (map->map_content[j][i] == '1')
				mlx_image_to_window(mlx, map->mini_img.wall, i * TAILE_SIZE, j * TAILE_SIZE);
			else if (map->map_content[j][i] == '0' ||map->map_content[j][i] == 'N')
			{
				mlx_image_to_window(mlx, map->mini_img.flor, i * TAILE_SIZE, j * TAILE_SIZE);
				if(map->map_content[j][i] == 'N')
					mlx_image_to_window(mlx, map->mini_img.player, i * TAILE_SIZE, j * TAILE_SIZE);
			}
			i++;
		}
		j++;
	}
}

void	move_img_x(t_map *map)
{
		if(map->mini_img.player->instances->x >MINI_WIDTH / 2)
		{
			move_imgs_inst(map->mini_img.flor, 'l', map->mini_img.player->instances->x - (MINI_WIDTH / 2));
			move_imgs_inst(map->mini_img.wall, 'l', map->mini_img.player->instances->x - (MINI_WIDTH / 2));
			map->mini_img.player->instances->x -= map->mini_img.player->instances->x - (MINI_WIDTH / 2);
		}
		else
		{
			move_imgs_inst(map->mini_img.flor, 'r', (MINI_WIDTH / 2) - map->mini_img.player->instances->x);
			move_imgs_inst(map->mini_img.wall, 'r', (MINI_WIDTH / 2) - map->mini_img.player->instances->x);
			map->mini_img.player->instances->x += (MINI_WIDTH / 2) - map->mini_img.player->instances->x;
		}
}

void	move_img_y(t_map *map)
{
		if(map->mini_img.player->instances->y > MINI_HEIGHT / 2)
		{
			move_imgs_inst(map->mini_img.flor, 'u', map->mini_img.player->instances->y - (MINI_HEIGHT / 2));
			move_imgs_inst(map->mini_img.wall, 'u', map->mini_img.player->instances->y - (MINI_HEIGHT / 2));
			map->mini_img.player->instances->y -= map->mini_img.player->instances->y - (MINI_HEIGHT / 2);
		}
		else
		{
			move_imgs_inst(map->mini_img.flor, 'd', (MINI_HEIGHT / 2) - map->mini_img.player->instances->y);
			move_imgs_inst(map->mini_img.wall, 'd', (MINI_HEIGHT / 2) - map->mini_img.player->instances->y);
			map->mini_img.player->instances->y += (MINI_HEIGHT / 2) - map->mini_img.player->instances->y;
		}
}

void	put_img_on_mini(mlx_t *mlx, t_map *map)
{
	int	y;
	int x;

	y = 0;
	x = 0;
	map->mini_img.flor = mlx_new_image(mlx, TAILE_SIZE, TAILE_SIZE);
	map->mini_img.wall = mlx_new_image(mlx, TAILE_SIZE, TAILE_SIZE);
	map->mini_img.player = mlx_new_image(mlx, 5, 5);

	draw_img(map->mini_img.flor, TAILE_SIZE, TAILE_SIZE, create_trgb(255, 255, 255, 255));
	draw_img(map->mini_img.wall, TAILE_SIZE, TAILE_SIZE, create_trgb(0, 0, 0, 255));
	draw_img(map->mini_img.player, 5, 5, create_trgb(255, 0, 0, 255));
	find_palayer_cord(&map->player2, map->map_content);
	
	draw_elements(mlx, map);
	if (map->mini_img.player->instances->x != MINI_WIDTH / 2)
		move_img_x(map);
	if(map->mini_img.player->instances->y != MINI_HEIGHT / 2)
		move_img_y(map);
	
}

void	draw_mini_map(t_map *map)
{
	mlx_t	*mlx;

	mlx = mlx_init(WI_WIDTH, WI_HEIGHT, "cub3D", false);
	put_img_on_mini(mlx, map);
	mlx_loop(mlx);
}