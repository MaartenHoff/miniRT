/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maahoff <maahoff@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:42:02 by maahoff           #+#    #+#             */
/*   Updated: 2025/02/16 20:19:08 by maahoff          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	init_data(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return (1);
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "miniRT");
	if (!data->win)
		return (1);
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->addr = mlx_get_data_addr(data->img, 
			&data->bits_per_pixel, &data->line_length, &data->endian);
	return (0);
}

void	fill_window(t_data *data)
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
			color = (0xFF << 16) | (0xFF * x / WIDTH);
			pixel = y * (data->line_length / 4) + x;
			*((int *)data->addr + pixel) = color;
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

int	main(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (init_data(data))
		return (1);
	fill_window(data);
	mlx_key_hook(data->win, key_hook, data);
	mlx_hook(data->win, 17, 0, close_window, data);
	mlx_loop(data->mlx);
	free(data->mlx);
	free(data);
	return (0);
}
