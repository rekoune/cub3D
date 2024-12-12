/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haouky <haouky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 08:34:05 by haouky            #+#    #+#             */
/*   Updated: 2024/12/12 12:06:50 by haouky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void setder(double angel, int *der)
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

void h_hit(double *hitp, int *der, t_player player, double angel)
{
    if(der[0] == -1)
        hitp[0] = (player.cord[0] / TAILE_SIZE) * TAILE_SIZE - 1;
    else if(der[0] == 1)
         hitp[0] = (player.cord[0] / TAILE_SIZE) * TAILE_SIZE + TAILE_SIZE;
    hitp[1] = ((hitp[0] - player.cord[0]) / tan(angel)) + player.cord[1];
}

void v_hit(double *hitp, int *der, t_player player, double angel)
{
    if(der[1] == -1)
        hitp[1] = (player.cord[1] / TAILE_SIZE) * TAILE_SIZE - 1;
    else if(der[1] == 1)
         hitp[1] = (player.cord[1] / TAILE_SIZE) * TAILE_SIZE + TAILE_SIZE;
    hitp[0] = player.cord[0] + (player.cord[1] - hitp[1]) * tan(angel);
}
int valid_P(double *hitp, char **map, double *size)
{   
    if(hitp[0] < 0 || hitp[1] < 0 || (hitp[0] / TAILE_SIZE) > (size[0] - 1)|| (hitp[1] / TAILE_SIZE) > size[1])
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
    int yx; 

    setder(angel, der);
    // printf("A1|========================================|\n");
    // printf("angel %f, der[0] = %f , der[1] = %f \n",angel, der[0], der[1]);
    
    angel = angel * (M_PI / 180);
    // printf("p.y %f p.x %f\n",map->player.cord[0], map->player.cord[1]);
    v_hit(hitpv, der, map->player, angel);
    // printf("Fv : y = %f | x = %f\n",hitpv[0], hitpv[1]);
    yx = (TAILE_SIZE * der[1]) * tan(angel);
    while(valid_P(hitpv, map->map_content, map->map_max_size))
    {
       hitpv[0]  += yx;  
       hitpv[1] += (TAILE_SIZE * der[1]);
    }
    // printf(" V : y = %f | x = %f\n",hitpv[0], hitpv[1]);
    // printf("A2|========================================|\n");
    h_hit(hitph, der, map->player, angel);
    yx = (TAILE_SIZE * der[0]) / tan(angel);
    // printf("FH : y = %f | x = %f | yx = %f\n",hitph[0], hitph[1], yx);
    while(valid_P(hitph, map->map_content, map->map_max_size))
    {
       hitph[0] += (TAILE_SIZE * der[0]);
       hitph[1]  += yx;
    }
    // printf(" H : y = %f | x = %f\n",hitph[0], hitph[1]);
    printf("A3|========================================|\n");
    if((hitph[0] == -1 || distance(map->player.cord, hitph) > distance(map->player.cord, hitpv)) && hitpv[0] != -1)
        return (hitpv);
    else
        return (hitph);
}
void caster(t_map *map)
{
    double hitph[2];
    double hitpv[2];
    static double player[2] = {0,0};
    static double xy[2] = {0,0};
    double *hitp;
    
    hitp = hitpoint(map , map->player.angel, hitph, hitpv);
    draw_line(map->mini_img.cover,player, xy,create_trgb(255,255,255,0));
    player[0] = map->mini_img.player->instances->y;
    player[1] = map->mini_img.player->instances->x;
    xy[0] = player[0] + (hitp[0] - map->player.cord[0]);
    xy[1] = player[1] + (hitp[1] - map->player.cord[1]);
    draw_line(map->mini_img.cover,player, xy,create_trgb(255,0,0,255));
    printf("x%f, y %f\n", xy[1], xy[0]);
    printf("HH : y = %f | x = %f\n",hitph[0] , hitph[1] );
    printf("VV  : y = %f | x = %f\n",hitpv[0] , hitpv[1] );
    // printf("***player y = %f x = %f\n", player[0] , player[1] ); 75 150
}