/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maahoff <maahoff@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:29:43 by maahoff           #+#    #+#             */
/*   Updated: 2025/02/19 16:32:30 by maahoff          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	send_ray(t_mlx_data *mlx_data, t_map *map)
{
	if (mlx_data || map)
		return (0xFFFFFF);
	return (0);
}
