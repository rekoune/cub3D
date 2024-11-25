#include "cub3D.h"

void	leaks(void)
{
	system("leaks -q cub3D");
}

void	move_player(void *arg)
{
	t_map *map;

	map = arg;
	if(mlx_is_key_down(map->mlx, MLX_KEY_DOWN))
	{
		// map->mini_img.player->instances->y++;
		move_imgs_inst(map->mini_img.wall, 'u', 3);
		move_imgs_inst(map->mini_img.flor, 'u', 3);
	}
	else if(mlx_is_key_down(map->mlx, MLX_KEY_UP))
	{
		// map->mini_img.player->instances->y--;
		move_imgs_inst(map->mini_img.wall, 'd', 3);
		move_imgs_inst(map->mini_img.flor, 'd', 3);
	}
	else if(mlx_is_key_down(map->mlx, MLX_KEY_RIGHT))
	{
		// map->mini_img.player->instances->x++;
		move_imgs_inst(map->mini_img.wall, 'l', 3);
		move_imgs_inst(map->mini_img.flor, 'l', 3);
	}
	else if(mlx_is_key_down(map->mlx, MLX_KEY_LEFT))
	{
		// map->mini_img.player->instances->x--;
		move_imgs_inst(map->mini_img.wall, 'r', 3);
		move_imgs_inst(map->mini_img.flor, 'r', 3);
	}
	if(mlx_is_key_down(map->mlx, MLX_KEY_ESCAPE))
		exit(0);
}

int	main(int ac, char **av)
{
	t_map		*map;

	atexit(leaks);
	if (ac != 2)
		return (printf("ERROR : Invalid arguments\n"), 1);
	map = checking_map(av[1]);
	map->mlx = mlx_init(WI_WIDTH, WI_HEIGHT, "cub3D", false);
	draw_mini_map(map->mlx, map);
	mlx_loop_hook(map->mlx, &move_player, map);
	mlx_loop(map->mlx);
	free_resources(map);
}
