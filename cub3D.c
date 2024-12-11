#include "cub3D.h"

void	leaks(void)
{
	system("leaks -q cub3D");
}
void mv_img(mlx_image_t *img,int y , int x)
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

int check_wall(t_map *map , double *op, int sig)
{
	if(map->map_content[(int)(map->player2.y + (op[1] * sig)) / 20 ][(int)(map->player2.x + (op[0] * sig)) / 20 ] == '1' 
		|| map->map_content[(int)(map->player2.y + 5 + (op[1] * sig)) / 20 ][(int)(map->player2.x + 5 + (op[0] * sig)) / 20 ] == '1'
		|| map->map_content[(int)(map->player2.y + 5 + (op[1] * sig)) / 20 ][(int)(map->player2.x + (op[0] * sig)) / 20 ] == '1'
		|| map->map_content[(int)(map->player2.y  + (op[1] * sig)) / 20 ][(int)(map->player2.x + 5 + (op[0] * sig)) / 20 ] == '1')
		return (0);
	return (1);
}
void move_p(t_map *map, int sig)
{
	double op[2];
	double radians;

	radians = map->player2.angel * (M_PI / 180);
	printf("rad %f\n", radians);
	op[0] = cos(radians) * M_S ;
	op[1] = sin(radians) * M_S ;
	printf("cosx %f\n",op[0]);
	printf("siny %f\n",op[1]);
	if(check_wall(map, op, sig))
	{
		map->player2.x += (int)(op[0]) * sig;
		map->player2.y += (int)(op[1]) * sig;
		printf("x = %f\n",map->player2.x);
		printf("y = %f\n",map->player2.y);
		mv_img(map->mini_img.flor, (int)(op[1]) * sig, (int)(op[0]) * sig);
		mv_img(map->mini_img.wall, (int)(op[1]) * sig, (int)(op[0]) * sig);
	}
}

void	move_player(void *arg)
{
	t_map *map;

	map = arg;
	if(mlx_is_key_down(map->mlx, MLX_KEY_DOWN))
		move_p(map, -1);
	else if(mlx_is_key_down(map->mlx, MLX_KEY_UP))
		move_p(map, 1);
	else if(mlx_is_key_down(map->mlx, MLX_KEY_LEFT))
	{
		map->player2.angel -= DG;
		printf("angel %f\n", map->player2.angel);
		if(map->player2.angel < 0)
			map->player2.angel += 360;
	}
	else if(mlx_is_key_down(map->mlx, MLX_KEY_RIGHT))
	{
		map->player2.angel += DG;
		printf("angel %f\n", map->player2.angel);
		if(map->player2.angel > 360)
			map->player2.angel -= 360;
	}
	if(mlx_is_key_down(map->mlx, MLX_KEY_ESCAPE))
		exit(0);
	caster(map); 
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
	map->player2.x *= 20;
	map->player2.y *= 20;
	map_max_sz(map->map_content, map->map_max_size);
	mlx_loop_hook(map->mlx, &move_player, map);
	mlx_loop(map->mlx);
	free_resources(map);
}
