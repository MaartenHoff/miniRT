#include "../../includes/miniRT.h"

int	color_plus_light(t_color light_color, double brightness, t_color color)
{
	color.r *= (light_color.r * brightness) / 255;
	color.g *= (light_color.g * brightness) / 255;
	color.b *= (light_color.b * brightness) / 255;
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
		return (color_plus_light(map->ambient->color, map->ambient->brightness, 
				(t_color){0, 0, 0}));
	color = color_plus_light(map->ambient->color, map->ambient->brightness, 
			hit.color);
	//printf("color: %d\n", color);
	return (color);
}
