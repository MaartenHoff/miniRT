#include "../../includes/miniRT.h"

t_hit	square_hit(t_planes *plane, double half_size, t_coords origin,
		t_coords direction)
{
	t_hit		hit;
	t_coords	local_point;

	hit.distance = -1;
	plane_hit(plane, origin, direction, &hit);
	if (hit.distance < 0)
		return (hit);
	local_point = vec_sub(hit.point, plane->point);
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

double	get_lowest_positive(t_hit *hits)
{
	double	t;

	t = -1;
	if (hits[0].distance >= 0 && (t < 0 || hits[0].distance < t))
		t = hits[0].distance;
	if (hits[1].distance >= 0 && (t < 0 || hits[1].distance < t))
		t = hits[1].distance;
	if (hits[2].distance >= 0 && (t < 0 || hits[2].distance < t))
		t = hits[2].distance;
	if (hits[3].distance >= 0 && (t < 0 || hits[3].distance < t))
		t = hits[3].distance;
	if (hits[4].distance >= 0 && (t < 0 || hits[4].distance < t))
		t = hits[4].distance;
	if (hits[5].distance >= 0 && (t < 0 || hits[5].distance < t))
		t = hits[5].distance;
	return (t);
}

double	get_square_hits(t_cube *cube, t_coords origin, t_coords direction,
		t_hit hits[6])
{
	double	half_size;

	half_size = cube->size / 2;
	hits[0] = square_hit(cube->square1, half_size, origin, direction);
	hits[1] = square_hit(cube->square2, half_size, origin, direction);
	hits[2] = square_hit(cube->square3, half_size, origin, direction);
	hits[3] = square_hit(cube->square4, half_size, origin, direction);
	hits[4] = square_hit(cube->square5, half_size, origin, direction);
	hits[5] = square_hit(cube->square6, half_size, origin, direction);
	return (get_lowest_positive(hits));
}

double	distance_to_cube(t_cube *cube, t_coords origin, t_coords direction,
		t_coords *normal)
{
	t_hit	hits[6];
	double	t;

	t = get_square_hits(cube, origin, direction, hits);
	if (t < 0)
		return (-1);
	if (hits[0].distance == t || hits[1].distance == t)
		*normal = cube->square1->vector;
	else if (hits[2].distance == t || hits[3].distance == t)
		*normal = cube->square3->vector;
	else
		*normal = cube->square5->vector;
	return (t);
}

int	cube_hit(t_cube *cube, t_coords origin, t_coords direction, t_hit *hit)
{
	double		t;
	t_coords	normal;

	t = -1;
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
