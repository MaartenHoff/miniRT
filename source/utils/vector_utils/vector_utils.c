//- create vector from two points
//- get vector length
//- normalize vector
//- get dot product

#include "../../../includes/miniRT.h"

t_coords	vec_create(t_coords point1, t_coords point2)
{
	t_coords	vector;

	vector.x = point2.x - point1.x;
	vector.y = point2.y - point1.y;
	vector.z = point2.z - point1.z;
	return (vector);
}

t_coords	vec_add(t_coords point1, t_coords point2)
{
	t_coords	vector;

	vector.x = point1.x + point2.x;
	vector.y = point1.y + point2.y;
	vector.z = point1.z + point2.z;
	return (vector);
}

double	vec_len(t_coords vector)
{
	return (sqrt(vector.x * vector.x + vector.y * 
			vector.y + vector.z * vector.z));
}

t_coords	vec_norm(t_coords vector)
{
	t_coords	normalized;
	double		length;

	length = vec_len(vector);
	normalized.x = vector.x / length;
	normalized.y = vector.y / length;
	normalized.z = vector.z / length;
	return (normalized);
}

double	vec_skalar(t_coords vector1, t_coords vector2)
{
	return (vector1.x * vector2.x + vector1.y * vector2.y + vector1.z 
		* vector2.z);
}

t_coords	vec_mul(t_coords vector, double scalar)
{
	t_coords	scaled;

	scaled.x = vector.x * scalar;
	scaled.y = vector.y * scalar;
	scaled.z = vector.z * scalar;
	return (scaled);
}

double point_distance(t_coords point1, t_coords point2)
{
	t_coords	vector;
	double		distance;

	vector = vec_create(point1, point2);
	distance = vec_len(vector);
	if (distance < 0)
		distance *= -1;
	return (distance);
}
