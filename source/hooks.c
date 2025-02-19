/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maahoff <maahoff@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 19:57:28 by maahoff           #+#    #+#             */
/*   Updated: 2025/02/19 16:29:23 by maahoff          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	close_window(t_mlx_data *mlx_data)
{
	mlx_destroy_window(mlx_data->mlx, mlx_data->win);
	free(mlx_data->mlx);
	free(mlx_data);
	exit(0);
}

int	key_hook(int key_code, t_mlx_data *mlx_data)
{
	if (key_code == ESC)
		close_window(mlx_data);
	return (0);
}
