#include "../../includes/miniRT.h"

double	mantle_intersection(t_cylinder *cylinder, t_coords origin,
		t_coords direction)
{
	t_coords	oc;
	t_coords	d_proj;
	t_coords	oc_proj;
	double		a;
	double		b;
	double		c;
	double		discriminant;
	double		sqrt_disc;
	double		t0;
	double		t1;
	double		t;
	t_coords	hit;
	double		proj;

	oc = vec_sub(origin, cylinder->base);
	d_proj = vec_sub(direction, vec_mul(cylinder->vector, vec_skalar(direction,
					cylinder->vector)));
	oc_proj = vec_sub(oc, vec_mul(cylinder->vector, vec_skalar(oc,
					cylinder->vector)));
	a = vec_skalar(d_proj, d_proj);
	b = 2.0 * vec_skalar(d_proj, oc_proj);
	c = vec_skalar(oc_proj, oc_proj) - cylinder->radius * cylinder->radius;
	discriminant = b * b - 4.0 * a * c;
	if (discriminant < 0 || fabs(a) < 1e-6)
		return (-1);
	sqrt_disc = sqrt(discriminant);
	t0 = (-b - sqrt_disc) / (2.0 * a);
	t1 = (-b + sqrt_disc) / (2.0 * a);
	if (t0 > 0)
		t = t0;
	else if (t1 > 0)
		t = t1;
	else
		return (-1);
	hit = vec_add(origin, vec_mul(direction, t));
	proj = vec_skalar(vec_sub(hit, cylinder->base), cylinder->vector);
	if (proj < 0 || proj > cylinder->height)
		return (-1);
	return (t);
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
	double	t;

	t = vec_skalar(vec_add(hit, cylinder->base), cylinder->vector) / vec_skalar(cylinder->vector, cylinder->vector);
	*normal = vec_create(vec_add(cylinder->base, vec_mul(cylinder->vector, t)), hit);
}

// {
// hit = vec_add(origin, vec_mul(direction, t));
// *normal = vec_create(vec_add(cylinder->base, vec_mul(cylinder->vector, cylinder->height)), hit);
// }

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
	if (mantle_t < 0)
		return (-1);
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
