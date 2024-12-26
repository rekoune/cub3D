#include "cub3D.h"

void	leaks(void)
{
	system("leaks -q cub3D");
}

void	draw_line(mlx_image_t *img, double *start, double *end, int color)
{
	int dy = end[0] - start[0];
	int dx = end[1] - start[1];
	int steps = 0;;
	float	x_inc = 0;
	float	y_inc = 0;
	int i = 0;
	float y = start[0];
	float x = start[1];

	if (abs(dx) > abs(dy))
		steps = abs(dx);
	else 
		steps = abs(dy);
	x_inc = (float)dx / (float)steps;
	y_inc = (float)dy / (float)steps;
	while(i < steps && y >= 0 && y < MINI_HEIGHT && x >= 0 && x < MINI_WIDTH)
	{
		mlx_put_pixel(img, round(x), round(y), color);
		x += x_inc;
		y += y_inc;
		i++;
	}
}

void	draw_rectangle(mlx_image_t *img, double *start, double height ,int color)
{
	int	j;
	int	i;

	j = 0;
	while( j < height && j + start[0] < WI_HEIGHT)
	{
		i = 0;
		while(i < REC_WITH && start[1] + i < WI_WIDTH)
		{
			mlx_put_pixel(img, start[1] + i, start[0] + j, color);
			i++;
		}
		j++;
	}
}

double	distance(double *start, double *end)
{
	double	distance;
	double		dx;
	double		dy;

	dy = end[0] - start[0];
	dx = end[1] - start[1];
	distance = sqrt(pow(dx, 2) + pow(dy, 2));
	return (distance);
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
	if(map->map_content[(int)(map->player.cord[0] + (op[1] * sig)) / TAILE_SIZE ][(int)(map->player.cord[1] + (op[0] * sig)) / TAILE_SIZE ] == '1'
		|| map->map_content[(int)(map->player.cord[0] + PLAYER_SIZE + (op[1] * sig)) / TAILE_SIZE ][(int)(map->player.cord[1] + PLAYER_SIZE + (op[0] * sig)) / TAILE_SIZE ] == '1'
		|| map->map_content[(int)(map->player.cord[0] + PLAYER_SIZE + (op[1] * sig)) / TAILE_SIZE ][(int)(map->player.cord[1] + (op[0] * sig)) / TAILE_SIZE ] == '1'
		|| map->map_content[(int)(map->player.cord[0]  + (op[1] * sig)) / TAILE_SIZE ][(int)(map->player.cord[1] + PLAYER_SIZE + (op[0] * sig)) / TAILE_SIZE ] == '1')
		return (0);
	return (1);
}
void move_p(t_map *map, int sig,double angel)
{
	double radians;

	radians = angel * (M_PI / 180);
	// printf("rad %f\n", radians);
	map->player.next_p_cord[0] = cos(radians) * M_S ;
	map->player.next_p_cord[1] = sin(radians) * M_S ;
	// printf("cosx %f\n",map->player.next_p_cord[0]);
	// printf("siny %f\n",map->player.next_p_cord[1]);
	if(check_wall(map, map->player.next_p_cord, sig))
	{
		map->player.cord[1] += round(map->player.next_p_cord[0]) * sig;
		map->player.cord[0] += round(map->player.next_p_cord[1]) * sig;
		// printf("x = %f\n",map->player.cord[1]);
		// printf("y = %f\n",map->player.cord[0]);
		mv_img(map->mini_img.flor, round(map->player.next_p_cord[1]) * sig, round(map->player.next_p_cord[0]) * sig);
		mv_img(map->mini_img.wall, round(map->player.next_p_cord[1]) * sig, round(map->player.next_p_cord[0]) * sig);
		caster(map);
	}
}



void	move_player(void *arg)
{
	t_map *map;

	map = arg;
	if(mlx_is_key_down(map->mlx, MLX_KEY_DOWN) || mlx_is_key_down(map->mlx, MLX_KEY_S))
		move_p(map, -1,map->player.angel);
	else if(mlx_is_key_down(map->mlx, MLX_KEY_UP) || mlx_is_key_down(map->mlx, MLX_KEY_W))
		move_p(map, 1,map->player.angel);
	else if(mlx_is_key_down(map->mlx, MLX_KEY_D))
		move_p(map, 1,normalize_angel(map->player.angel + 90));
	else if(mlx_is_key_down(map->mlx, MLX_KEY_A))
		move_p(map, 1,normalize_angel(map->player.angel - 90));
	else if(mlx_is_key_down(map->mlx, MLX_KEY_LEFT))
	{
		map->player.angel -= DG;
		map->player.angel = normalize_angel(map->player.angel);
		caster(map);
	}
	else if(mlx_is_key_down(map->mlx, MLX_KEY_RIGHT))
	{
		map->player.angel = normalize_angel(map->player.angel);
		map->player.angel += DG;
		caster(map);
	}
	else if(mlx_is_key_down(map->mlx, MLX_KEY_ESCAPE))
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
	map->player.cord[1] = map->player.cord[1] * TAILE_SIZE + (TAILE_SIZE / 2) ;
	map->player.cord[0] = map->player.cord[0] * TAILE_SIZE + (TAILE_SIZE / 2);
	map_max_sz(map->map_content, map->map_max_size);
	caster(map);
	mlx_loop_hook(map->mlx, &move_player, map);
	// mlx_key_hook(map->mlx,my_ftkey,map);
	mlx_loop(map->mlx);
	free_resources(map);
}
