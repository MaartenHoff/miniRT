/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maahoff <maahoff@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:18:08 by maahoff           #+#    #+#             */
/*   Updated: 2025/02/20 18:42:23 by maahoff          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

# include "structs.h"
# include "42mlx/mlx.h"
# include "libft/libft.h"


// ray_handling
int		send_ray(t_mlx_data *mlx_data, t_map *map);

// parser
int		parser(t_mlx_data **mlx_data, t_map **map, int argc, char **argv);
char	**tokenizer(char *line);
int		init(t_mlx_data **mlx_data, t_map **map, int argc, char **argv);

// hooks
int		close_window(t_mlx_data *mlx_data);
int		key_hook(int key_code, t_mlx_data *mlx_data);

#endif