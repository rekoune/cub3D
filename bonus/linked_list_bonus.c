/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arekoune <arekoune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:40:28 by arekoune          #+#    #+#             */
/*   Updated: 2025/02/01 13:54:18 by arekoune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

t_map_lst	*new_node(char *str)
{
	t_map_lst	*node;

	node = malloc(sizeof(t_map_lst));
	node->content = str;
	node->next = NULL;
	return (node);
}

void	add_back(t_map_lst **head, t_map_lst *new_node)
{
	t_map_lst	*node;

	node = *head;
	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	while (node->next)
		node = node->next;
	node->next = new_node;
}

int	ft_lstsize(t_map_lst *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

int	str_count(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

int	str_len(char *str, char c)
{
	int	i;

	i = 0;
	while (str && str[i] && str[i] != c)
		i++;
	return (i);
}
