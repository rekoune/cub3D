#include "cub3D_bonus.h"

void	leaks(void)
{
	system("leaks -q cub3D_bonus");
	system("leaks -q cub3D_bonus");
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
			if (j + start[0] > MINI_HEIGHT || i + start[1] > MINI_WIDTH)
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
	if(map->map_content[(int)(map->player.cord[0] - (PLAYER_SIZE / 2) + (op[1] * sig)) / TAILE_SIZE ][(int)(map->player.cord[1] + (PLAYER_SIZE / 2) + (op[0] * sig)) / TAILE_SIZE ] == '1'
		|| map->map_content[(int)(map->player.cord[0] + (PLAYER_SIZE / 2) + (op[1] * sig)) / TAILE_SIZE ][(int)(map->player.cord[1] + (PLAYER_SIZE / 2) + (op[0] * sig)) / TAILE_SIZE ] == '1'
		|| map->map_content[(int)(map->player.cord[0] - (PLAYER_SIZE / 2) + (op[1] * sig)) / TAILE_SIZE ][(int)(map->player.cord[1] - (PLAYER_SIZE / 2) + (op[0] * sig)) / TAILE_SIZE ] == '1'
		|| map->map_content[(int)(map->player.cord[0] + (PLAYER_SIZE / 2) + (op[1] * sig)) / TAILE_SIZE ][(int)(map->player.cord[1] - (PLAYER_SIZE / 2) + (op[0] * sig)) / TAILE_SIZE ] == '1')
		return (0);
	return (1);
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

void mouse_mv(t_map *map)
{
    int x;
	int y;
	mlx_get_mouse_pos(map->mlx, &x, &y);
	map->player.angel += (x - map->player.mouse) * DG * M_SEN;
	map->player.angel = normalize_angel(map->player.angel);
	map->player.mouse = x;
	// mlx_set_mouse_pos(map->mlx, (WI_WIDTH / 2), (WI_HEIGHT / 2));
}

void	move_player(void *arg)
{
	t_map *map;

	map = arg;
	// mouse_mv(map);
	if(mlx_is_key_down(map->mlx, MLX_KEY_DOWN) || mlx_is_key_down(map->mlx, MLX_KEY_S))
		move_p(map, -1,map->player.angel);
	else if(mlx_is_key_down(map->mlx, MLX_KEY_UP) || mlx_is_key_down(map->mlx, MLX_KEY_W))
	{
		if (map->animation.timer == 0 || map->animation.flag == STANDING)
			map->animation.flag = RUNNING;
		move_p(map, 1,map->player.angel);
	}
	else if(mlx_is_key_down(map->mlx, MLX_KEY_D))
		move_p(map, 1,normalize_angel(map->player.angel + 90));
	else if(mlx_is_key_down(map->mlx, MLX_KEY_A))
		move_p(map, 1,normalize_angel(map->player.angel - 90))  ;
	else if(mlx_is_key_down(map->mlx, MLX_KEY_LEFT))
	{
		map->player.angel -= DG;
		map->player.angel = normalize_angel(map->player.angel);
	}
	else if(mlx_is_key_down(map->mlx, MLX_KEY_RIGHT))
	{
		map->player.angel += DG;
		map->player.angel = normalize_angel(map->player.angel);
	}
	else if(mlx_is_key_down(map->mlx, MLX_KEY_ESCAPE))
		exit(0);
	else if (mlx_is_key_down(map->mlx, MLX_KEY_RIGHT_CONTROL) || 
			mlx_is_key_down(map->mlx, MLX_KEY_LEFT_CONTROL) || 
			mlx_is_mouse_down(map->mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		if (map->animation.shott_num != 0 && (map->animation.flag == STANDING || map->animation.flag == RUNNING))
		{

			map->animation.flag = SHOTTING;
			draw_amo(map, map->animation.shott_num);
		}
	}
	else if (mlx_is_key_down(map->mlx, MLX_KEY_R))
	{
			map->animation.flag = RELOADING;
			map->animation.shott_num = 8;
			draw_amo(map, map->animation.shott_num);
	}
	else if (map->animation.shott_num == 0)
	{
			map->animation.flag = RELOADING;
			map->animation.shott_num = 8;
			draw_amo(map, map->animation.shott_num);
	}
	if (map->animation.timer == 0)
	{
		if (map->animation.flag == SHOTTING)
		{
			map->animation.shott_num--;
			draw_amo(map, map->animation.shott_num);
		}
		map->animation.flag = STANDING;
	}
	animation(map);
	caster(map);
}

int	main(int ac, char **av)
{
	t_map		*map;

	// atexit(leaks);
	if (ac != 2)
		return (printf("ERROR : Invalid arguments\n"), 1);
	map = checking_map(av[1]);
	map->mlx = mlx_init(WI_WIDTH, WI_HEIGHT, "cub3D", false);
	draw_mini_map(map->mlx, map);
	map->player.cord[1] = map->player.cord[1] * TAILE_SIZE + (TAILE_SIZE / 2) + (PLAYER_SIZE / 2);
	map->player.cord[0] = map->player.cord[0] * TAILE_SIZE + (TAILE_SIZE / 2) + (PLAYER_SIZE / 2);
	map_max_sz(map->map_content, map->map_max_size);
	// mlx_set_mouse_pos(map->mlx, (WI_WIDTH / 2), (WI_HEIGHT / 2));
	// mlx_set_cursor_mode(map->mlx, MLX_MOUSE_DISABLED);
	// caster(map);
	mlx_loop_hook(map->mlx, &move_player, map);
	mlx_loop(map->mlx);
	printf("her\n");
	mlx_set_mouse_pos(map->mlx, (WI_WIDTH / 2), (WI_HEIGHT / 2));
	free_resources(map);
}
