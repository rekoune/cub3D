/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haouky <haouky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 08:34:05 by haouky            #+#    #+#             */
/*   Updated: 2024/12/19 11:34:52 by haouky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void set_derction(double angel, int *der)
{
    if(angel > 180 && angel < 360)
       der[0] = -1;
    else
        der[0] = 1;
    if(angel > 90 && angel < 270)
        der[1] = -1;
    else
        der[1] = 1;
}

double normalize_angel(double angel)
{
    if(angel < 0)
			angel += 360;
    if(angel >= 360)
			angel -= 360;
    return (angel);
}

void horizontal_hit(double *hitp, int *der, t_player player, double angel)
{
    if(der[0] == -1)
        hitp[0] = floor(player.cord[0] / TAILE_SIZE) * TAILE_SIZE - 0.0001;
    else if(der[0] == 1)
         hitp[0] = floor(player.cord[0] / TAILE_SIZE) * TAILE_SIZE + TAILE_SIZE + 0.0001;
    if(der[1] == 1)
        hitp[1] = player.cord[1] + fabs(((hitp[0] - player.cord[0]) / tan(angel)));
    else
        hitp[1] = player.cord[1] - fabs(((hitp[0] - player.cord[0]) / tan(angel)));
}

void victical_hit(double *hitp, int *der, t_player player, double angel)
{
    if(der[1] == -1)
        hitp[1] = floor(player.cord[1] / TAILE_SIZE) * TAILE_SIZE - 0.0001;
    else if(der[1] == 1)
         hitp[1] = floor(player.cord[1] / TAILE_SIZE) * TAILE_SIZE + TAILE_SIZE + 0.0001;
    if(der[0] == 1)
        hitp[0] = player.cord[0] + fabs((player.cord[1] - hitp[1]) * tan(angel));
    else
        hitp[0] = player.cord[0] - fabs((player.cord[1] - hitp[1]) * tan(angel));
}
int valid_Point(double *hitp, char **map, int *size)
{   
    printf("size[0] = %d size[1] = %d |hitp[0] = %f hitp[1] = %f\n",size[0], size[1],hitp[0]/ TAILE_SIZE, hitp[1]/ TAILE_SIZE);
    if(isinf(hitp[0]) || isinf(hitp[1]) || hitp[0] < 0 || hitp[1] < 0 || (hitp[0] / TAILE_SIZE) > (size[0])|| (int)(hitp[1] / TAILE_SIZE) > (size[1]))
    {
        hitp[0] = -1;
    }
    if(hitp[0] == -1 || map[(int)(hitp[0] / TAILE_SIZE)][(int)(hitp[1] / TAILE_SIZE)] == '1')
    {
        return (0);
    }
    return (1);
}

double  *hitpoint(t_map *map,double angel,double *hitph,double  *hitpv)
{
    int der[2];
    double yx;

    set_derction(angel, der);
    printf("V1|========================================|\n");
    angel *= (M_PI / 180); 
    victical_hit(hitpv, der, map->player, angel); 
    yx = (TAILE_SIZE * der[1]) * tan(angel);
    while(valid_Point(hitpv, map->map_content, map->map_max_size)) 
    {
        if(der[0] == 1)
            hitpv[0]  += fabs(yx);
        else
            hitpv[0]  -= fabs(yx);  
        hitpv[1] += (TAILE_SIZE * der[1]);
    }
    printf("H2|========================================|\n");
    horizontal_hit(hitph, der, map->player, angel); 
    yx = (TAILE_SIZE * der[0]) / tan(angel);
    while(valid_Point(hitph, map->map_content, map->map_max_size)) 
    {
       hitph[0] += (TAILE_SIZE * der[0]);
        if(der[1] == 1)
            hitph[1]  += fabs(yx);
        else
            hitph[1]  -= fabs(yx);
    }
    printf("A3|========================================|\n");
    printf("dir[0]  = %d der[1] = %d \n",der[0], der[1]);
    printf("angel %f\n", map->player.angel);
    if(hitpv[0] != -1 && (hitph[0] == -1 || distance(hitph, map->player.cord) > distance(hitpv,map->player.cord)))
        return (hitpv);
    else
        return (hitph);
}

void caster(t_map *map)
{
    double hitph[2];
    double hitpv[2];
    double player[2];
    double xy[2];
    double *hitp;
    int i = -30;
    draw_img(map->mini_img.cover,MINI_HEIGHT, MINI_WIDTH,0 | 0 | 0| 0);
    while (i < 30)
    {
    hitp = hitpoint(map , normalize_angel(map->player.angel + i), hitph, hitpv);
    player[0] = map->mini_img.player->instances->y;
    player[1] = map->mini_img.player->instances->x;
    xy[0] = player[0] + (hitp[0] - map->player.cord[0]);
    xy[1] = player[1] + (hitp[1] - map->player.cord[1]);
    draw_line(map->mini_img.cover,player, xy,create_trgb(50,0,200,255));
    printf("prcord y = %f x = %f |/tailsize| y = %f x = %f\n", map->player.cord[0],  map->player.cord[1],map->player.cord[0] / TAILE_SIZE, map->player.cord[1] / TAILE_SIZE);
    printf("draw |y%f, x %f\n", xy[0], xy[1]);
    printf("HH : y = %f | x = %f / tz => y = %f x = %f\n",hitph[0] , hitph[1], hitph[0] / TAILE_SIZE , hitph[1] / TAILE_SIZE );
    printf("VV  : y = %f | x = %f / tz => y = %f x = %f\n",hitpv[0] , hitpv[1],  hitpv[0] / TAILE_SIZE , hitpv[1] / TAILE_SIZE);
    printf("Hitp[0] = %f hitp[1] = %f\n",hitp[0], hitp[1]);
    i++;
    }
}