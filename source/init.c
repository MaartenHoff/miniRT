/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiler <adiler@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:30:16 by maahoff           #+#    #+#             */
/*   Updated: 2025/02/20 18:52:40 by adiler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	init_mlx_data(t_mlx_data **mlx_data)
{
	*mlx_data = malloc(sizeof(t_mlx_data));
	if (!(*mlx_data))
		return (1);
	(*mlx_data)->mlx = mlx_init();
	if (!(*mlx_data)->mlx)
		return (1);
	(*mlx_data)->win = mlx_new_window((*mlx_data)->mlx, WIDTH, HEIGHT,
			"miniRT");
	if (!(*mlx_data)->win)
		return (1);
	(*mlx_data)->img = mlx_new_image((*mlx_data)->mlx, WIDTH, HEIGHT);
	(*mlx_data)->addr = mlx_get_data_addr((*mlx_data)->img,
			&(*mlx_data)->bits_per_pixel, &(*mlx_data)->line_length,
			&(*mlx_data)->endian);
	return (0);
}