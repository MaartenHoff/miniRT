#include "../../includes/miniRT.h"

t_coords	get_direction(t_map *map, int x, int y)
{
	t_coords	direction;
	t_coords	point_on_vp;

	point_on_vp = vec_add(map->vp->start,
			vec_add(vec_mul(map->vp->x_vector, x),
				vec_mul(map->vp->y_vector, y)));
	direction = vec_norm(vec_create(map->camera->coords, point_on_vp));
	return (direction);
}
