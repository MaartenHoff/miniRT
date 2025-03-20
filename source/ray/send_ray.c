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
	t_coords	safe_distance;
	t_hit		place_holder;
	double		brightness;
	double		skalar;
	t_coords	light_direction;
	t_coords	light_direction_normed;

	(void)old_ray;
	place_holder.distance = -1;
	safe_distance = vec_add(hit.point, vec_mul(hit.normal, 1e-10));
	//printf("hit point: %lf, %lf, %lf\n", hit.point.x, hit.point.y, hit.point.z);
	//printf("light source: %lf, %lf, %lf\n", map->light->source.x, map->light->source.y, map->light->source.z);
	light_direction = vec_create(hit.point, map->light->source);
	//printf("light direction: %lf, %lf, %lf\n", light_direction.x, light_direction.y, light_direction.z);
	light_direction_normed = vec_norm(light_direction);
	//printf("light direction normalized: %lf, %lf, %lf\n", light_direction_normed.x, light_direction_normed.y, light_direction_normed.z);
	if (send_ray_to_objects(map, safe_distance, light_direction_normed, &place_holder))
	{
		if (place_holder.distance < vec_len(light_direction))
        {
			// printf("hit color: %d, %d, %d\n", hit.color.r, hit.color.g, hit.color.b);
			// printf("obstacle distance: %lf\n", place_holder.distance);
			// printf("obsacle color: %d, %d, %d\n", place_holder.color.r, place_holder.color.g, place_holder.color.b);
			// printf("obstacle normal: %lf, %lf, %lf\n", place_holder.normal.x, place_holder.normal.y, place_holder.normal.z);
			// printf("obstacle point: %lf, %lf, %lf\n", place_holder.point.x, place_holder.point.y, place_holder.point.z);
			return (0);
		}
	}
	skalar = vec_skalar(hit.normal, light_direction_normed);
	//printf("skalar: %lf\n", skalar);
	brightness = map->light->brightness * skalar;
	//printf("brightness: %lf\n", brightness);
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
	//printf("object hit distance: %lf\n", hit.distance);
	//printf("objecthit color: %d, %d, %d\n", hit.color.r, hit.color.g, hit.color.b);
	//printf("object hit normal: %lf, %lf, %lf\n", hit.normal.x, hit.normal.y, hit.normal.z);
	//printf("object hit point: %lf, %lf, %lf\n", hit.point.x, hit.point.y, hit.point.z);
	final_light = light_plus_light(map->light->color, 
			calc_light(map, hit, direction), map->ambient->color, 
			map->ambient->brightness);
	//printf("final_light: %d, %d, %d\n", final_light.color.r, final_light.color.g, final_light.color.b);
	color = light_hit_color(final_light.color, final_light.brightness, 
			hit.color);
	//printf("color: %d, %d, %d\n", color.r, color.g, color.b);
	//printf("----------\n");
	return (color_to_int(color));
}
