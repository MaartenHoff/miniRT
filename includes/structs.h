/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maahoff <maahoff@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:51:53 by maahoff           #+#    #+#             */
/*   Updated: 2025/02/20 16:47:37 by maahoff          ###   ########.fr       */
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
	double		diameter;
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
	double		diameter;
	double		height;
	t_color		color;
}	t_cylinder;

typedef struct s_objects
{
	int					type;
	t_planes			*plane;
	t_spheres			*spheres;
	t_cylinder			*cylinder;
	struct s_objects	*next;
}	t_objects;

typedef struct s_light
{
	t_coords	source;
	double		brightness;
	t_color		color;
}	t_light;

typedef struct s_camera
{
	t_coords	coords;
	t_coords	vector;
	int			fov;
}	t_camera;

typedef struct s_ambient
{
	double	brightness;
	t_color	color;
}	t_ambient;

typedef struct s_map
{
	t_ambient	*ambient;
	t_camera	*camera;
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