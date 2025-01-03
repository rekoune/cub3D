    #include "cub3D.h"

void	draw_3D(t_map *map, double dis_to_wall, int color, double p)
{
	double	wall_heigth;
	double	dest;
	double start[2];
	static double 	i;

	if (p == (PLAYER_VIEW / 2) * -1)
		i = 0;
	dest = (double)(WI_WIDTH / 2) / tan((PLAYER_VIEW / 2) * M_PI / 180);
	// printf("dis to wall origin == %f, wall height == %f\n", dis_to_wall, wall_heigth);
	dis_to_wall *= cos(p * (M_PI / 180));
	wall_heigth = (WALL_HEIGHT / dis_to_wall) * dest;
	// printf("dis to wall new one == %f, wall height == %f\n", dis_to_wall, wall_heigth);
	start[0] = (WI_HEIGHT /  2) - (wall_heigth / 2); 
	if (start[0] < 0)
		start[0] = 0;
	start[1] = i;
	i += REC_WITH;
	draw_rectangle(map->win_img.win_img, start, wall_heigth, color);
}
