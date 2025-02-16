/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maahoff <maahoff@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:42:02 by maahoff           #+#    #+#             */
/*   Updated: 2025/02/16 19:47:44 by maahoff          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"
#include "../includes/structs.h"

int	init_window(t_window *window)
{
	window->mlx = mlx_init();
	if (!window->mlx)
		return (1);
	window->win = mlx_new_window(window->mlx, WIDTH, HEIGHT, "miniRT");
	if (!window->win)
		return (1);
	window->img = mlx_new_image(window->mlx, WIDTH, HEIGHT);
	window->addr = mlx_get_data_addr(window->img, 
			&window->bits_per_pixel, &window->line_length, &window->endian);
	return (0);
}

void	fill_window(t_window *window)
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
			pixel = y * (window->line_length / 4) + x;
			*((int *)window->addr + pixel) = color;
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(window->mlx, window->win, window->img, 0, 0);
}

int	main(void)
{
	t_window	*window;

	window = malloc(sizeof(t_window));
	if (init_window(window))
		return (1);
	fill_window(window);
	mlx_key_hook(window->win, (void *)exit, NULL);
	mlx_loop(window->mlx);
	free(window->mlx);
	free(window);
	return (0);
}
