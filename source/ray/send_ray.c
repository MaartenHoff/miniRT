#include "../../includes/miniRT.h"

int	ambient_light(t_map *map, t_color color)
{
	color.r *= (map->ambient->color.r * map->ambient->brightness)/255;
	color.g *= (map->ambient->color.g * map->ambient->brightness)/255;
	color.b *= (map->ambient->color.b * map->ambient->brightness)/255;
	return (color_to_int(color));
}

int	send_ray_to_objects(t_map *map, t_coords origin, t_coords direction, 
		t_hit *closest_hit)
{
	t_objects	*current;
	t_hit		new_hit;

	current = map->objects;
	while (current)
	{
		new_hit.distance = -1;
		if (current->type == SPHERE)
			sphere_hit(current->spheres, origin, direction, &new_hit);
		else if (current->type == CYLINDER)
			cylinder_hit(map, origin, direction, &new_hit);
		else if (current->type == PLANE)
			plane_hit(map, origin, direction, &new_hit);
		if (new_hit.distance >= 0.0)
		{
			if (closest_hit->distance < 0.0 || 
				new_hit.distance < closest_hit->distance)
				*closest_hit = new_hit;
		}
		current = current->next;
	}
	return (closest_hit->distance >= 0.0);
}

int	send_ray(t_map *map, t_coords direction)
{
	t_hit	hit;
	int		color;

	hit.distance = -1;
	if (!send_ray_to_objects(map, map->camera->coords, direction, &hit))
		return (ambient_light(map, (t_color){0, 0, 0}));
	color = ambient_light(map, hit.color);
	//printf("color: %d\n", color);
	return (color);
}


	//final = calculate_lighting(map, hit);
	// return (color_to_int(final));