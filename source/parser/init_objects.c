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
	(*objects)->cylinder->vector = vec_norm(split_coords(params[2]));
	(*objects)->cylinder->diameter = ft_atof(params[3]);
	(*objects)->cylinder->radius = (*objects)->cylinder->diameter / 2;
	(*objects)->cylinder->height = ft_atof(params[4]);
	(*objects)->cylinder->color = split_color(params[5]);
	(*objects)->cylinder->plane1 = malloc(sizeof(t_planes));
	(*objects)->cylinder->plane2 = malloc(sizeof(t_planes));
	(*objects)->cylinder->plane1->point = (*objects)->cylinder->base;
	(*objects)->cylinder->plane1->vector = (*objects)->cylinder->vector;
	(*objects)->cylinder->plane2->point = vec_add((*objects)->cylinder->base, 
			vec_mul((*objects)->cylinder->vector, 
				(*objects)->cylinder->height));
	(*objects)->cylinder->plane2->vector = (*objects)->cylinder->vector;
	return (0);
}

int	add_cube_squares(t_cube *cube)
{
	cube->square1 = malloc(sizeof(t_planes));
	cube->square2 = malloc(sizeof(t_planes));
	cube->square3 = malloc(sizeof(t_planes));
	cube->square4 = malloc(sizeof(t_planes));
	cube->square5 = malloc(sizeof(t_planes));
	cube->square6 = malloc(sizeof(t_planes));
	cube->square1->point = vec_add(cube->center, (t_coords){cube->center.x
			+ cube->size, cube->center.y, cube->center.z});
	cube->square1->vector = (t_coords){1, 0, 0};
	cube->square2->point = vec_add(cube->center, (t_coords){cube->center.x
			- cube->size, cube->center.y, cube->center.z});
	cube->square2->vector = (t_coords){-1, 0, 0};
	cube->square3->point = vec_add(cube->center, (t_coords){cube->center.x,
			cube->center.y + cube->size, cube->center.z});
	cube->square3->vector = (t_coords){0, 1, 0};
	cube->square4->point = vec_add(cube->center, (t_coords){cube->center.x,
			cube->center.y - cube->size, cube->center.z});
	cube->square4->vector = (t_coords){0, -1, 0};
	cube->square5->point = vec_add(cube->center, (t_coords){cube->center.x,
			cube->center.y, cube->center.z + cube->size});
	cube->square5->vector = (t_coords){0, 0, 1};
	cube->square6->point = vec_add(cube->center, (t_coords){cube->center.x,
			cube->center.y, cube->center.z - cube->size});
	cube->square6->vector = (t_coords){0, 0, -1};
	return (0);
}

int	add_cube(char **params, t_objects **objects)
{
	(*objects)->next = NULL;
	(*objects)->type = CUBE;
	(*objects)->plane = NULL;
	(*objects)->spheres = NULL;
	(*objects)->cylinder = NULL;
	(*objects)->cube = malloc(sizeof(t_cube));
	if (!(*objects)->cube)
		return (ERR_NOMEM);
	(*objects)->cube->center = split_coords(params[1]);
	(*objects)->cube->size = ft_atof(params[2]);
	if (add_cube_squares((*objects)->cube) == ERR_NOMEM)
		return (ERR_NOMEM);
	(*objects)->cube->color = split_color(params[3]);
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
