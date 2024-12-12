#include "cub3D.h"

void	leaks(void)
{
	system("leaks -q cub3D");
}

void	draw_line(mlx_image_t *img, int *start, int *end, int color)
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

void	draw_rectangle(mlx_image_t *img, int *start, int height ,int color)
{
	int	j;
	int	i;

	j = 0;
	while(j < height && j < WI_HEIGHT)
	{
		i = 0;
		while(i < REC_WITH && i < WI_WIDTH)
		{
			mlx_put_pixel(img, start[1] + i, start[0] + j, color);
			i++;
		}
		j++;
	}
}

double	distance(int *start, int *end)
{
	double	distance;
	int		dx;
	int		dy;

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
	if(map->map_content[(int)(map->player2.y + (op[1] * sig)) / 20 ][(int)(map->player2.x + (op[0] * sig)) / 20 ] == '1' 
		|| map->map_content[(int)(map->player2.y + 5 + (op[1] * sig)) / 20 ][(int)(map->player2.x + 5 + (op[0] * sig)) / 20 ] == '1'
		|| map->map_content[(int)(map->player2.y + 5 + (op[1] * sig)) / 20 ][(int)(map->player2.x + (op[0] * sig)) / 20 ] == '1'
		|| map->map_content[(int)(map->player2.y  + (op[1] * sig)) / 20 ][(int)(map->player2.x + 5 + (op[0] * sig)) / 20 ] == '1')
		return (0);
	return (1);
}
void move_p(t_map *map, int sig)
{
	double radians;

	radians = map->player2.angel * (M_PI / 180);
	// printf("rad %f\n", radians);
	map->player2.next_p_cord[0] = cos(radians) * M_S ;
	map->player2.next_p_cord[1] = sin(radians) * M_S ;
	// printf("cosx %f\n",map->player2.next_p_cord[0]);
	// printf("siny %f\n",map->player2.next_p_cord[1]);
	if(check_wall(map, map->player2.next_p_cord, sig))
	{
		map->player2.x += (int)(map->player2.next_p_cord[0]) * sig;
		map->player2.y += (int)(map->player2.next_p_cord[1]) * sig;
		// printf("x = %f\n",map->player2.x);
		// printf("y = %f\n",map->player2.y);
		mv_img(map->mini_img.flor, (int)(map->player2.next_p_cord[1]) * sig, (int)(map->player2.next_p_cord[0]) * sig);
		mv_img(map->mini_img.wall, (int)(map->player2.next_p_cord[1]) * sig, (int)(map->player2.next_p_cord[0]) * sig);
	}
}



void	move_player(void *arg)
{
	t_map *map;

	map = arg;
	if(mlx_is_key_down(map->mlx, MLX_KEY_DOWN))
	{
		move_p(map, -1);
	}
	else if(mlx_is_key_down(map->mlx, MLX_KEY_UP))
	{
		move_p(map, 1);
	}
	else if(mlx_is_key_down(map->mlx, MLX_KEY_LEFT))
	{
		map->player2.angel -= DG;
		if(map->player2.angel < 0)
			map->player2.angel += 360;
		printf("angel %d\n", map->player2.angel);
	}
	else if(mlx_is_key_down(map->mlx, MLX_KEY_RIGHT))
	{
		map->player2.angel += DG;
		if(map->player2.angel > 360)
			map->player2.angel -= 360;
		printf("angel %d\n", map->player2.angel);
	}
	// map->player2.next_p_cord[0] = cos(map->player2.angel * (M_PI / 180)) * M_S ;
	// map->player2.next_p_cord[1] = sin(map->player2.angel * (M_PI / 180)) * M_S ;
	int p[2];
	p[0] = 500;
	p[1] = 400;
	draw_rectangle(map->win_img, p, 40, create_trgb(0, 0, 255, 255));
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
	map->player2.x *= TAILE_SIZE;
	map->player2.y *= TAILE_SIZE;
	mlx_loop_hook(map->mlx, &move_player, map);
	mlx_loop(map->mlx);
	free_resources(map);
}
