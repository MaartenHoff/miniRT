#ifndef MINIRT_H
# define MINIRT_H

# define WIDTH	1000
# define HEIGHT	1000

# define MAX_INPUT 100

# define ESC	65307

# define ERR_NOMEM	12		// Memory allocation error
# define ERR_INVAL	22		// Invalid argument
# define ERR_ARGC	128		// Wrong number of arguments
# define ERR_FDFILE	130		// File cant open
# define ERR_NOTRT	131		// File is not a .rt file

# include <stdlib.h>
# include <stdio.h>	
# include <fcntl.h>
# include <unistd.h>
# include <math.h>

# include "structs.h"
# include "42mlx/mlx.h"
# include "libft/libft.h"

# define SPHERE 1
# define PLANE 2
# define CYLINDER 3


// ray_handling
t_coords		get_direction(t_map *map, int x, int y);
int				send_ray(t_map *map, t_coords direction);
int				sphere_hit(t_spheres *sphere, t_coords origin, t_coords 
					direction, t_hit *hit);
double			sphere_intersection(t_spheres *sphere, t_coords origin, 
					t_coords d);
int				cylinder_hit(t_map *map, t_coords origin, t_coords direction, 
					t_hit *hit);
int				plane_hit(t_map *map, t_coords origin, t_coords direction, 
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
//		utils
char			**tokenizer(char *line);
t_coords		split_coords(char *str);
t_color			split_color(char *str);

//	utils
// 		free
void			free_map(t_map *map);
void			free_params(char ***params);
// 		error
int				handle_error(int error_code, t_map *map);
// 		light_utils
int				color_to_int(t_color color);
t_color			light_hit_color(t_color light_color, double brightness, 
					t_color color);
t_light_data	light_plus_light(t_color light1, double brightness1, 
					t_color light2, double brightness2);
// 		vector_utils
t_coords		vec_create(t_coords point1, t_coords point2);
double			vec_len(t_coords vector);
t_coords		vec_norm(t_coords vector);
double			vec_skalar(t_coords vector1, t_coords vector2);
t_coords		vec_mul(t_coords vector, double scalar);
double			point_distance(t_coords point1, t_coords point2);
t_coords		vec_add(t_coords point1, t_coords point2);
t_coords		vec_cross(t_coords vector1, t_coords vector2);

// testing
void			print_map(t_map *map);
void			print_vektor(t_coords vector);
#endif