/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maahoff <maahoff@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 11:13:22 by maahoff           #+#    #+#             */
/*   Updated: 2025/03/24 11:13:23 by maahoff          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/miniRT.h"

t_coords	vec_mul(t_coords vector, double scalar)
{
	t_coords	scaled;

	scaled.x = vector.x * scalar;
	scaled.y = vector.y * scalar;
	scaled.z = vector.z * scalar;
	return (scaled);
}

double	point_distance(t_coords point1, t_coords point2)
{
	t_coords	vector;
	double		distance;

	vector = vec_create(point1, point2);
	distance = vec_len(vector);
	if (distance < 0)
		distance *= -1;
	return (distance);
}

t_coords	vec_cross(t_coords vector1, t_coords vector2)
{
	t_coords	result;

	result.x = vector1.y * vector2.z - vector1.z * vector2.y;
	result.y = vector1.z * vector2.x - vector1.x * vector2.z;
	result.z = vector1.x * vector2.y - vector1.y * vector2.x;
	return (result);
}

t_coords	vec_sub(t_coords point1, t_coords point2)
{
	t_coords	vector;

	vector.x = point1.x - point2.x;
	vector.y = point1.y - point2.y;
	vector.z = point1.z - point2.z;
	return (vector);
}
