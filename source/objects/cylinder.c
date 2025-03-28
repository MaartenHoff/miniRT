/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maahoff <maahoff@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 11:16:24 by maahoff           #+#    #+#             */
/*   Updated: 2025/03/24 11:16:25 by maahoff          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_hit	circle_hit(t_planes *plane, double radius, t_coords origin,
		t_coords direction)
{
	t_hit	hit;
	double	distance;

	hit.distance = -1;
	plane_hit(plane, origin, direction, &hit);
	if (hit.distance < 0)
		return (hit);
	distance = vec_len(vec_create(hit.point, plane->point));
	if (distance > radius)
		hit.distance = -1;
	return (hit);
}

t_hit	get_mantle_hit(t_cylinder *cylinder, t_coords origin, 
	t_coords direction)
{
	t_hit	hit;
	double	distance;

	hit.color = cylinder->color;
	hit.normal = (t_coords){0, 0, 0};
	hit.point = (t_coords){0, 0, 0};
	distance = mantle_intersection(cylinder, origin, direction);
	if (distance < 0)
	{
		hit.distance = -1;
		return (hit);
	}
	hit.distance = distance;
	hit.point = vec_add(origin, vec_mul(direction, distance));
	if (vec_skalar(vec_create(cylinder->base, hit.point), cylinder->vector) > 
		cylinder->height || vec_skalar(vec_create(cylinder->base, hit.point), 
			cylinder->vector) < 0)
		hit.distance = -1;
	return (hit);
}

void	get_normal(t_cylinder *cylinder, t_coords hit, t_coords *normal)
{
	t_coords	proj;

	proj = vec_mul(cylinder->vector, vec_skalar(
				vec_create(cylinder->base, hit), cylinder->vector));
	*normal = vec_sub(vec_create(cylinder->base, hit), proj);
}

double	distance_to_cylinder(t_cylinder *cylinder, t_coords origin,
		t_coords direction, t_coords *normal)
{
	t_hit		circle1_hit;
	t_hit		circle2_hit;
	t_hit		mantle_hit;
	double		t;

	circle1_hit = circle_hit(cylinder->plane1, cylinder->radius, origin,
			direction);
	circle2_hit = circle_hit(cylinder->plane2, cylinder->radius, origin,
			direction);
	mantle_hit = get_mantle_hit(cylinder, origin, direction);
	t = get_lowest_but_positve_t(circle1_hit.distance, circle2_hit.distance,
			mantle_hit.distance);
	if (t < 0)
		return (-1);
	if (t == circle1_hit.distance || t == circle2_hit.distance)
		*normal = cylinder->vector;
	else
	{
		get_normal(cylinder, mantle_hit.point, normal);
		*normal = vec_norm(*normal);
	}
	return (t);
}

int	cylinder_hit(t_cylinder *cylinder, t_coords origin, 
	t_coords direction,	t_hit *hit)
{
	double		t;
	t_coords	normal;

	t = -1;
	normal = (t_coords){0, 0, 0};
	t = distance_to_cylinder(cylinder, origin, direction, &normal);
	if (t < 0)
		return (0);
	hit->point = vec_add(origin, vec_mul(direction, t));
	hit->distance = t;
	hit->color = cylinder->color;
	if (vec_skalar(direction, normal) > 0)
		normal = vec_mul(normal, -1);
	hit->normal = normal;
	return (0);
}
