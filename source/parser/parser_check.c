#include "../../includes/miniRT.h"

/*
 * #sp: [x,y,z] center    [diameter] (positive float)    [R,G,B]
 */
int	check_sphere(char **params)
{
	if (ft_arrlen(params) != 4)
		return (ERR_SP);
	if (ft_atof(params[2]) <= 0.0)
		return (ERR_SP);
	return (0);
}

/*
 * #pl: [x,y,z] point    [normal_vector]    [R,G,B]
 */
int	check_plane(char **params)
{
	if (ft_arrlen(params) != 4)
		return (ERR_PL);
	return (0);
}

/*
 * #cy: [x,y,z] base    [axis]    [diameter]    [height]    [R,G,B]
 */
int	check_cylinder(char **params)
{
	if (ft_arrlen(params) != 6)
		return (ERR_CY);
	if (ft_atof(params[3]) <= 0.0)
		return (ERR_CY);
	if (ft_atof(params[4]) <= 0.0)
		return (ERR_CY);
	return (0);
}

int	check_params(char ****params)
{
	int	error_check;
	int	i;

	i = -1;
	error_check = 0;
	while (params && (*params) && (*params)[++i] && !error_check)
	{
		if (!ft_strcmp((*params)[i][0], "A"))
			error_check = check_ambient((*params)[i]);
		else if (!ft_strcmp((*params)[i][0], "C"))
			error_check = check_camera((*params)[i]);
		else if (!ft_strcmp((*params)[i][0], "L"))
			error_check = check_light((*params)[i]);
		else if (!ft_strcmp((*params)[i][0], "sp"))
			error_check = check_sphere((*params)[i]);
		else if (!ft_strcmp((*params)[i][0], "pl"))
			error_check = check_plane((*params)[i]);
		else if (!ft_strcmp((*params)[i][0], "cy"))
			error_check = check_cylinder((*params)[i]);
		else
			return (free_params(*params), ERR_PARAM);
	}
	if (!(params && (*params)) || error_check)
		return (free_params(*params), ERR_PARAM);
	return (error_check);
}
