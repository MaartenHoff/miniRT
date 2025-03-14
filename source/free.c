#include "../includes/miniRT.h"

void	free_params(char ***params)
{
	int	i;
	int	j;

	i = 0;
	if (!params)
		return ;
	while (params[i])
	{
		j = 0;
		while (params[i][j])
		{
			ft_memdel((void **)&params[i][j]);
			j++;
		}
		ft_memdel((void **)&params[i]);
		i++;
	}
	free(params);
}

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
	t_objects	*temp;

	if (!map)
		return ;
	temp = map->objects;
	while (temp)
	{
		if (temp->type == SPHERE)
			free_sphere(temp->spheres);
		else if (temp->type == PLANE)
			free_plane(temp->plane);
		else if (temp->type == CYLINDER)
			free_cylinder(temp->cylinder);
		temp = temp->next;
		ft_memdel((void **)&(map->objects));
		map->objects = temp;
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
