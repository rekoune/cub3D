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
	t_map_lst *node;

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