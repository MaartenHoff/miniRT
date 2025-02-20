/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maahoff <maahoff@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 19:57:28 by maahoff           #+#    #+#             */
/*   Updated: 2025/02/20 16:50:38 by maahoff          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	close_window(t_mlx_data *mlx_data)
{
	if (!mlx_data)
		return (0);
	if (mlx_data->img)
		mlx_destroy_image(mlx_data->mlx, mlx_data->img);
	if (mlx_data->win)
		mlx_destroy_window(mlx_data->mlx, mlx_data->win);
	if (mlx_data->mlx)
		mlx_destroy_display(mlx_data->mlx);
	if (mlx_data->mlx)
		free(mlx_data->mlx);
	free(mlx_data);
	exit (0);
}

int	key_hook(int key_code, t_mlx_data *mlx_data)
{
	if (key_code == ESC)
		return (close_window(mlx_data));
	return (0);
}
