/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiler <adiler@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:29:43 by maahoff           #+#    #+#             */
/*   Updated: 2025/02/19 17:32:05 by adiler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	send_ray(t_mlx_data *mlx_data, t_map *map)
{
	if (mlx_data || map)
		return (0xFFFFFF);
	return (0);
}
