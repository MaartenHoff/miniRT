#include "../../includes/miniRT.h"

int	add_sphere(char **params, t_objects **objects)
{
	(*objects)->next = NULL;
	(*objects)->type = SPHERE;
	(*objects)->plane = NULL;
	(*objects)->cylinder = NULL;
	(*objects)->spheres = malloc(sizeof(t_spheres));
	if (!(*objects)->spheres)
		return (ERR_NOMEM);
	(*objects)->spheres->center = split_coords(params[1]);
	if (!(*objects)->spheres->center)
		return (ERR_NOMEM);
	(*objects)->spheres->diameter = ft_atoi(params[2]);
	(*objects)->spheres->color = split_color(params[3]);
	if (!(*objects)->spheres->color)
		return (ERR_NOMEM);
	return (0);
}

int	add_plane(char **params, t_objects **objects)
{
	(*objects)->next = NULL;
	(*objects)->type = PLANE;
	(*objects)->spheres = NULL;
	(*objects)->cylinder = NULL;
	(*objects)->plane = malloc(sizeof(t_planes));
	if (!(*objects)->plane)
		return (ERR_NOMEM);
	(*objects)->plane->point = split_coords(params[1]);
	if (!(*objects)->plane->point)
		return (ERR_NOMEM);
	(*objects)->plane->vector = split_coords(params[2]);
	if (!(*objects)->plane->vector)
		return (ERR_NOMEM);
	(*objects)->plane->color = split_color(params[3]);
	if (!(*objects)->plane->color)
		return (ERR_NOMEM);
	return (0);
}

int	add_cylinder(char **params, t_objects **objects)
{
	(*objects)->next = NULL;
	(*objects)->type = CYLINDER;
	(*objects)->plane = NULL;
	(*objects)->spheres = NULL;
	(*objects)->cylinder = malloc(sizeof(t_cylinder));
	if (!(*objects)->cylinder)
		return (ERR_NOMEM);
	(*objects)->cylinder->base = split_coords(params[1]);
	if (!(*objects)->cylinder->base)
		return (ERR_NOMEM);
	(*objects)->cylinder->vector = split_coords(params[2]);
	if (!(*objects)->cylinder->vector)
		return (ERR_NOMEM);
	(*objects)->cylinder->diameter = ft_atoi(params[3]);
	(*objects)->cylinder->height = ft_atoi(params[4]);
	(*objects)->cylinder->color = split_color(params[5]);
	if (!(*objects)->cylinder->color)
		return (ERR_NOMEM);
	return (0);
}

int	another_object(char **params, t_map **map)
{
	t_objects	*start;
	int			error_check;

	start = (*map)->objects;
	while ((*map)->objects)
		(*map)->objects = (*map)->objects->next;
	(*map)->objects = malloc(sizeof(t_objects));
	if (!(*map)->objects)
		return (ERR_NOMEM);
	(*map)->objects->next = NULL;
	if (!ft_strcmp(params[0], "sp"))
		error_check = add_sphere(params, &(*map)->objects);
	else if (!ft_strcmp(params[0], "pl"))
		error_check = add_plane(params, &(*map)->objects);
	else
		error_check = add_cylinder(params, &(*map)->objects);
	(*map)->objects = start;
	return (error_check);
}
