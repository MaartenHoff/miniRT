/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maahoff <maahoff@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:18:08 by maahoff           #+#    #+#             */
/*   Updated: 2025/02/16 21:01:21 by maahoff          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define WIDTH	1000
# define HEIGHT	1000

# define ESC	65307

# include "structs.h"
# include "42mlx/mlx.h"
# include "libft/libft.h"
# include <stdlib.h>

int	close_window(t_data *data);
int	key_hook(int key_code, t_data *data);

#endif