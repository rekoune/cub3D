/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haouky <haouky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:59:48 by haouky            #+#    #+#             */
/*   Updated: 2025/01/21 13:00:18 by haouky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
