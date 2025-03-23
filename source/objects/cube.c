#include "../../includes/miniRT.h"

t_hit	square_hit(t_planes *plane, double size, t_coords origin,
		t_coords direction)
{
	t_hit	hit;
	double	distance;

	hit.distance = -1;
	plane_hit(plane, origin, direction, &hit);
	if (hit.distance < 0)
		return (hit);
	distance = vec_len(vec_create(hit.point, plane->point));
	if (distance > size)
		hit.distance = -1;
	return (hit);
}

double	distance_to_cube(t_cube *cube, t_coords origin,
	t_coords direction, t_coords *normal)
{
	t_hit		square1_hit;
	// t_hit		square2_hit;
	// t_hit		square3_hit;
	// t_hit		square4_hit;
	// t_hit		square5_hit;
	// t_hit		square6_hit;
	double		t;

	square1_hit = square_hit(cube->square1, cube->size, origin, direction);
	t = get_lowest_but_positve_t(square1_hit.distance, -1, -1);
	if (t < 0)
		return (-1);
	//get normal
	*normal = cube->square1->vector;
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
