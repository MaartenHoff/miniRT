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
	(*objects)->spheres->diameter = ft_atof(params[2]);
	(*objects)->spheres->radius = (*objects)->spheres->diameter / 2;
	(*objects)->spheres->color = split_color(params[3]);
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
	(*objects)->plane->vector = vec_norm(split_coords(params[2]));
	(*objects)->plane->color = split_color(params[3]);
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
	(*objects)->cylinder->vector = split_coords(params[2]);
	(*objects)->cylinder->diameter = ft_atof(params[3]);
	(*objects)->cylinder->height = ft_atof(params[4]);
	(*objects)->cylinder->color = split_color(params[5]);
	return (0);
}

int	another_object(char **params, t_map **map)
{
	t_objects	*new_object;
	t_objects	*tmp;
	int			error_check;

	new_object = malloc(sizeof(t_objects));
	if (!new_object)
		return (ERR_NOMEM);
	new_object->next = NULL;
	if (!ft_strcmp(params[0], "sp"))
		error_check = add_sphere(params, &new_object);
	else if (!ft_strcmp(params[0], "pl"))
		error_check = add_plane(params, &new_object);
	else
		error_check = add_cylinder(params, &new_object);
	if ((*map)->objects == NULL)
		(*map)->objects = new_object;
	else if (!error_check)
	{
		tmp = (*map)->objects;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_object;
	}
	return (error_check);
}
