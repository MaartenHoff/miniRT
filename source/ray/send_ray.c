#include "../../includes/miniRT.h"

int		ambiant_light(t_map *map);
t_color	calculate_lighting(t_map *map, t_hit *hit);
int		color_to_int(t_color final);

int	send_ray_to_objects(t_map *map, t_coords direction, t_coords *closest_hit)
{
	t_objects	*current;
	t_coords	*hit;
	int			color;

	current = map->objects;
	hit = NULL;
	while (current)
	{
		if (current->type == SPHERE)
			// check_if_sphere_gets_hit -- yes / no, if yes return color, position of hit
		//else if (current->type == CYLINDER)
			// check if cylinder (ingnore for now)
		//else if (current->type == PLANE)
			// check if Plane (ingnore for now)
		// if distance from hit to Camera is smaller than closest_hit -> replace closes hit with hit
		current = current->next;
	}
	return (color);
}

int	send_ray(t_map *map, t_coords direction)
{
	t_hit	*hit;
	t_color	final;

	if (!send_ray_to_objects(map, direction, hit))
		return (ambient_light(map));
	final = calculate_lighting(map, hit);

	return (color_to_int(final));
}
