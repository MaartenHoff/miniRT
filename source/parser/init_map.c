/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maahoff <maahoff@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 11:15:53 by maahoff           #+#    #+#             */
/*   Updated: 2025/03/24 11:15:54 by maahoff          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	camera->vector = vec_norm(split_coords(params[2]));
	camera->fov = ft_atoi(params[3]) * (M_PI / 180);
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
	light->brightness = ft_atof(params[2]);
	light->color = split_color(params[3]);
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
				!ft_strcmp(params[groups][0], "cy") || 
					!ft_strcmp(params[groups][0], "cu"))
			error_check = another_object(params[groups], map);
		groups++;
	}
	return (error_check);
}

int	init_map(char ***params, t_map **map)
{
	int	error_check;

	*map = malloc(sizeof(t_map));
	if (!map)
		return (ERR_NOMEM);
	(*map)->ambient = NULL;
	(*map)->camera = NULL;
	(*map)->objects = NULL;
	(*map)->light = NULL;
	(*map)->vp = NULL;
	error_check = init_groups(params, map);
	return (error_check);
}
