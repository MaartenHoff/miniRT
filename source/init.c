/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maahoff <maahoff@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:30:16 by maahoff           #+#    #+#             */
/*   Updated: 2025/02/19 16:48:15 by maahoff          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	init_mlx_data(t_mlx_data *mlx_data)
{
	mlx_data = malloc(sizeof (t_mlx_data));
	if (!mlx_data)
		return (1);
	mlx_data->mlx = mlx_init();
	if (!mlx_data->mlx)
		return (1);
	mlx_data->win = mlx_new_window(mlx_data->mlx, WIDTH, HEIGHT, "miniRT");
	if (!mlx_data->win)
		return (1);
	mlx_data->img = mlx_new_image(mlx_data->mlx, WIDTH, HEIGHT);
	mlx_data->addr = mlx_get_data_addr(mlx_data->img, 
			&mlx_data->bits_per_pixel, 
			&mlx_data->line_length, &mlx_data->endian);
	return (0);
}

int	init_map(t_map **map, int argc, char **argv)
{
	if (!argc || !argv)
		return (1);
	*map = malloc(sizeof(t_map));
	if (!map)
		return (ERR_NOMEM);
	(*map)->light = NULL;
	(*map)->objects = NULL;
	return (0);
}

int	init(t_mlx_data *mlx_data, t_map **map, int argc, char **argv)
{
	int	error_check;

	error_check = init_mlx_data(mlx_data);
	if (error_check)
		return (error_check);
	error_check = init_map(map, argc, argv);
	if (error_check)
	{
		free(mlx_data->mlx);
		return (free(mlx_data), error_check);
	}
	return (0);
}
