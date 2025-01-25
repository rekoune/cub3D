    #include "cub3D_bonus.h"

mlx_image_t *get_image(t_map *map, mlx_t *mlx, char *path)
{
	mlx_texture_t *texture;
	mlx_image_t *img;

	texture = mlx_load_png(path);
	if (!texture)
	{
		free_resources(map);
		exit(ft_write("Invalid texture\n", 1));
	}
	img = mlx_texture_to_image(mlx, texture);
	if (!img)
	{
		free_resources(map);
		mlx_delete_texture(texture);
		exit(ft_write("Getting the image form texture fails\n", 1));
	}
	mlx_delete_texture(texture);
	return (img);
}
int	**get_2d_pixels(mlx_image_t *img)
{
	int **pixels_2d;
	int	i;
	int	j;
	int count;
	int	*pixel;

	i = 0;
	count = 0;
	if (!img)
		return(NULL);
	pixels_2d = malloc(sizeof(int *) * img->height);
	while (i < (int) img->height)
	{
		j = 0;
		pixel = malloc(sizeof(int) * img->width);
		while (j < (int) img->width)
		{
			pixel[j++] = create_trgb(img->pixels[count], img->pixels[count + 1], 
											img->pixels[count + 2], img->pixels[count + 3]);
			count += 4;
		}
		pixels_2d[i++] = pixel;
	}
	return(pixels_2d);
}

double get_x_image(double hit_x, double hit_y, char flag)
{
	double image_x;

	if (flag == 'v')
	{
		image_x = (hit_y / TAILE_SIZE ) - floor(hit_y / TAILE_SIZE );
		return (image_x);
	}
	image_x = (hit_x /TAILE_SIZE) -  floor(hit_x / TAILE_SIZE);
	return(image_x);
}

mlx_image_t *get_dir_img(t_map *map, int ***img_pixels, double ray_angle)
{
	// if(map->ray.hit_line == 'v' && map->ray.dir == 1){
	// 	*img_pixels = map->win_img.px_north;
	// 	return (map->win_img.north);
	// }
	// else if(map->ray.hit_line == 'v' && map->ray.dir == -1){
	// 	*img_pixels = map->win_img.px_south;
	// 	return (map->win_img.south);
	// }
	// else if(map->ray.hit_line == 'h' && map->ray.dir == 1){
	// 	*img_pixels = map->win_img.px_east;
	// 	return (map->win_img.east);
	// }
	// *img_pixels = map->win_img.px_west;
	// return (map->win_img.west);
	// (void) ray_angle;
	if (map->ray.hit_line == 'h' && sin((ray_angle + map->player.angel) * (M_PI / 180)) < 0)
	{
		*img_pixels = map->win_img.px_north;
		return (map->win_img.north);
	}
	else if(map->ray.hit_line == 'h' && sin((ray_angle + map->player.angel) * (M_PI / 180)) > 0){
		*img_pixels = map->win_img.px_south;
		return (map->win_img.south);
	}
	else if(map->ray.hit_line == 'v' && cos((ray_angle + map->player.angel) * (M_PI / 180)) > 0){
		*img_pixels = map->win_img.px_east;
		return (map->win_img.east);
	}
	else if (map->ray.hit_line == 'v' && cos((ray_angle + map->player.angel) * (M_PI / 180)) < 0)
	{
		*img_pixels = map->win_img.px_west;
		return (map->win_img.west);
	}
	return (NULL);
}

void door_texturing(t_map *map, double *top_buttom, double wall_height, double dist_to_door)
{
	int	image_x;
	int	image_y;
	int	**img_pixels;
	mlx_image_t *img;
	int	i;

	i = (wall_height - WI_HEIGHT) / 2;
	if (i < 0)
		i = 0;                                                                                                                           
	img = map->win_img.door;
	image_x = get_x_image(map->door.hit_cord[1], map->door.hit_cord[0], map->door.hit_line) * img->width;
	img_pixels = map->win_img.px_door;
	
	while(i < wall_height)
	{
		if (top_buttom[0] > WI_HEIGHT){
			break;
		}
		image_y = i / wall_height * img->height;
		if (image_y > map->door.scop)
			if (top_buttom[0] >= 0 && (top_buttom[0] > MINI_HEIGHT || top_buttom[1] > MINI_WIDTH)){
					mlx_put_pixel(map->win_img.door_cover, top_buttom[1], top_buttom[0], img_pixels[image_y][image_x]);
		// if (dist_to_door <= 100)
		// 	mlx_put_pixel(map->win_img.door_cover, top_buttom[1], top_buttom[0], 0);
		}
		i++;
		top_buttom[0]++;
	}
	(void)dist_to_door;
}

void texturing(t_map *map, double *top_buttom, double wall_height, double ray_angle)
{
	int	image_x;
	int	image_y;
	int	**img_pixels;
	mlx_image_t *img;
	int	i;

	i = (wall_height - WI_HEIGHT) / 2;
	if (i < 0)
		i = 0;                                                                                                                              
	img = get_dir_img(map, &img_pixels, ray_angle);
	image_x = get_x_image(map->ray.hit_x, map->ray.hit_y, map->ray.hit_line) * img->width;
	while(i < wall_height)
	{
		if (top_buttom[0] > WI_HEIGHT){
			break;
		}
		image_y = i / wall_height * img->height;
		if (top_buttom[0] >= 0 && (top_buttom[0] > MINI_HEIGHT || top_buttom[1] > MINI_WIDTH)){
			mlx_put_pixel(map->win_img.win_img, top_buttom[1], top_buttom[0], img_pixels[image_y][image_x]);
		}
		i++;
		top_buttom[0]++;
	}
}

void	draw_3D(t_map *map, double dis_to_wall, int color, double ray_angle)
{
	double	wall_heigth;
	double	dest;
	double start[2];
	static double 	i;

	if (ray_angle == (PLAYER_VIEW / 2) * -1)
		i = 0;
	dest = (double)(WI_WIDTH / 2) / tan((PLAYER_VIEW / 2) * M_PI / 180);
	// printf("dis to wall origin == %f, wall height == %f\n", dis_to_wall, wall_heigth);
	dis_to_wall *= cos(ray_angle * (M_PI / 180));
	wall_heigth = (WALL_HEIGHT / dis_to_wall) * (dest);
	// printf("dis to wall new one == %f, wall height == %f\n", dis_to_wall, wall_heigth);
	// printf("p == %f\n", p);
	start[0] = (WI_HEIGHT /  2) - (wall_heigth / 2); 
	if (start[0] < 0)
		start[0] = 0;
	start[1] = i;
	texturing(map, start, wall_heigth, ray_angle);
	if (map->door.hit_cord[0] != -1)
	{
		dis_to_wall = distance(map->player.cord, map->door.hit_cord);
		dis_to_wall *= cos(ray_angle * (M_PI / 180));
		
		if (dis_to_wall <= 80)
			map->door.timer_flag = true;
		if (map->door.timer_flag)
			map->door.timer++;
		if (map->door.timer == 100)
		{
			map->door.scop += map->win_img.door->height / 400;
			map->door.timer = 0;
		}
		if (map->door.scop > (int)map->win_img.door->height && dis_to_wall  >= 80 * 2)
		{
			// printf("dist to door = %f\n", dis_to_wall);
			map->door.scop = 0;
			map->door.timer_flag = false;
		}
		map->door.door_height = ((WALL_HEIGHT / dis_to_wall) * dest);
		start[0] = (WI_HEIGHT /  2) - (map->door.door_height / 2);
		door_texturing(map, start, map->door.door_height, dis_to_wall);
	}
	i += REC_WITH;
	(void) color;
}
