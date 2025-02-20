#include "../includes/miniRT.h"

void	free_sphere(t_spheres *sphere)
{
	if (!sphere)
		return ;
	if (sphere->color)
		free(sphere->color);
	if (sphere->center)
		free(sphere->center);
	free(sphere);
}

void	free_plane(t_planes *plane)
{
	if (!plane)
		return ;
	if (plane->color)
		free(plane->color);
	if (plane->point)
		free(plane->point);
	if (plane->vector)
		free(plane->vector);
	free(plane);
}

void	free_cylinder(t_cylinder *cylinder)
{
	if (!cylinder)
		return ;
	if (cylinder->color)
		free(cylinder->color);
	if (cylinder->base)
		free(cylinder->base);
	if (cylinder->vector)
		free(cylinder->vector);
	free(cylinder);
}

void	free_map(t_map *map)
{
	t_objects	*tmp_obj;
	tmp_obj = map->objects;
	while (tmp_obj)
	{
		if (tmp_obj->type == SPHERE)
			free_sphere(tmp_obj->spheres);
		else if (tmp_obj->type == PLANE)
			free_plane(tmp_obj->plane);
		else if (tmp_obj->type == CYLINDER)
			free_cylinder(tmp_obj->cylinder);
		tmp_obj = tmp_obj->next;
	}
	free(map->ambient->color);
	free(map->ambient);
	free(map->camera->coords);
	free(map->camera->vector);
	free(map->camera);
	free(map->light->color);
	free(map->light->source);
	free(map->light);
	free(map);
}

	