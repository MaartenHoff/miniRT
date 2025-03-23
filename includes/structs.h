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

typedef struct s_light_data
{
	t_color	color;
	double	brightness;
}	t_light_data;

typedef struct s_spheres
{
	t_coords	center;
	double		diameter;
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
	double		diameter;
	double		radius;
	double		height;
	t_color		color;
	t_planes	*plane1;
	t_planes	*plane2;
}	t_cylinder;

typedef struct s_cube
{
	t_coords	center;
	double		size;
	t_planes	*square1;
	t_planes	*square2;
	t_planes	*square3;
	t_planes	*square4;
	t_planes	*square5;
	t_planes	*square6;
	t_color		color;
}	t_cube;

typedef struct s_objects
{
	int					type;
	t_planes			*plane;
	t_spheres			*spheres;
	t_cylinder			*cylinder;
	t_cube				*cube;
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
	double		fov;
}	t_camera;

typedef struct s_ambient
{
	double	brightness;
	t_color	color;
}	t_ambient;

typedef struct s_hit {
	t_coords	point;
	t_coords	normal;
	double		distance;
	t_color		color;
}	t_hit;

typedef struct s_vp
{
	double		height;
	double		width;
	t_coords	start;
	t_coords	x_vector;
	t_coords	y_vector;
}	t_vp;

typedef struct s_map
{
	t_ambient	*ambient;
	t_camera	*camera;
	t_objects	*objects;
	t_light		*light;
	t_vp		*vp;
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