/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiler <adiler@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:18:08 by maahoff           #+#    #+#             */
/*   Updated: 2025/02/20 18:52:36 by adiler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define WIDTH	1000
# define HEIGHT	1000

# define ESC	65307

# define ERR_NOMEM	12		// Memory allocation error
# define ERR_INVAL	22		// Invalid argument
# define ERR_ARGC	128		// Wrong number of arguments

# include <stdlib.h>
# include <stdio.h>	
# include <fcntl.h>
# include <unistd.h>

# include "structs.h"
# include "42mlx/mlx.h"
# include "libft/libft.h"


// ray_handling
int	send_ray(t_mlx_data *mlx_data, t_map *map);

// init
int	init_mlx_data(t_mlx_data **mlx_data);

// hooks
int		close_window(t_mlx_data *mlx_data);
int		key_hook(int key_code, t_mlx_data *mlx_data);

// parser
int	parser(t_mlx_data **mlx_data, t_map **map, int argc, char **argv);

#endif