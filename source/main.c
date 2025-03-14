#include "../includes/miniRT.h"

void	fill_window(t_mlx_data *mlx_data, t_map *map)
{
	int	x;
	int	y;
	int	color;
	int	pixel;

	y = 0;
	(void)map;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			color = send_ray(mlx_data, map);
			pixel = y * mlx_data->line_length + x * 
				(mlx_data->bits_per_pixel / 8);
			mlx_data->addr[pixel] = color;
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx_data->mlx, mlx_data->win, mlx_data->img, 0, 0);
}

int	main(int argc, char **argv)
{
	t_mlx_data	*mlx_data;
	t_map		*map;
	int			error_check;

	mlx_data = NULL;
	map = NULL;
	error_check = parser(&mlx_data, &map, argc, argv);
	if (error_check)
		return (handle_error(error_check, map));
	print_map(map);
	fill_window(mlx_data, map);
	free_map(map);
	mlx_key_hook(mlx_data->win, key_hook, mlx_data);
	mlx_hook(mlx_data->win, 17, 0, close_window, mlx_data);
	mlx_loop(mlx_data->mlx);
	return (0);
}
