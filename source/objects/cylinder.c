#include "../../includes/miniRT.h"

double	mantle_intersection(t_cylinder *cylinder, t_coords origin, 
			t_coords direction)
{
	(void)cylinder;
	(void)origin;
	(void)direction;
	return (-1);
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

t_hit	circle_hit(t_planes *plane, double radius, t_coords origin, t_coords direction)
{
	t_hit	hit;
	double	distance;

	plane_hit(plane, origin, direction, &hit);
	if (hit.distance < -1)
		return (hit);
	distance = vec_len(vec_create(hit.point, plane->point));
	if (distance > radius)
		hit.distance = -1;
	return (hit);
}


int	cylinder_intersection(t_cylinder *cylinder, t_coords origin, 
	t_coords direction, t_coords *normal)
{
	t_hit		circle1_hit;
	t_hit		circle2_hit;
	double		mantle_t;
	double		t;
	t_coords	hit;

	circle1_hit = circle_hit(cylinder->plane1, cylinder->radius, origin, direction);
	circle2_hit = circle_hit(cylinder->plane2, cylinder->radius, origin, direction);
	mantle_t = mantle_intersection(cylinder, origin, direction);
	t = get_lowest_but_positve_t(circle1_hit.distance, circle2_hit.distance, mantle_t);
	if (t < 0)
		return (-1);
	if (t == circle1_hit.distance || t == circle2_hit.distance)
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
