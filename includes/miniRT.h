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
int			send_ray(t_mlx_data *mlx_data, t_map *map);

// init
int			init_mlx_data(t_mlx_data **mlx_data);

// hooks
int			close_window(t_mlx_data *mlx_data);
int			key_hook(int key_code, t_mlx_data *mlx_data);

// parser
int			parser(t_mlx_data **mlx_data, t_map **map, int argc, char **argv);
int			init_map(char ***params, t_map **map);
int			another_object(char **params, t_map **map);
//		utils
char		**tokenizer(char *line);
t_coords	*split_coords(char *str);
t_color		*split_color(char *str);

// error
int			handle_error(int error_code, t_map *map);

// free
void		free_map(t_map *map);
void		free_params(char ***params);

// testing
void		print_map(t_map *map);
#endif