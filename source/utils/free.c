/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maahoff <maahoff@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 11:12:57 by maahoff           #+#    #+#             */
/*   Updated: 2025/03/24 11:12:58 by maahoff          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

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
	free(sphere);
}

void	free_plane(t_planes *plane)
{
	if (!plane)
		return ;
	free(plane);
}

void	free_cylinder(t_cylinder *cylinder)
{
	if (!cylinder)
		return ;
	if (cylinder->plane1)
		free(cylinder->plane1);
	if (cylinder->plane2)
		free(cylinder->plane2);
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
		else if (temp->type == CUBE)
			free_cube(temp->cube);
		temp = temp->next;
		ft_memdel((void **)&(map->objects));
		map->objects = temp;
	}
	free(map->vp);
	free(map->ambient);
	free(map->camera);
	free(map->light);
	free(map);
}
