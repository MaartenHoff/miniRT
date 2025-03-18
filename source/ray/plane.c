#include "../../includes/miniRT.h"

int	plane_hit(t_planes *plane, t_coords origin, t_coords direction, t_hit *hit)
{
	double	t;

	t = plane_intersection(plane, origin, direction);
	// printf("t: %f\n", t);
	if (t < 0)
		return (0);
	hit->point = vec_add(origin, vec_mul(direction, t));
	hit->distance = t;
	hit->color = plane->color;
	hit->normal = plane->vector;
	return (0);
}
