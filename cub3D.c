# include "cub3D.h"
# include "MLX42/include/MLX42/MLX42.h"

int main ()
{
	mlx_t *mlx;
	mlx = mlx_init(1000, 800, "test", false);
	mlx_loop(mlx);
}
