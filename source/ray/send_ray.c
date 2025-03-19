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
			cylinder_hit(current->cylinder, origin, direction, &new_hit);
		else if (current->type == PLANE)
			plane_hit(current->plane, origin, direction, &new_hit);
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
	safe_distance = vec_add(hit.point, vec_mul(hit.normal, 1e-6));
	direction = vec_create(hit.point, map->light->source);
	direction = vec_norm(direction);
	if (send_ray_to_objects(map, safe_distance, direction, &place_holder))
		return (0);
	skalar = vec_skalar(hit.normal, direction);
	brightness = map->light->brightness * skalar;
	return (brightness);
}

int	send_ray(t_map *map, t_coords direction)
{
	t_hit			hit;
	t_light_data	final_light;
	t_color			color;

	//print_vektor(direction);
	hit.distance = -1;
	if (!send_ray_to_objects(map, map->camera->coords, direction, &hit))
		return (0);
	// printf("\nhit distance: %lf\n", hit.distance);
	// printf("hit color: %d, %d, %d\n", hit.color.r, hit.color.g, hit.color.b);
	// printf("hit normal: %lf, %lf, %lf\n", hit.normal.x, hit.normal.y, hit.normal.z);
	//printf("hit point: %lf, %lf, %lf\n", hit.point.x, hit.point.y, hit.point.z);
	// printf("----------");
	final_light = light_plus_light(map->light->color, 
			calc_light(map, hit, direction), map->ambient->color, 
			map->ambient->brightness);
	printf("final_light: %d, %d, %d\n", final_light.color.r, final_light.color.g, final_light.color.b);
	color = light_hit_color(final_light.color, final_light.brightness, 
			hit.color);
	return (color_to_int(color));
}
