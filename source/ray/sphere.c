#include "../../includes/miniRT.h"

int	sphere_hit(t_spheres *sphere, t_coords *origin, t_coords direction, 
	t_hit *hit)
{
	double	t;

	t = sphere_intersection(*sphere, *origin, direction);
	// print_vektor(direction);
	hit->point = vec_add(*origin, vec_mul(direction, t));
	hit->distance = t;
	hit->color = *sphere->color;
	hit->normal = vec_create(hit->point, *sphere->center);
	return (0);
}
