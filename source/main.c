/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiler <adiler@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:42:02 by maahoff           #+#    #+#             */
/*   Updated: 2025/02/19 17:29:29 by adiler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	fill_window(t_mlx_data *mlx_data)
{
	int	x;
	int	y;
	int	color;
	int	pixel;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			// color = send_ray(mlx_data, map);
			color = 0xFFFFF0;
			pixel = y * mlx_data->line_length + x * (mlx_data->bits_per_pixel / 8);
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

	mlx_data = NULL;
	map = NULL;
	if (init(&mlx_data, &map, argc, argv))
		return (1);
	fill_window(mlx_data);
	mlx_key_hook(mlx_data->win, key_hook, mlx_data);
	mlx_hook(mlx_data->win, 17, 0, close_window, mlx_data);
	mlx_loop(mlx_data->mlx);
	free(mlx_data->mlx);
	free(mlx_data);
	free(map);
	return (0);
}
