/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haouky <haouky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 08:34:05 by haouky            #+#    #+#             */
/*   Updated: 2024/12/11 08:34:19 by haouky           ###   ########.fr       */
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

void h_hit(int *hitp, int *der, t_player player, double angel)
{
    if(der[0] == -1)
        hitp[0] = (player.y / TAILE_SIZE) * TAILE_SIZE - 1;
    else if(der[0] == 1)
         hitp[0] = (player.y / TAILE_SIZE) * TAILE_SIZE + TAILE_SIZE;
    hitp[1] = ((hitp[0] - player.y) / tan(angel)) + player.x;
}

void v_hit(int *hitp, int *der, t_player player, double angel)
{
    if(der[1] == -1)
        hitp[1] = (player.x / TAILE_SIZE) * TAILE_SIZE - 1;
    else if(der[1] == 1)
         hitp[1] = (player.x / TAILE_SIZE) * TAILE_SIZE + TAILE_SIZE;
    hitp[0] = player.y + (player.x - hitp[1]) * tan(angel);
}
int valid_P(int *hitp, char **map, int *size)
{
    if(hitp[0] < 0 || hitp[1] < 0 || (hitp[0] / TAILE_SIZE) > size[0] - 1|| (hitp[1] / TAILE_SIZE) > size[1])
    {
        printf("|in|\n\n");
        hitp[0] = -1;
    }
    printf("*-> p[0] = %d p[1] = %d siz[0] = %d sz[1] %d\n", hitp[0] / TAILE_SIZE, hitp[1] / TAILE_SIZE, size[0], size[1]);
    if(hitp[0] == -1 || map[(hitp[0] / TAILE_SIZE)][(hitp[1] / TAILE_SIZE)] == '1')
        return (0);
    return (1);
    printf("done\n");
}

void hitpoint(t_map *map,double angel,int *hitph,int  *hitpv)
{
    int der[2];
    int yx; 

    setder(angel, der);
    printf("A1|========================================|\n");
    printf("angel %f, der[0] = %d , der[1] = %d \n",angel, der[0], der[1]);
    
    angel = angel * (M_PI / 180);
    printf("p.y %f p.x %f\n",map->player2.y, map->player2.x);
    v_hit(hitpv, der, map->player2, angel);
    printf("Fv : y = %d | x = %d\n",hitpv[0], hitpv[1]);
    yx = (TAILE_SIZE * der[1]) * tan(angel);
    while(valid_P(hitpv, map->map_content, map->map_max_size))
    {
       hitpv[0]  += yx;  
       hitpv[1] += (TAILE_SIZE * der[1]);
    }
    printf(" v : y = %d | x = %d\n",hitpv[0], hitpv[1]);
    printf("A2|========================================|\n");
    h_hit(hitph, der, map->player2, angel);
    yx = (TAILE_SIZE * der[0]) / tan(angel);
    printf("FH : y = %d | x = %d | yx = %d\n",hitph[0], hitph[1], yx);
    while(valid_P(hitph, map->map_content, map->map_max_size))
    {
       hitph[0] += (TAILE_SIZE * der[0]);
       hitph[1]  += yx;
    }
    printf(" H : y = %d | x = %d\n",hitph[0], hitph[1]);
    printf("A3|========================================|\n");
}
void caster(t_map *map)
{
    int hitph[2];
    int hitpv[2];
    
    hitpoint(map, map->player2.angel, hitph, hitpv);
    printf("HH : y = %d | x = %d\n",hitph[0] / TAILE_SIZE, hitph[1] / TAILE_SIZE);
    printf("VV  : y = %d | x = %d\n",hitpv[0] / TAILE_SIZE, hitpv[1] / TAILE_SIZE);
}