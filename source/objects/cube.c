#include "../../includes/miniRT.h"

t_hit	square_hit(t_planes *plane, double size, t_coords origin,
		t_coords direction)
{
	t_hit		hit;
	t_coords	local_point;
	double		half_size;

	hit.distance = -1;
	plane_hit(plane, origin, direction, &hit);
	if (hit.distance < 0)
		return (hit);
	local_point = vec_sub(hit.point, plane->point);
	half_size = size / 2.0;
	if (plane->vector.x != 0)
	{
		if (fabs(local_point.y) > half_size || fabs(local_point.z) > half_size)
			hit.distance = -1;
	}
	else if (plane->vector.y != 0)
	{
		if (fabs(local_point.x) > half_size || fabs(local_point.z) > half_size)
			hit.distance = -1;
	}
	else
	{
		if (fabs(local_point.x) > half_size || fabs(local_point.y) > half_size)
			hit.distance = -1;
	}
	return (hit);
}

double get_actually_lowest_but_positve_t(double t1, double t2, double t3,
	double t4, double t5, double t6)
{
	double t;

	t = DBL_MAX;
	if (t1 >= 0 && t1 < t)
		t = t1;
	if (t2 >= 0 && t2 < t)
		t = t2;
	if (t3 >= 0 && t3 < t)
		t = t3;
	if (t4 >= 0 && t4 < t)
		t = t4;
	if (t5 >= 0 && t5 < t)
		t = t5;
	if (t6 >= 0 && t6 < t)
		t = t6;
	return t;
}

double	distance_to_cube(t_cube *cube, t_coords origin, t_coords direction,
		t_coords *normal)
{
	t_hit	square1_hit;
	t_hit	square2_hit;
	t_hit	square3_hit;
	t_hit	square4_hit;
	t_hit	square5_hit;
	t_hit	square6_hit;
	double	t;

	square1_hit = square_hit(cube->square1, cube->size, origin, direction);
	square2_hit = square_hit(cube->square2, cube->size, origin, direction);
	square3_hit = square_hit(cube->square3, cube->size, origin, direction);
	square4_hit = square_hit(cube->square4, cube->size, origin, direction);
	square5_hit = square_hit(cube->square5, cube->size, origin, direction);
	square6_hit = square_hit(cube->square6, cube->size, origin, direction);
	t = get_actually_lowest_but_positve_t(square1_hit.distance, square2_hit.distance,
			square3_hit.distance, square4_hit.distance, square5_hit.distance,
			square6_hit.distance);
	if (t < 0)
		return (-1);
	// get normal
	if (square1_hit.distance == t || square2_hit.distance == t)
		*normal = cube->square1->vector;
	else if (square3_hit.distance == t || square4_hit.distance == t)
		*normal = cube->square3->vector;
	else
		*normal = cube->square5->vector;
	return (t);
}

int	cube_hit(t_cube *cube, t_coords origin, t_coords direction, t_hit *hit)
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
