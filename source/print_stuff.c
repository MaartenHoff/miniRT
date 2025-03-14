/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_stuff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maahoff <maahoff@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:36:40 by maahoff           #+#    #+#             */
/*   Updated: 2025/03/14 14:52:48 by maahoff          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	print_map(t_map *map)
{
	t_objects	*obj;

	if (!map)
		return ;
	printf("map:\n");
	if (map->ambient)
	{
		printf("ambient:\n");
		printf("\tbrightness: [%lf]\n", map->ambient->brightness);
		if (map->ambient->color)
			printf("\tcolor: r:[%d] g:[%d] b:[%d]\n",
				map->ambient->color->r,
				map->ambient->color->g,
				map->ambient->color->b);
	}
	if (map->camera)
	{
		printf("camera:\n");
		if (map->camera->coords)
			printf("\tcoords: x:[%d] y:[%d] z:[%d]\n",
				map->camera->coords->x,
				map->camera->coords->y,
				map->camera->coords->z);
		if (map->camera->vector)
			printf("\tvector: x:[%d] y:[%d] z:[%d]\n",
				map->camera->vector->x,
				map->camera->vector->y,
				map->camera->vector->z);
		printf("\tfov: [%d]\n", map->camera->fov);
	}
	if (map->light)
	{
		printf("light:\n");
		if (map->light->source)
			printf("\tsource: x:[%d] y:[%d] z:[%d]\n",
				map->light->source->x,
				map->light->source->y,
				map->light->source->z);
		printf("\tbrightness: [%lf]\n", map->light->brightness);
		if (map->light->color)
			printf("\tcolor: r:[%d] g:[%d] b:[%d]\n",
				map->light->color->r,
				map->light->color->g,
				map->light->color->b);
	}
	if (map->objects)
	{
		obj = map->objects;
		while (obj)
		{
			if (obj->plane)
			{
				printf("plane:\n");
				if (obj->plane->point)
					printf("\tpoint: x:[%d] y:[%d] z:[%d]\n",
						obj->plane->point->x,
						obj->plane->point->y,
						obj->plane->point->z);
				if (obj->plane->vector)
					printf("\tvector: x:[%d] y:[%d] z:[%d]\n",
						obj->plane->vector->x,
						obj->plane->vector->y,
						obj->plane->vector->z);
				if (obj->plane->color)
					printf("\tcolor: r:[%d] g:[%d] b:[%d]\n",
						obj->plane->color->r,
						obj->plane->color->g,
						obj->plane->color->b);
			}
			if (obj->spheres)
			{
				printf("sphere:\n");
				if (obj->spheres->center)
					printf("\tcenter: x:[%d] y:[%d] z:[%d]\n",
						obj->spheres->center->x,
						obj->spheres->center->y,
						obj->spheres->center->z);
				printf("\tdiameter: [%lf]\n", obj->spheres->diameter);
				if (obj->spheres->color)
					printf("\tcolor: r:[%d] g:[%d] b:[%d]\n",
						obj->spheres->color->r,
						obj->spheres->color->g,
						obj->spheres->color->b);
			}
			if (obj->cylinder)
			{
				printf("cylinder:\n");
				if (obj->cylinder->base)
					printf("\tbase: x:[%d] y:[%d] z:[%d]\n",
						obj->cylinder->base->x,
						obj->cylinder->base->y,
						obj->cylinder->base->z);
				if (obj->cylinder->vector)
					printf("\tvector: x:[%d] y:[%d] z:[%d]\n",
						obj->cylinder->vector->x,
						obj->cylinder->vector->y,
						obj->cylinder->vector->z);
				printf("\tdiameter: [%lf]\n", obj->cylinder->diameter);
				printf("\theight: [%lf]\n", obj->cylinder->height);
				if (obj->cylinder->color)
					printf("\tcolor: r:[%d] g:[%d] b:[%d]\n",
						obj->cylinder->color->r,
						obj->cylinder->color->g,
						obj->cylinder->color->b);
			}
			obj = obj->next;
		}
	}
	printf("\n");
}
