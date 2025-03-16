#include "../../includes/miniRT.h"

// add ambiant_light to pixel color
int			ambiant_light(t_map *map);
// send another ray in direction of light check for
t_color		calculate_lighting(t_map *map, t_hit *hit); 
// t_color into int color
int			color_to_int(t_color final);
int			sphere_hit(t_map *map, t_coords *origin, t_coords direction, 
				t_hit *hit);
int			cylinder_hit(t_map *map, t_coords *origin, t_coords direction, 
				t_hit *hit);
int			plane_hit(t_map *map, t_coords *origin, t_coords direction, 
				t_hit *hit);

int	send_ray_to_objects(t_map *map, t_coords *origin, t_coords direction, 
		t_hit *closest_hit)
{
	t_objects	*current;
	t_hit		*new_hit;

	current = map->objects;
	new_hit = NULL;
	while (current)
	{
		if (current->type == SPHERE)
			sphere_hit(map, origin, direction, new_hit);
		else if (current->type == CYLINDER)
			cylinder_hit(map, origin, direction, new_hit);
		else if (current->type == PLANE)
			plane_hit(map, origin, direction, new_hit);
		if (closest_hit && new_hit && closest_hit->distance > new_hit->distance)
			closest_hit = new_hit;
		ft_memdel((void **)&new_hit);
		current = current->next;
	}
	return (closest_hit != NULL);
}

int	send_ray(t_map *map, t_coords direction)
{
	t_hit	*hit;
	t_color	final;

	hit = NULL;
	if (!send_ray_to_objects(map, map->camera->coords, direction, hit))
		return (ambient_light(map));
	final = calculate_lighting(map, hit);
	return (color_to_int(final));
}
