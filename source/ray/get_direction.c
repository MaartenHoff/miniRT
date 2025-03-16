#include "../../includes/miniRT.h"

t_coords	*get_direction(t_map *map, int x, int y)
{
	t_coords	*direction;
	(void)map;
	(void)x;
	(void)y;

	direction = malloc(sizeof(t_coords));
	if (!direction)
		return (NULL);
	//point_on_linewand = map->viewport->start + (x * map->viewport->x_vector) + (y * map->viewport->y_vector);
	//direction = make_vektor between_origin and point_on_linewand;
	return (direction);
}
