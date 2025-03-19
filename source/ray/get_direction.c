#include "../../includes/miniRT.h"

t_coords	get_direction(t_map *map, int x, int y)
{
	t_coords	direction;
	t_coords	point_on_viewport;

	point_on_viewport = vec_add(map->viewport->start, 
			vec_add(vec_mul(map->viewport->x_vector, x), 
				vec_mul(map->viewport->y_vector, y)));
	//print_vektor(point_on_viewport);
	direction = vec_norm(vec_create(map->camera->coords, point_on_viewport));
	return (direction);
}
