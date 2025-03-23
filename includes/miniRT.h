#ifndef MINIRT_H
# define MINIRT_H

# define WIDTH	1000
# define HEIGHT	1000

# define SHININESS		100
# define SPEKULARFAKTOR	1

// Plastik			10 - 50		0.5 - 0.7
// Metall			100 - 500	0.8 - 1.0
// Glas				200 - 500	0.9 - 1.0
// Marmor			50 - 200	0.6 - 0.9
// Holz (poliert)	10 - 50		0.3 - 0.6
// Holz (rau)		1 - 10		0.1 - 0.3
// Haut				5 - 20		0.2 - 0.5

# define MAX_INPUT 100

# define ESC	65307

# define ERR_NOMEM	12		// Memory allocation error
# define ERR_INVAL	22		// Invalid argument
# define ERR_ARGC	128		// Wrong number of arguments
# define ERR_FDFILE	130		// File cant open
# define ERR_NOTRT	131		// File is not a .rt file
// params
# define ERR_PARAM	132		// Params error: Incorrect parameter format or count
# define ERR_A		133		// Ambient error: Invalid ambient light parameters
# define ERR_C		134		// Camera error: Invalid camera parameters
# define ERR_L		135		// Light error: Invalid light parameters
# define ERR_OBJ	139		// No object
# define ERR_SP		136		// Sphere error: Invalid sphere parameters
# define ERR_PL		137		// Plane error: Invalid plane parameters
# define ERR_CY		138		// Cylinder error: Invalid cylinder parameters
# define ERR_CU		139		// Cube error: Invalid cube parameters

# include <stdlib.h>
# include <stdio.h>	
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include <float.h>

# include "structs.h"
# include "42mlx/mlx.h"
# include "libft/libft.h"

# define SPHERE 1
# define PLANE 2
# define CYLINDER 3
# define CUBE 4

// ray_handling
t_coords		get_direction(t_map *map, int x, int y);
int				send_ray(t_map *map, t_coords direction);
int				sphere_hit(t_spheres *sphere, t_coords origin, t_coords 
					direction, t_hit *hit);
double			sphere_intersection(t_spheres *sphere, t_coords origin, 
					t_coords d);
int				plane_hit(t_planes *plane, t_coords origin, t_coords direction, 
					t_hit *hit);
double			plane_intersection(t_planes *plane, t_coords origin, 
					t_coords direction);
int				cylinder_hit(t_cylinder *cylinder_hit, t_coords origin, 
					t_coords direction, t_hit *hit);
double			mantle_intersection(t_cylinder *cylinder, t_coords origin,
					t_coords direction);
int				cube_hit(t_cube *cube, t_coords origin, t_coords direction,	
					t_hit *hit);

// hooks
int				close_window(t_mlx_data *mlx_data);
int				key_hook(int key_code, t_mlx_data *mlx_data);

// parser
int				parser(t_mlx_data **mlx_data, t_map **map, int argc, 
					char **argv);
int				init_map(char ***params, t_map **map);
int				init_mlx_data(t_mlx_data **mlx_data);
int				another_object(char **params, t_map **map);
int				add_cube(char **params, t_objects **objects);
//		utils
int				check_params(char ****params);
char			**tokenizer(char *line);
t_coords		split_coords(char *str);
t_color			split_color(char *str);
int				check_objects(char **params, int **check);
double			solve_quadratic(double a, double b, double c);
double			get_lowest_but_positve_t(double plane1_t, double plane2_t,
					double mantle_t);
int				is_valid_coordinates(const char *str);
int				is_valid_color(const char *str);

//	utils
// 		free
void			free_map(t_map *map);
void			free_params(char ***params);
void			free_cube(t_cube *cube);
// 		error
int				handle_error(int error_code, t_map *map);
// 		light_utils
int				color_to_int(t_color color);
t_color			add_specular(t_color final_color, t_color light_color, 
					double specular_intensity);
t_color			light_hit_color(t_color light_color, double brightness, 
					t_color color);
t_light_data	light_plus_light(t_color light1, double brightness1, 
					t_color light2, double brightness2);
// 		vector_utils
t_coords		vec_create(t_coords point1, t_coords point2);
double			vec_len(t_coords vector);
t_coords		vec_norm(t_coords vector);
t_coords		vec_sub(t_coords point1, t_coords point2);
double			vec_skalar(t_coords vector1, t_coords vector2);
t_coords		vec_mul(t_coords vector, double scalar);
double			point_distance(t_coords point1, t_coords point2);
t_coords		vec_add(t_coords point1, t_coords point2);
t_coords		vec_cross(t_coords vector1, t_coords vector2);

#endif