#include "../../includes/miniRT.h"

t_coords	vec_add(t_coords vector, t_coords vector2);

t_coords	get_direction(t_map *map, int x, int y)
{
	t_coords	direction;
	t_coords	point_on_viewport;

	(void)map;
	(void)x;
	(void)y;

	point_on_viewport = vec_add(map->viewport->start, 
			vec_add(vec_mul(map->viewport->x_vector, x), 
				vec_mul(map->viewport->y_vector, y)));
	direction = vec_create(*(map->camera->coords), point_on_viewport);
	return (direction);
}
