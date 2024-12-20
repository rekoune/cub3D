#include "cub3D.h"

void	free_2d(char **str, char *str2)
{
	int	i;

	i = 0;
	if (str2)
		free(str2);
	while (str && str[i])
		free(str[i++]);
	free(str);
}

void	free_list(t_map_lst *map)
{
	t_map_lst	*node;

	while (map)
	{
		node = map->next; 
		free(map);
		map = node;
	}
}

void	free_resources(t_map *map)
{
	free_2d(map->map_content, NULL);
	free(map->directions.east);
	free(map->directions.west);
	free(map->directions.north);
	free(map->directions.south);
	free(map);
}
