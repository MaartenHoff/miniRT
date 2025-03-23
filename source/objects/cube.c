#include "../../includes/miniRT.h"

double	distance_to_cube(t_cube *cube, t_coords origin,
	t_coords direction, t_coords *normal)
{
t_hit		plane1_hit;
t_hit		plane2_hit;
t_hit		plane3_hit;
t_hit		plane4_hit;
t_hit		plane5_hit;
t_hit		plane6_hit;
double		t;

plane1_hit = plane_hit(cube->plane1, )
t = get_lowest_but_positve_t(circle1_hit.distance, circle2_hit.distance,
		mantle_hit.distance);
if (t < 0)
	return (-1);
if (t == circle1_hit.distance || t == circle2_hit.distance)
	*normal = cylinder->vector;
else
{
	get_normal(cylinder, mantle_hit.point, normal);
	*normal = vec_norm(*normal);
}
return (t);
}

int	cube_hit(t_cube *cube, t_coords origin, 
	t_coords direction,	t_hit *hit)
{
	double		t;
	t_coords	normal;

	normal = (t_coords){0, 0, 0};
	t = distance_to_cube(cube, origin, direction, &normal);
	if (t < 0)
		return (0);
	hit->point = vec_add(origin, vec_mul(direction, t));
	hit->distance = t;
	hit->color = cube->color;
	if (vec_skalar(direction, normal) > 0)
		normal = vec_mul(normal, -1);
	hit->normal = normal;
	return (0);
}
