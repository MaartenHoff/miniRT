#include "../../includes/miniRT.h"

int	init_sphere(char **params, t_map **map)
{
	t_objects	*objects;
	char		**split;
	int			error_check;

	error_check = 0;
	objects = alloc_sphere(map);
	if (!objects)
		return (error_check);
	objects->spheres->center = split_coords(params[1]);
	if (!objects->spheres->center)
		free_map(*map);
	objects->spheres->diameter = ft_atoi(params[2]);
	objects->spheres->color = split_color(params[3]);
	if (!objects->spheres->color)
		free_map(*map);
	ft_lstadd_back(&(*map)->objects, objects);
	return (error_check);
}

int	init_plane(char **params, t_map **map)
{
	t_objects	*objects;
	int			error_check;

	error_check = alloc_plane(&objects);
	if (error_check)
		return (error_check);
	objects->plane->point = split_coords(params[1]);
	if (!objects->plane->point)
		free_map(*map);
	objects->plane->vector = split_coords(params[2]);
	if (!objects->plane->vector)
		free_map(*map);
	objects->plane->color = split_color(params[3]);
	if (!objects->plane->color)
		free_map(*map);
	ft_lstadd_back(&(*map)->objects, objects);
	return (0);
}

int	init_cylinder(char **params, t_map **map)
{
	t_objects	*objects;
	int			error_check;

	error_check = alloc_cylinder(&objects);
	if (error_check)
		return (error_check);
	objects->cylinder->base = split_coords(params[1]);
	if (!objects->cylinder->base)
		free_map(*map);
	objects->cylinder->vector = split_coords(params[2]);
	if (!objects->cylinder->vector)
		free_map(*map);
	objects->cylinder->diameter = ft_atoi(params[3]);
	objects->cylinder->height = ft_atoi(params[4]);
	objects->cylinder->color = split_color(params[5]);
	if (!objects->cylinder->color)
		free_map(*map);
	ft_lstadd_back(&(*map)->objects, objects);
	return (0);
}
