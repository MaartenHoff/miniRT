#include "../../includes/miniRT.h"

double	mantle_intersection(t_cylinder *cylinder, t_coords origin, 
			t_coords direction)
{
	
}

double	get_lowest_but_positve_t(double plane1_t, double plane2_t, 
			double mantle_t)
{
	if (plane1_t > 0 && plane2_t > 0 && plane1_t <= plane2_t)
		plane2_t = plane1_t;
	else if (plane1_t > 0 && plane2_t > 0)
		plane1_t = plane2_t;
	if (plane2_t > 0 && mantle_t > 0 && plane2_t <= mantle_t)
		plane2_t = mantle_t;
	else if (plane2_t > 0 && mantle_t > 0)
		mantle_t = plane2_t;
	if (mantle_t > 0 && plane1_t > 0 && mantle_t <= plane1_t)
		mantle_t = plane1_t;
	else if (mantle_t > 0 && plane1_t > 0)
		plane1_t = mantle_t;
	if (plane1_t > 0)
		return (plane1_t);
	else if (plane2_t > 0)
		return (plane2_t);
	else if (mantle_t > 0)
		return (mantle_t);
	return (-1);
}

int	cylinder_intersection(t_cylinder *cylinder, t_coords origin, 
	t_coords direction, t_coords *normal)
{
	double		plane1_t;
	double		plane2_t;
	double		mantle_t;
	double		t;
	t_coords	hit;

	plane1_t = plane_intersection(cylinder->plane1, origin, direction);
	plane2_t = plane_intersection(cylinder->plane2, origin, direction);
	mantle_t = mantle_intersection(cylinder, origin, direction);
	t = get_lowest_but_positve_t(plane1_t, plane2_t, mantle_t);
	if (t < 0)
		return (-1);
	if (t == plane1_t || t == plane2_t)
		*normal = cylinder->plane1->vector;
	else
	{
		hit = vec_add(origin, vec_mul(direction, t));
		*normal = vec_create(vec_add(cylinder->base, 
					vec_mul(cylinder->vector, cylinder->height)), hit);
	}
	return (t);
}

int	cylinder_hit(t_cylinder *cylinder, t_coords origin, 
	t_coords direction, t_hit *hit)
{
	int			t;
	t_coords	normal;

	t = cylinder_intersection(cylinder, origin, direction, &normal);
	if (t < 0)
		return (0);
	hit->point = vec_add(origin, vec_mul(direction, t));
	hit->distance = t;
	hit->color = cylinder->color;
	if (vec_skalar(direction, normal) > 0)
		normal = vec_mul(normal, -1);
	hit->normal = normal;
	return (0);
}
