#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_coords
{
	double	x;
	double	y;
	double	z;
}	t_coords;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_spheres
{
	t_coords	*center;
	double		diameter;
	double		radius;
	t_color		*color;
}	t_spheres;

typedef struct s_planes
{
	t_coords	*point;
	t_coords	*vector;
	t_color		*color;
}	t_planes;

typedef struct s_cylinder
{
	t_coords	*base;
	t_coords	*vector;
	double		diameter;
	double		height;
	t_color		*color;
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
	t_coords	*source;
	double		brightness;
	t_color		*color;
}	t_light;

typedef struct s_camera
{
	t_coords	*coords;
	t_coords	*vector;
	int			fov;
}	t_camera;

typedef struct s_ambient
{
	double	brightness;
	t_color	*color;
}	t_ambient;

typedef struct s_hit {
	t_coords	*point;
	t_coords	*normal;
	double		distance;
	t_color		*color;
}	t_hit;

typedef struct s_viewport
{
	double		height;
	double		width;
	t_coords	*start;
	t_coords	*x_vector;
	t_coords	*y_vector;
}	t_viewport;

typedef struct s_map
{
	t_ambient	*ambient;
	t_camera	*camera;
	t_objects	*objects;
	t_light		*light;
	t_viewport	*viewport;
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