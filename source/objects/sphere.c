#include "../../includes/miniRT.h"

int	sphere_hit(t_spheres *sphere, t_coords origin, t_coords direction, 
	t_hit *hit)
{
	double	t;

	t = sphere_intersection(sphere, origin, direction);
	if (t < 0)
		return (0);
	hit->point = vec_add(origin, vec_mul(direction, t));
	hit->distance = t;
	hit->color = sphere->color;
	hit->normal = vec_norm(vec_create(sphere->center, hit->point));
	return (0);
}

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

double	sphere_intersection(t_spheres *sphere, t_coords origin, t_coords d)
{
	t_coords	co;
	double		a;
	double		b;
	double		c;

	// print_vektor(d);
	co = vec_create(sphere->center, origin);
	a = vec_skalar(d, d);
	b = 2 * vec_skalar(co, d);
	c = vec_skalar(co, co) - sphere->radius * sphere->radius;
	return (solve_quadratic(a, b, c));
}
