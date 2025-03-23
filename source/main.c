#include "../includes/miniRT.h"

void	set_pixel(int color, t_mlx_data *mlx_data, int x, int y)
{
	int	pixel;

	pixel = y * mlx_data->line_length + x * (mlx_data->bits_per_pixel / 8);
	*(int *)(mlx_data->addr + pixel) = color;
}

void	fill_window(t_mlx_data *mlx_data, t_map *map)
{
	int			x;
	int			y;
	int			j;
	int			l;
	int			color;
	int			colors[4];
	int			color_temp;
	t_coords	direction;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			j = 0;
			while (j < 1)
			{
				l = 0;
				while (l < 1)
				{
					direction = get_direction(map, x, y);
					color_temp = send_ray(map, direction);
					color = 
				}
			}
			direction = get_direction(map, x, y);
			color = send_ray(map, direction);
			set_pixel(color, mlx_data, x, y);
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
	fill_window(mlx_data, map);
	free_map(map);
	mlx_key_hook(mlx_data->win, key_hook, mlx_data);
	mlx_hook(mlx_data->win, 17, 0, close_window, mlx_data);
	mlx_loop(mlx_data->mlx);
	return (0);
}
