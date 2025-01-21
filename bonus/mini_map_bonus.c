#include "cub3D_bonus.h"

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
void draw_background(mlx_image_t *img, double *height_width, double *start, int color)
{
	while(start[0] < height_width[0])
	{
		start[1] = 0;
		while(start[1] < height_width[1])
		{
			if (start[0] > MINI_HEIGHT || start[1] > MINI_WIDTH)
				mlx_put_pixel(img, start[1], start[0], color);
			start[1]++;
		}
		start[0]++;
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
			if(map[j][i] == 'N' || map[j][i] == 'S' || map[j][i] == 'W' || map[j][i] == 'E')
			{
				player->cord[1] = i;
				player->cord[0] = j;
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
			else if (map->map_content[j][i] != '1' && map->map_content[j][i] != ' ')
				mlx_image_to_window(mlx, map->mini_img.flor, i * TAILE_SIZE, j * TAILE_SIZE);
			i++;
		}
		j++;
	}
	mlx_image_to_window(mlx, map->mini_img.player, map->player.cord[1] * TAILE_SIZE + (TAILE_SIZE / 2), map->player.cord[0] * TAILE_SIZE + (TAILE_SIZE / 2));
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

void initial_images(t_map *map)
{
	map->mini_img.flor = mlx_new_image(map->mlx, TAILE_SIZE , TAILE_SIZE );
	map->mini_img.wall = mlx_new_image(map->mlx, TAILE_SIZE , TAILE_SIZE );
	map->mini_img.player = mlx_new_image(map->mlx, PLAYER_SIZE, PLAYER_SIZE);
	map->mini_img.cover = mlx_new_image(map->mlx, MINI_WIDTH, MINI_HEIGHT);
	map->win_img.win_img = mlx_new_image(map->mlx, WI_WIDTH, WI_HEIGHT);
	map->mini_img.buttom = mlx_new_image(map->mlx, MINI_WIDTH + TAILE_SIZE, TAILE_SIZE);
	map->mini_img.right = mlx_new_image(map->mlx, TAILE_SIZE, MINI_HEIGHT + TAILE_SIZE);
	map->win_img.background = mlx_new_image(map->mlx, WI_WIDTH, WI_HEIGHT);
	map->win_img.north = get_image(map, map->mlx, map->directions.north);	
	map->win_img.east = get_image(map, map->mlx, map->directions.east);	
	map->win_img.west = get_image(map, map->mlx, map->directions.west);	
	map->win_img.south = get_image(map, map->mlx, map->directions.south);
	map->win_img.px_north = get_2d_pixels(map->win_img.north);	
	map->win_img.px_east = get_2d_pixels(map->win_img.east);	
	map->win_img.px_south = get_2d_pixels(map->win_img.south);	
	map->win_img.px_west = get_2d_pixels(map->win_img.west);
	map->animation.choot_num = 8;
	map->animation.flag = 0;
	map->animation.timer = 0;	
	map->animation.amo_img = NULL;
}

void drawing_images(t_map *map)
{
	double start[2];
	start[0] = 0;
	start[1] = 0;
	double height[2];
	height[0] = WI_HEIGHT / 2;
	height[1] = WI_WIDTH;
	draw_background(map->win_img.background, height, start, create_trgb(map->colors.ceiling[0], 
				map->colors.ceiling[1], map->colors.ceiling[2], 255));
	start[1] =  WI_HEIGHT / 2;
	height[0] = WI_HEIGHT;
	draw_background(map->win_img.background, height, start, create_trgb(map->colors.floor[0], 
				map->colors.floor[1], map->colors.floor[2], 255));
	draw_img(map->mini_img.flor, TAILE_SIZE, TAILE_SIZE, create_trgb(255, 255, 255, 255));
	draw_img(map->mini_img.wall, TAILE_SIZE, TAILE_SIZE, create_trgb(0, 0, 0, 255));
	draw_img(map->mini_img.player, PLAYER_SIZE, PLAYER_SIZE, create_trgb(0, 0, 255, 255));
	draw_img(map->mini_img.buttom, TAILE_SIZE, MINI_WIDTH + TAILE_SIZE,create_trgb(map->colors.ceiling[0], 
				map->colors.ceiling[1], map->colors.ceiling[2], 255));
	draw_img(map->mini_img.right, MINI_HEIGHT, TAILE_SIZE, create_trgb(map->colors.ceiling[0], 
				map->colors.ceiling[1], map->colors.ceiling[2], 255));
}

void	draw_mini_map(mlx_t *mlx, t_map *map)
{
	

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
	add_animation_img(map);
	mlx_put_string(map->mlx, "AMO :", WI_WIDTH - 120, 10);
	map->animation.amo_img = mlx_put_string(map->mlx, "8", WI_WIDTH - 50, 10);
	if (map->mini_img.player->instances->x != MINI_WIDTH / 2)
		move_img_x(map);
	if(map->mini_img.player->instances->y != MINI_HEIGHT / 2)
		move_img_y(map);
}

