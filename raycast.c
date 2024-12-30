/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haouky <haouky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 08:34:05 by haouky            #+#    #+#             */
/*   Updated: 2024/12/30 09:55:19 by haouky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

double  *hitpoint(t_map *map,double angel,double *hitph,double  *hitpv)
{
    int der[2];
    double yx;

    set_derction(angel, der);
    // printf("V1|========================================|\n");
    angel *= (M_PI / 180); 
    victical_hit(hitpv, der, map->player, angel); 
    yx = (TAILE_SIZE * der[1]) * tan(angel);
    while(valid_Point(hitpv, map->map_content, map->map_max_size)) 
    {
        hitpv[0]  += fabs(yx) * der[0];
        hitpv[1] += (TAILE_SIZE * der[1]);
    }
    // printf("H2|========================================|\n");
    horizontal_hit(hitph, der, map->player, angel); 
    yx = (TAILE_SIZE * der[0]) / tan(angel);
    while(valid_Point(hitph, map->map_content, map->map_max_size)) 
    {
        hitph[0] += (TAILE_SIZE * der[0]);
        hitph[1]  += fabs(yx) * der[1];
    }
    // printf("A3|=========/===============================|\n");
    // printf("dir[0]  = %d der[1] = %d \n",der[0], der[1]);
    // printf("angel %f\n", map->player.angel);
    if(hitpv[0] != -1 && (hitph[0] == -1 || distance(hitph, map->player.cord) > distance(hitpv,map->player.cord)))
    {
        map->color_test = create_trgb(245, 222, 179, 255);
        return (hitpv);
    }
    else{
        map->color_test = create_trgb(169, 169, 169, 255);
        return (hitph);
    }
}
void raycaster(t_map *map,double angleshift, double *hitph, double *hitpv)
{
    double player[2];
    double xy[2];
    double *hitp;
    
    hitp = hitpoint(map , normalize_angel(map->player.angel + angleshift), hitph, hitpv);
    player[0] = map->mini_img.player->instances->y + (PLAYER_SIZE / 2);
    player[1] = map->mini_img.player->instances->x + (PLAYER_SIZE / 2);
    xy[0] = player[0] + (hitp[0] - map->player.cord[0]);
    xy[1] = player[1] + (hitp[1] - map->player.cord[1]);
    draw_line(map->mini_img.cover,player, xy,create_trgb(255,0,0,255));
    draw_3D(map, distance(map->player.cord, hitp), map->color_test,angleshift);
}
void caster(t_map *map)
{
    double hitph[2];
    double hitpv[2];
    double i;
    
    i = (PLAYER_VIEW / 2) * -1;
    draw_img(map->win_img.win_img, WI_HEIGHT, WI_WIDTH, create_trgb(0,0,0,0));
    draw_img(map->mini_img.cover, MINI_HEIGHT, MINI_WIDTH, create_trgb(0,0,0,0));
    while (i < (PLAYER_VIEW / 2))
    {    
        raycaster(map, i, hitph, hitpv);
        i += RES;
    }
}
