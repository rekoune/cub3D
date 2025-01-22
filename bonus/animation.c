#include "cub3D_bonus.h"

char	*get_digit(long nb)
{
	char	str[12];
	char	*s;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (nb == 0)
		str[i++] = '0';
	while (nb)
	{
		str[i++] = (nb % 10) + 48;
		nb = nb / 10;
	}
	str[i] = '\0';
	s = malloc((str_len(str, '\0') + 1) * sizeof(char));
	i--;
	while (i >= 0)
	{
		s[j] = str[i];
		j++;
		i--;
	}
	s[j] = '\0';
	return (s);
}


mlx_image_t **get_textures(t_map *map, char *path, int  size)
{
    int i;
    mlx_image_t **img;
    char    *joined_path;
    char    *tmp;
    char    *n_str;

    img = malloc (sizeof(mlx_image_t *) * size + 1);
    i = 0;
    while (i < size)
    {
        n_str = get_digit(i);
        joined_path = str_join(path, n_str);
        tmp = joined_path;
        joined_path = str_join(joined_path, ".png");
        img[i] = get_image(map, map->mlx, joined_path);
        free(n_str);
        free(joined_path);
        free(tmp);
        i++;
    }
    img[i] = NULL;
    return (img);
}

void animation_init(t_map *map){
    map->animation.shotting = get_textures(map, "bonus/animation_textures/shotting/", 9); 
    map->animation.reloading = get_textures(map, "bonus/animation_textures/reloading/", 24);
    map->animation.running = get_textures(map, "bonus/animation_textures/running/", 5); 
    map->animation.standing = get_textures(map, "bonus/animation_textures/standing/", 17);
}

void add_images(mlx_t *mlx, mlx_image_t **imgs)
{
    int i;

    i = 0;
    while(imgs[i])
    {
        mlx_image_to_window(mlx, imgs[i], 400, 640);
        imgs[i]->enabled = false;
        i++;
    }
}

void    add_animation_img(t_map *map)
{
    add_images(map->mlx, map->animation.shotting);
    add_images(map->mlx, map->animation.reloading);
    add_images(map->mlx, map->animation.running);
    add_images(map->mlx, map->animation.standing);
}

void disable_images(mlx_image_t **images)
{
    int i;

    i = 0;
    while(images[i])
        images[i++]->enabled = false;
}

void    disable_all_images(t_map *map)
{
    disable_images(map->animation.shotting);
    disable_images(map->animation.reloading);
    disable_images(map->animation.running);
    disable_images(map->animation.standing);
}

void    animate_it(t_map *map , mlx_image_t **images, int timer, int num_frames, int frame_time)
{
    (void) num_frames;
    if (timer % frame_time == 0){
        disable_all_images(map);
        if (timer == frame_time * num_frames)
            images[0]->enabled = true;
        else 
            images[timer / frame_time]->enabled = true;
    }
}

void    draw_amo(t_map *map, int shott_num)
{
    char *str;

    str = get_digit(shott_num);
    if (map->animation.amo_img != NULL)
				draw_img(map->animation.amo_img, map->animation.amo_img->height, map->animation.amo_img->width, 0);
	map->animation.amo_img =  mlx_put_string(map->mlx, str, WI_WIDTH - 50, 10);
    free(str);
}

void animation(t_map *map)
{
    int num_frames;
    int frame_time;
    static int old_flag;

    frame_time = 3;
    num_frames = 0;
    
    if (old_flag != map->animation.flag)
    {
        old_flag = map->animation.flag;
        map->animation.timer = 0;
    }
    if (map->animation.flag == STANDING)
        animate_it(map, map->animation.standing, map->animation.timer, num_frames = 17, frame_time);
    else if (map->animation.flag == RUNNING)
        animate_it(map, map->animation.running, map->animation.timer, num_frames = 5, 4);
    else if (map->animation.flag == SHOTTING)
        animate_it(map, map->animation.shotting, map->animation.timer, num_frames = 9, frame_time);
    else if (map->animation.flag == RELOADING)
        animate_it(map, map->animation.reloading, map->animation.timer, num_frames = 24, frame_time);

    if (map->animation.timer == num_frames * frame_time)
        map->animation.timer  = -1; 
    map->animation.timer++;
}
