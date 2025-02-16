/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maahoff <maahoff@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 19:57:28 by maahoff           #+#    #+#             */
/*   Updated: 2025/02/16 20:33:40 by maahoff          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	close_window(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	free(data->mlx);
	free(data);
	exit(0);
}

int	key_hook(int key_code, t_data *data)
{
	if (key_code == ESC)
		close_window(data);
	return (0);
}
