#include "../../includes/miniRT.h"

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

double	calc_light(t_map *map, t_hit hit, t_coords old_ray)
{
	t_coords	direction;
	t_coords	safe_distance;
	t_hit		place_holder;
	double		brightness;
	double		skalar;

	(void)old_ray;
	place_holder.distance = -1;
	safe_distance = vec_add(hit.point, vec_mul(hit.normal, 1e-4));
	direction = vec_create(hit.point, map->light->source);
	direction = vec_norm(direction);
	if (send_ray_to_objects(map, safe_distance, direction, &place_holder))
		return (0);
	skalar = vec_skalar(hit.normal, direction);
	if (skalar < 0)
		return (0);
	brightness = map->light->brightness * skalar;
	if (brightness > 1)
		brightness = 1;
	return (brightness);
}

int	send_ray(t_map *map, t_coords direction)
{
	t_hit			hit;
	t_light_data	final_light;
	t_color			color;

	hit.distance = -1;
	if (!send_ray_to_objects(map, map->camera->coords, direction, &hit))
		return (color_to_int(light_hit_color(map->ambient->color, 
					map->ambient->brightness, (t_color){0, 0, 0})));
	final_light = light_plus_light(map->light->color, calc_light(map, hit, 
				direction), map->ambient->color, map->ambient->brightness);
	color = light_hit_color(final_light.color, final_light.brightness, 
			hit.color);
	return (color_to_int(color));
}
