#include "../../includes/miniRT.h"

int	sphere_hit(t_spheres *sphere, t_coords origin, t_coords direction, 
	t_hit *hit)
{
	double	t;

	t = -1;
	t = sphere_intersection(sphere, origin, direction);
	if (t < 0)
		return (0);
	hit->point = vec_add(origin, vec_mul(direction, t));
	hit->distance = t;
	hit->color = sphere->color;
	hit->normal = vec_norm(vec_create(sphere->center, hit->point));
	return (0);
}

double	sphere_intersection(t_spheres *sphere, t_coords origin, t_coords d)
{
	t_coords	co;
	double		a;
	double		b;
	double		c;

	co = vec_create(sphere->center, origin);
	a = vec_skalar(d, d);
	b = 2 * vec_skalar(co, d);
	c = vec_skalar(co, co) - sphere->radius * sphere->radius;
	return (solve_quadratic(a, b, c));
}
