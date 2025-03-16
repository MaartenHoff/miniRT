//- create vector from two points
//- get vector length
//- normalize vector
//- get dot product

#include "../../includes/miniRT.h"

t_coords *create_vector(t_coords start, t_coords end)
{
	t_coords	*vector;

	vector = malloc(sizeof(t_coords));
	if (!vector)
		return (NULL);
	vector->x = end.x - start.x;
	vector->y = end.y - start.y;
	vector->z = end.z - start.z;
	return (vector);
}

double get_vector_length(t_coords vector)
{
	return (sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z));
}

t_coords normalize_vector(t_coords vector)
{
	t_coords	normalized;
	double		length;

	length = get_vector_length(vector);
	normalized.x = vector.x / length;
	normalized.y = vector.y / length;
	normalized.z = vector.z / length;
	return (normalized);
}

double get_dot_product(t_coords vector1, t_coords vector2)
{
	return (vector1.x * vector2.x + vector1.y * vector2.y + vector1.z * vector2.z);
}

t_coords scale_vector(t_coords vector, double scalar)
{
	t_coords	scaled;

	scaled.x = vector.x * scalar;
	scaled.y = vector.y * scalar;
	scaled.z = vector.z * scalar;
	return (scaled);
}

double get_point_distance(t_coords point1, t_coords point2)
{
	t_coords	*vector;
	double		distance;

	vector = create_vector(point1, point2);
	distance = get_vector_length(*vector);
	free(vector);
	return (distance);
}

int color_to_int(t_color color)
{
	return ((color.r << 16) | (color.g << 8) | color.b);
}
