#include "cub3D.h"

void	draw_3D(mlx_image_t *img, double dis_to_wall)
{
	double	wall_heigth;
	double	dest;
	int start[2];
	int 	i = 0;
	//dest : the distance of player to projection plane
	dest = (WI_WIDTH / 2) / tan(30 * M_PI / 180);
	wall_heigth = ((double)WALL_HEIGHT / (double)dis_to_wall) * dest;
	printf("dest = %f, wall hieght %f\n", dest	, wall_heigth);
	start[0] = (WI_HEIGHT / 2) - (wall_heigth / 2); 
	start[1] = 0;
	while(i < WI_WIDTH)
	{
		start[0] = i * REC_WITH;
		draw_rectangle(img, start, wall_heigth, create_trgb(0, 0, 255, 255));
		// start[1] += REC_WITH;
		i++;
	}

}