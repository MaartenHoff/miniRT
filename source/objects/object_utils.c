/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maahoff <maahoff@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 11:23:46 by maahoff           #+#    #+#             */
/*   Updated: 2025/03/24 11:23:47 by maahoff          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

double	solve_quadratic(double a, double b, double c)
{
	double	discriminant;
	double	sqrt_discriminant;
	double	t1;
	double	t2;

	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (-1);
	sqrt_discriminant = sqrt(discriminant);
	t1 = (-b + sqrt_discriminant) / (2 * a);
	t2 = (-b - sqrt_discriminant) / (2 * a);
	if (t1 >= 0 && t2 >= 0)
	{
		if (t1 < t2)
			return (t1);
		return (t2);
	}
	if (t1 >= 0)
		return (t1);
	if (t2 >= 0)
		return (t2);
	return (-1);
}

double	get_lowest_but_positve_t(double plane1_t, double plane2_t,
	double mantle_t)
{
	double	min_t;

	min_t = -1;
	if (plane1_t > 0 && (min_t < 0 || plane1_t < min_t))
		min_t = plane1_t;
	if (plane2_t > 0 && (min_t < 0 || plane2_t < min_t))
		min_t = plane2_t;
	if (mantle_t > 0 && (min_t < 0 || mantle_t < min_t))
		min_t = mantle_t;
	return (min_t);
}

double	mantle_intersection(t_cylinder *cylinder, t_coords origin,
	t_coords direction)
{
	double		a;
	double		b;
	double		c;
	t_coords	q;
	t_coords	u;

	q = vec_sub(vec_create(cylinder->base, origin), vec_mul(cylinder->vector, 
				vec_skalar(vec_create(cylinder->base, origin), 
					cylinder->vector)));
	u = vec_sub(direction, vec_mul(cylinder->vector, vec_skalar(direction, 
					cylinder->vector)));
	a = vec_skalar(u, u);
	b = 2 * vec_skalar(u, q);
	c = vec_skalar(q, q) - cylinder->radius * cylinder->radius;
	return (solve_quadratic(a, b, c));
}
