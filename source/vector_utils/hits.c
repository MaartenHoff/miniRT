#include "../../includes/miniRT.h"

double	sphere_intersection(t_spheres *sphere, t_coords *origin, t_coords *d)
{
	t_coords	oc;
	double		t;

	oc = create_vector(origin, sphere->center);
	t = -2 * dot_product(&oc, &d);
	t = sqrt(pow(2 * dot_product(&oc, &d), 2) - 4 * dot_product(&oc, &oc) * ()
	
}