#include "../../includes/miniRT.h"

#define GROUPS 60
#define FEATURES 6

int	init_camera(char **params, t_map **map)
{
	t_camera	*camera;
	int			error_check;

	error_check = 0;
	camera = malloc(sizeof(t_camera));
	if (!camera)
		return (ERR_NOMEM);
	camera->coords = split_coords(params[1]);
	if (!camera->coords)
	{
		free(camera);
		return (ERR_NOMEM);
	}
	camera->vector = split_coords(params[2]);
	if (!camera->vector)
	{
		free(camera->coords);
		free(camera);
		return (ERR_NOMEM);
	}
	camera->fov = ft_atoi(params[3]);
	(*map)->camera = camera;
	return (error_check);
}

int	init_light(char **params, t_map **map)
{
	t_light	*light;
	int		error_check;

	error_check = 0;
	light = malloc(sizeof(t_light));
	if (!light)
		return (ERR_NOMEM);
	light->source = split_coords(params[1]);
	if (params[1] && !light->source)
		return (ERR_NOMEM);
	light->brightness = ft_atof(params[2]);
	light->color = split_color(params[3]);
	if (params[3] && !light->color)
		return (ERR_NOMEM);
	(*map)->light = light;
	return (error_check);
}

int	init_ambient(char **params, t_map **map)
{
	t_ambient	*ambient;
	int			error_check;

	error_check = 0;
	ambient = malloc(sizeof(t_ambient));
	if (!ambient)
		return (ERR_NOMEM);
	ambient->brightness = ft_atof(params[1]);
	ambient->color = split_color(params[2]);
	if (!ambient->color)
	{
		free(ambient);
		return (ERR_NOMEM);
	}
	(*map)->ambient = ambient;
	return (error_check);
}

int	init_groups(char ***params, t_map **map)
{
	int	groups;
	int	error_check;

	error_check = 0;
	groups = 0;
	while (params[groups] && !error_check)
	{
		if (!ft_strcmp(params[groups][0], "A"))
			error_check = init_ambient(params[groups], map);
		else if (!ft_strcmp(params[groups][0], "C"))
			error_check = init_camera(params[groups], map);
		else if (!ft_strcmp(params[groups][0], "L"))
			error_check = init_light(params[groups], map);
		else if (!ft_strcmp(params[groups][0], "sp") || 
			!ft_strcmp(params[groups][0], "pl") || 
				!ft_strcmp(params[groups][0], "cy"))
			error_check = another_object(params[groups], map);
		groups++;
	}
	return (error_check);
}

int	init_map(char ***params, t_map **map)
{
	int	groups;
	int	error_check;

	groups = 0;
	*map = malloc(sizeof(t_map));
	if (!map)
		return (ERR_NOMEM);
	(*map)->ambient = NULL;
	(*map)->camera = NULL;
	(*map)->objects = NULL;
	(*map)->light = NULL;
	(*map)->viewport = NULL;
	error_check = init_groups(params, map);
	return (error_check);
}
