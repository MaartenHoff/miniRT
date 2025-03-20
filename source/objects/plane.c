#include "../../includes/miniRT.h"

int	plane_hit(t_planes *plane, t_coords origin, t_coords direction, t_hit *hit)
{
	double		t;
	t_coords	normal;

	normal = plane->vector;
	t = plane_intersection(plane, origin, direction);
	if (t < 0)
		return (0);
	hit->point = vec_add(origin, vec_mul(direction, t));
	hit->distance = t;
	hit->color = plane->color;
	if (vec_skalar(direction, normal) > 0)
		normal = vec_mul(normal, -1);
	hit->normal = normal;
	return (0);
}

double	plane_intersection(t_planes *plane, t_coords origin, t_coords direction)
{
	double		t;
	double		np;
	double		nd;
	double		no;

	np = vec_skalar(plane->vector, origin);
	nd = vec_skalar(plane->vector, direction);
	no = vec_skalar(plane->vector, plane->point);

	t = (-np + no) / nd;
	return (t);
}
