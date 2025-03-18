#include "../../includes/miniRT.h"

double	plane_intersection(t_planes *plane, t_coords origin, t_coords direction)
{
	double		t;

	double		np;
	double		nd;
	double		no;

	np = vec_skalar(plane->vector, origin);
	nd = vec_skalar(plane->vector, direction);
	no = vec_skalar(plane->vector, plane->point);

	t = (-np + no)/nd;
	return (t);
}