/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maahoff <maahoff@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 11:12:53 by maahoff           #+#    #+#             */
/*   Updated: 2025/03/24 11:12:54 by maahoff          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	free_cube(t_cube *cube)
{
	if (!cube)
		return ;
	if (cube->square1)
		free(cube->square1);
	if (cube->square2)
		free(cube->square2);
	if (cube->square3)
		free(cube->square3);
	if (cube->square4)
		free(cube->square4);
	if (cube->square5)
		free(cube->square5);
	if (cube->square6)
		free(cube->square6);
	free(cube);
}
