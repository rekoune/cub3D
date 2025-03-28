/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arekoune <arekoune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:51:32 by haouky            #+#    #+#             */
/*   Updated: 2025/02/03 12:20:09 by arekoune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static int	cw(char const *s, char c)
{
	int	i;
	int	ct;
	int	n;

	i = 0;
	ct = 0;
	n = 1;
	while (s[i] != 0)
	{
		if (s[i] == c)
			n = 1;
		if (s[0] == c || (s[i] == c && (s[i + 1] == c || s[i + 1] == '\0')))
			exit(ft_write("Error: Invalid Color arguments\n", 1));
		if (s[i] != c && n == 1)
		{
			ct++;
			n = 0;
		}
		i++;
	}
	return (ct);
}

static int	lenw(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != 0 && s[i] != c)
		i++;
	return (i);
}

void	fr(char **s, int i)
{
	while (i >= 0)
		free(s[i--]);
	free(s);
}

static char	**msp(char **str, char *s, int word, char c)
{
	int	i;

	i = 0;
	while (i < word)
	{
		while (*s == c)
			s++;
		str[i] = str_dup(s, 0, lenw(s, c));
		if (str[i] == 0)
		{
			fr(str, i);
			return (0);
		}
		s += lenw(s, c);
		i++;
	}
	str[i] = 0;
	return (str);
}

char	**ft_split(char *s, char c)
{
	char	**str;
	int		word;

	if (!s)
		return (NULL);
	word = cw(s, c);
	str = malloc((word + 1) * sizeof(char *));
	if (str == NULL)
		return (NULL);
	return (msp(str, s, word, c));
}
