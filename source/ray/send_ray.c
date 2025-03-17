#include "../../includes/miniRT.h"

int	ambient_light(t_map *map)
{
	t_color	color;

	color.r = 0;
	color.g = 0;
	color.b = 0;
	color.r += 255 * map->ambient->brightness;
	color.g += 255 * map->ambient->brightness;
	color.b += 255 * map->ambient->brightness;
	return (color_to_int(color));
}

int	send_ray_to_objects(t_map *map, t_coords *origin, t_coords direction, 
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
	t_hit	*hit;
	int		color;

	hit = malloc(sizeof(t_hit));
	if (!hit)
		return (0);
	hit->distance = -1;
	if (!send_ray_to_objects(map, map->camera->coords, direction, hit))
		return (ft_memdel((void **)&hit), ambient_light(map));
	color = color_to_int(hit->color);
	ft_memdel((void **)&hit);
	printf("color: %d\n", color);
	return (color);
}


	//final = calculate_lighting(map, hit);
	// return (color_to_int(final));