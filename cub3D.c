#include "cub3D.h"

void	leaks(void)
{
	system("leaks -q cub3D");
}

int	main(int ac, char **av)
{
	t_map		*map;
	int			i;

	i = 0;
	atexit(leaks);
	if (ac != 2)
		return (printf("ERROR : Invalid arguments\n"), 1);
	map = checking_map(av[1]);
	printf("south = %s\n", map->directions.south);
	printf("north = %s\n", map->directions.north);
	printf("east = %s\n", map->directions.east);
	printf("west = %s\n", map->directions.west);
	while (i < 3)
		printf("F = %d ", map->colors.floor[i++]);
	printf("\n");
	i = 0;
	while (i < 3)
		printf("C = %d ", map->colors.ceiling[i++]);
	printf("\n");
	i = 0;
	while(map->map_content[i])
		printf("%s\n", map->map_content[i++]);
	free_resources(map);
}
