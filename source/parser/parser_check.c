/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maahoff <maahoff@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 11:15:25 by maahoff           #+#    #+#             */
/*   Updated: 2025/03/24 12:00:00 by maahoff          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

//#A: [ambient_ratio]: 0.0-1.0    [R,G,B]: 0 to 255
int	check_ambient(char **params, int **check)
{
	(*check)[0]++;
	if ((*check)[0] > 1)
		return (ERR_A);
	if (ft_arrlen(params) != 3)
		return (ERR_A);
	if (ft_atof(params[1]) < 0.0
		|| ft_atof(params[1]) > 1.0)
		return (ERR_A);
	if (params[2] && !is_valid_color(params[2]))
		return (ERR_A);
	return (0);
}

//* #C: [x,y,z] position  [x,y,z] (orientation)  [FOV]: Field of view 0-180
int	check_camera(char **params, int **check)
{
	(*check)[1]++;
	if ((*check)[1] > 1)
		return (ERR_C);
	if (ft_arrlen(params) != 4)
		return (ERR_C);
	if (ft_atoi(params[3]) < 0
		|| ft_atoi(params[3]) > 180)
		return (ERR_C);
	if (!is_valid_coordinates(params[1]) || !is_valid_coordinates(params[2]))
		return (ERR_C);
	return (0);
}

// #L: [x,y,z] position    [brightness] 0.0-1.0    ([R,G,B] is optional)
int	check_light(char **params, int **check)
{
	int			len;

	(*check)[2]++;
	if ((*check)[2] > 1)
		return (ERR_L);
	len = ft_arrlen(params);
	if (len != 3 && len != 4)
		return (ERR_L);
	if (ft_atof(params[2]) < 0.0 || ft_atof(params[2]) > 1.0)
		return (ERR_L);
	if (!is_valid_coordinates(params[1]))
		return (ERR_L);
	if (params[3] && !is_valid_color(params[3]))
		return (ERR_L);
	return (0);
}

int	check_map(char ***params, int **check)
{
	int	i;
	int	error_check;

	i = -1;
	error_check = 0;
	if (!params || !(*params) || !(**params))
		return (ERR_PARAM);
	while (params && params[++i] && !error_check)
	{
		if (params[i][0] && !ft_strcmp(params[i][0], "A"))
			error_check = check_ambient(params[i], check);
		else if (params[i][0] && !ft_strcmp(params[i][0], "C"))
			error_check = check_camera(params[i], check);
		else if (params[i][0] && !ft_strcmp(params[i][0], "L"))
			error_check = check_light(params[i], check);
		else if (params[i][0] && (!ft_strcmp(params[i][0], "sp") || 
			!ft_strcmp(params[i][0], "pl") || 
			!ft_strcmp(params[i][0], "cy") ||
			!ft_strcmp(params[i][0], "cu")))
			error_check = check_objects(params[i], check);
		else
			return (ERR_PARAM);
	}
	return (error_check);
}

int	check_params(char ****params)
{
	int	error_check;
	int	*check;

	check = malloc(sizeof(int) * 4);
	if (!check)
		return (ERR_NOMEM);
	check[0] = 0;
	check[1] = 0;
	check[2] = 0;
	check[3] = 0;
	error_check = check_map(*params, &check);
	if (error_check)
		return (free(check), free_params(*params), error_check);
	if (check[0] < 1)
		return (free(check), free_params(*params), ERR_A);
	if (check[1] < 1)
		return (free(check), free_params(*params), ERR_C);
	if (check[2] < 1)
		return (free(check), free_params(*params), ERR_L);
	if (check[3] < 1)
		return (free(check), free_params(*params), ERR_OBJ);
	return (free(check), error_check);
}
