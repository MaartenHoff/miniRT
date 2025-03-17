#include "../../includes/miniRT.h"

int	sphere_hit(t_spheres *sphere, t_coords *origin, t_coords direction, 
	t_hit *hit)
{
	double	t;

	t = sphere_intersection(*sphere, *origin, direction);
	// printf("t: %lf\n", t);
	// print_vektor(direction);
	if (t < 0)
		return (0);
	hit->point = vec_add(*origin, vec_mul(direction, t));
	hit->distance = t;
	hit->color = *sphere->color;
	hit->normal = vec_norm(vec_create(*sphere->center, hit->point));
	return (0);
}
