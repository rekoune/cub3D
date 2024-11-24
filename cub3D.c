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
	draw_mini_map(map);
	free_resources(map);
}
