#include "cub3D.h"

void	draw_3D(mlx_image_t *img, double dis_to_wall, int color)
{
	double	wall_heigth;
	double	dest;
	double start[2];
	static double 	i;

	//dest : the distance of player to projection plane
	
	// printf("distance to wall  =  %f\n", dis_to_wall);
	if (i >= WI_WIDTH)
		i = 0;
	// printf("start y = %f, wall heigt == %f, window height = %d\n", start[0], wall_heigth / 2, WI_WIDTH / 2);
	dest = (double)(WI_WIDTH / 2) / tan(30 * M_PI / 180);
	// while(i * REC_WITH < WI_WIDTH)
	// {
		wall_heigth = (WALL_HEIGHT / dis_to_wall) * dest;
		// printf(" in draw 3D wall height == %f, dest == %f, dest to wall %f \n", wall_heigth, dest, dis_to_wall);
		// start[1] += i * REC_WITH;
		start[0] = (WI_HEIGHT /  2) - (wall_heigth / 2); 
		if (start[0] < 0)
			start[0] = 0;
		start[1] = i;
		// printf("x = %f, y = %f, wall Height == %f\n", start[1], start[0], wall_heigth);
		i += REC_WITH;
		draw_rectangle(img, start, wall_heigth, color);
	// 	i++;
	// }

}