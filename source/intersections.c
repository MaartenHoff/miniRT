#include "../../includes/miniRT.h"

double	sphere_intersection(t_spheres sphere, t_coords origin, t_coords d)
{
	t_coords	*oc;
	double		t1;
	double		t2;

	oc = create_vector(origin, sphere.center);
	t1 = sqrt(pow(2 * dot_product(*oc, d), 2) - 4 * dot_product(*oc, *oc) * (dot_product(oc, oc) - pow(sphere.diameter / 2, 2)));
	t2 = sqrt(pow(2 * dot_product(*oc, d), 2) - 4 * dot_product(*oc, *oc) * (dot_product(oc, oc) - pow(sphere.diameter / 2, 2)));
	t1 = (-2 * dot_product(*oc, d) + t1) / 2 * dot_product(d, d);
	t2 = (-2 * dot_product(*oc, d) - t2) / 2 * dot_product(d, d);
	free(oc);
	if (t1 < t2)
		return (t1);
	else
		return (t2);
	free(oc);
}