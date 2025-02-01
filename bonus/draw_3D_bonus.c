/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3D_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arekoune <arekoune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:39:42 by arekoune          #+#    #+#             */
/*   Updated: 2025/01/30 12:28:44 by arekoune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	{
		return(NULL);
	}
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

mlx_image_t *get_dir_img(t_map *map, int ***img_pixels, double ray_angle)
{
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
	if (img)
	{
		image_x = get_x_image(map->ray.hit_x, map->ray.hit_y, map->ray.hit_line) * img->width;
		while(i < wall_height)
		{
			if (top_buttom[0] > WI_HEIGHT)
				break;
			image_y = i / wall_height * img->height;
			if (top_buttom[0] >= 0 && (top_buttom[0] > MINI_HEIGHT || top_buttom[1] > MINI_WIDTH)){
				mlx_put_pixel(map->win_img.win_img, top_buttom[1], top_buttom[0], img_pixels[image_y][image_x]);
			}
			i++;
			top_buttom[0]++;
		}
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
	dis_to_wall *= cos(ray_angle * (M_PI / 180));
	wall_heigth = (WALL_HEIGHT / dis_to_wall) * (dest);
	start[0] = (WI_HEIGHT /  2) - (wall_heigth / 2); 
	if (start[0] < 0)
		start[0] = 0;
	start[1] = i;
	texturing(map, start, wall_heigth, ray_angle);
	door_status(map, dest, ray_angle, start);
	i += REC_WITH;
	(void) color;
}
