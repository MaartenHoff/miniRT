#include "../../includes/miniRT.h"

int	alloc_shere(t_objects **objects)
{
	t_spheres	*spheres;

	*objects = malloc(sizeof(t_objects));
	if (!(*objects))
		return (ERR_NOMEM);
	spheres = malloc(sizeof(t_spheres));
	if (!spheres)
		return (ERR_NOMEM);
	(*objects)->type = SPHERE;
	(*objects)->spheres = spheres;
	(*objects)->next = NULL;
	return (0);
}

int	alloc_plane(t_objects **objects)
{
	t_planes	*plane;

	*objects = malloc(sizeof(t_objects));
	if (!(*objects))
		return (ERR_NOMEM);
	plane = malloc(sizeof(t_planes));
	if (!plane)
		return (ERR_NOMEM);
	(*objects)->type = PLANE;
	(*objects)->plane = plane;
	(*objects)->next = NULL;
	return (0);
}

int	alloc_cylinder(t_objects **objects)
{
	t_cylinder	*cylinder;

	*objects = malloc(sizeof(t_objects));
	if (!(*objects))
		return (ERR_NOMEM);
	cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder)
		return (ERR_NOMEM);
	(*objects)->type = CYLINDER;
	(*objects)->cylinder = cylinder;
	(*objects)->next = NULL;
	return (0);
}

t_color	*split_color(char *str)
{
	t_color	*color;
	char	**split;

	color = malloc(sizeof(t_color));
	if (!color)
		return (NULL);
	split = ft_split(str, ',');
	if (!split)
		return (NULL);
	color->r = ft_atoi(split[0]);
	color->g = ft_atoi(split[1]);
	color->b = ft_atoi(split[2]);
	ft_free_array(split);
	return (color);
}

t_coords	*split_coords(char *str)
{
	t_coords	*coords;
	char		**split;

	coords = malloc(sizeof(t_coords));
	if (!coords)
		return (NULL);
	split = ft_split(str, ',');
	if (!split)
	{
		free(coords);
		return (NULL);
	}
	coords->x = ft_atoi(split[0]);
	coords->y = ft_atoi(split[1]);
	coords->z = ft_atoi(split[2]);
	ft_free_array(split);
	return (coords);
}
