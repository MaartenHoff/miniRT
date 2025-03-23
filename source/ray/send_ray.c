#include "../../includes/miniRT.h"

t_coords	reflect(t_coords v, t_coords n)
{
	return (vec_sub(v, vec_mul(n, 2 * vec_skalar(v, n))));
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
			cylinder_hit(current->cylinder, origin, direction, &new_hit);
		else if (current->type == PLANE)
			plane_hit(current->plane, origin, direction, &new_hit);
		else if (current->type == CUBE)
			cube_hit(current->cube, origin, direction, &new_hit);
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

double	calc_light(t_map *map, t_hit hit, t_coords old_ray, double *skalar)
{
	t_coords	safe_distance;
	t_hit		place_holder;
	double		brightness;
	t_coords	l_dir;
	t_coords	reflect_dir;

	place_holder.distance = -1;
	safe_distance = vec_add(hit.point, vec_mul(hit.normal, 1e-10));
	l_dir = vec_create(hit.point, map->light->source);
	if (send_ray_to_objects(map, safe_distance, vec_norm(l_dir), &place_holder))
	{
		if (place_holder.distance < vec_len(l_dir))
			return (0);
	}
	*skalar = vec_skalar(hit.normal, vec_norm(l_dir));
	brightness = map->light->brightness * *skalar;
	reflect_dir = reflect(l_dir, hit.normal);
	*skalar = vec_skalar(vec_norm(reflect_dir), vec_norm(old_ray));
	if (*skalar < 0)
		*skalar = 0;
	*skalar = SPEKULARFAKTOR * pow(*skalar, SHININESS);
	return (brightness);
}

int	send_ray(t_map *map, t_coords direction)
{
	t_hit			hit;
	t_light_data	final_light;
	t_color			color;
	double			skalar;

	skalar = 0.0;
	hit.distance = -1;
	if (!send_ray_to_objects(map, map->camera->coords, direction, &hit))
		return (0);
	final_light = light_plus_light(map->light->color, 
			calc_light(map, hit, direction, &skalar), map->ambient->color, 
			map->ambient->brightness);
	color = light_hit_color(final_light.color, final_light.brightness, 
			hit.color);
	color = add_specular(color, map->light->color, skalar);
	return (color_to_int(color));
}
