#include "../../includes/miniRT.h"

double	mantle_intersection(t_cylinder *cylinder, t_coords origin,
		t_coords direction)
{
	double		a;
	double		b;
	double		c;
	t_coords	B;
	t_coords	u;

	B = vec_sub(vec_create(cylinder->base, origin), vec_mul(cylinder->vector, 
		vec_skalar(vec_create(cylinder->base, origin), cylinder->vector)));
	u = vec_sub(direction, vec_mul(cylinder->vector, vec_skalar(direction, 
		cylinder->vector)));
	a = vec_skalar(u, u);
	b = 2 * vec_skalar(u, B);
	c = vec_skalar(B, B) - cylinder->radius * cylinder->radius;
	return (solve_quadratic(a, b, c));
}

double	get_lowest_but_positve_t(double plane1_t, double plane2_t,
		double mantle_t)
{
	double min_t;

	min_t = -1;
	if (plane1_t > 0 && (min_t < 0 || plane1_t < min_t))
		min_t = plane1_t;
	if (plane2_t > 0 && (min_t < 0 || plane2_t < min_t))
		min_t = plane2_t;
	if (mantle_t > 0 && (min_t < 0 || mantle_t < min_t))
		min_t = mantle_t;
	return min_t;
}

t_hit	circle_hit(t_planes *plane, double radius, t_coords origin,
		t_coords direction)
{
	t_hit	hit;
	double	distance;

	plane_hit(plane, origin, direction, &hit);
	if (hit.distance < -1)
		return (hit);
	distance = vec_len(vec_create(hit.point, plane->point));
	if (distance > radius)
		hit.distance = -1;
	return (hit);
}


void	get_normal(t_cylinder *cylinder, t_coords hit, t_coords *normal)
{
	t_coords	proj;

	proj = vec_mul(cylinder->vector, vec_skalar(vec_create(cylinder->base, hit), cylinder->vector));
	*normal = vec_create(vec_create(cylinder->base, hit), proj);
}

int	distance_to_cylinder(t_cylinder *cylinder, t_coords origin,
		t_coords direction, t_coords *normal)
{
	t_hit		circle1_hit;
	t_hit		circle2_hit;
	double		mantle_t;
	t_coords	mantle_hit;
	double		t;

	circle1_hit = circle_hit(cylinder->plane1, cylinder->radius, origin,
			direction);
	circle2_hit = circle_hit(cylinder->plane2, cylinder->radius, origin,
			direction);
	mantle_t = mantle_intersection(cylinder, origin, direction);
	mantle_hit = vec_add(origin, vec_mul(direction, mantle_t));
	t = get_lowest_but_positve_t(circle1_hit.distance, circle2_hit.distance,
			mantle_t);
	if (t < 0)
		return (-1);
	if (t == circle1_hit.distance || t == circle2_hit.distance)
		*normal = cylinder->vector;
	else
	{
		get_normal(cylinder, mantle_hit, normal);
		*normal = vec_norm(*normal);
	}
	return (t);
}

int	cylinder_hit(t_cylinder *cylinder, t_coords origin, t_coords direction,
		t_hit *hit)
{
	int			t;
	t_coords	normal;

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
