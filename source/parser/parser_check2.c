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

/*
 * #cu: [x,y,z] center    [x, y, z] vector		[size]    [R,G,B]
 */
int	check_cube(char **params)
{
	if (ft_arrlen(params) != 5)
		return (ERR_CU);
	if (ft_atof(params[3]) <= 0.0)
		return (ERR_CU);
	return (0);
}

int	check_objects(char **params, int **check)
{
	int	error_check;

	(*check)[3]++;
	error_check = 0;
	if (!ft_strcmp(params[0], "sp"))
		error_check = check_sphere(params);
	else if (!ft_strcmp(params[0], "pl"))
		error_check = check_plane(params);
	else if (!ft_strcmp(params[0], "cy"))
		error_check = check_cylinder(params);
	else if (!ft_strcmp(params[0], "cu"))
		error_check = check_cube(params);
	else
		return (ERR_PARAM);
	return (error_check);
}
