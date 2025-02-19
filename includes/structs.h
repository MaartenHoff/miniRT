/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maahoff <maahoff@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:51:53 by maahoff           #+#    #+#             */
/*   Updated: 2025/02/19 16:10:45 by maahoff          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_coords
{
	int	x;
	int	y;
	int	z;
}	t_coords;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_spheres
{
	t_coords	center;
	double		radius;
	t_color		color;
}	t_spheres;

typedef struct s_planes
{
	t_coords	point;
	t_coords	vector;
	t_color		color;
}	t_planes;

typedef struct s_cylinder
{
	t_coords	base;
	t_coords	vector;
	double		radius;
	double		height;
	t_color		color;
}	t_cylinder;

typedef struct s_objects
{
	t_planes	*plane;
	t_spheres	*spheres;
	t_cylinder	*cylinder;
}	t_objects;

typedef struct s_light
{
	t_coords	source;
	double		ambiance;
}	t_light;
typedef struct s_map
{
	t_coords	camera;
	t_objects	*objects;
	t_light		*light;
}	t_map;

typedef struct s_mlx_data
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_mlx_data;

#endif