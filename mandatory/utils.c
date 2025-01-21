/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haouky <haouky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 13:40:10 by haouky            #+#    #+#             */
/*   Updated: 2025/01/21 14:01:52 by haouky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	str_len(char *str, char c)
{
	int	i;

	i = 0;
	while (str && str[i] && str[i] != c)
		i++;
	return (i);
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

int	str_count(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
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
