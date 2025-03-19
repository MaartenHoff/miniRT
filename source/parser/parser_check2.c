#include "../../includes/miniRT.h"

/*
 * #A: [ambient_ratio]: 0.0-1.0    [R,G,B]: 0 to 255
 */
int	check_ambient(char **params)
{
	if (ft_arrlen(params) != 3)
		return (ERR_A);
	if (ft_atof(params[1]) < 0.0
		|| ft_atof(params[1]) > 1.0)
		return (ERR_A);
	return (0);
}

//* #C: [x,y,z] position    [orientation] (e.g. 0,0,1)    
//[FOV]: Field of view 0-180 degrees
int	check_camera(char **params)
{
	if (ft_arrlen(params) != 4)
		return (ERR_C);
	if (ft_atoi(params[3]) < 0
		|| ft_atoi(params[3]) > 180)
		return (ERR_C);
	return (0);
}

/*
 * #L: [x,y,z] position    [brightness] 0.0-1.0    ([R,G,B] is optional)
 */
int	check_light(char **params)
{
	int	len;

	len = ft_arrlen(params);
	if (len != 3 && len != 4)
		return (ERR_L);
	if (ft_atof(params[2]) < 0.0 || ft_atof(params[2]) > 1.0)
		return (ERR_L);
	return (0);
}
