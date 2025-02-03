/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arekoune <arekoune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:40:51 by arekoune          #+#    #+#             */
/*   Updated: 2025/02/03 12:06:40 by arekoune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D_bonus.h"

bool	str_comp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (false);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (s1[i] != s2[i])
		return (false);
	return (true);
}

int	ft_write(char *str, int rtrn)
{
	int	i;

	i = 0;
	while (str[i])
		write(2, &str[i++], 1);
	return (rtrn);
}

char	*str_dup(char *str, int start, int size)
{
	char	*dup_str;
	int		i;

	i = 0;
	dup_str = malloc(sizeof(char) * (size + 1));
	while (i < size && str[i])
	{
		dup_str[i] = str[start];
		i++;
		start++;
	}
	dup_str[i] = '\0';
	return (dup_str);
}

char	*str_join(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = malloc((str_len(s1, '\0') + str_len(s2, '\0') + 1) * sizeof(char));
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}

long	ft_atoi(char *str)
{
	int		i;
	long	nb;

	i = 0;
	nb = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '\0')
		exit(ft_write("Error: Invalid Color argument\n", 1));
	while (str[i])
	{
		if ((str[i] > '9' || str[i] < '0') && str[i] != ' ')
			exit(ft_write("Error: Invalid Color argument\n", 1));
		nb = nb * 10;
		nb = nb + (str[i++] - 48);
		while (str[i] == ' ')
		{
			if (str[i + 1] != '\0' && str[i + 1] != ' ')
				exit(ft_write("Error: Invalid Color argument\n", 1));
			i++;
		}
	}
	if (nb > 255)
		exit(ft_write("Error: Invalid Color argument\n", 1));
	return (nb);
}
