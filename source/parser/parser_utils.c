#include "../../includes/miniRT.h"

t_color	*split_color(char *str)
{
	t_color	*color;
	char	**split;

	color = malloc(sizeof(t_color));
	if (!color)
		return (NULL);
	split = ft_split(str, ',');
	if (!split)
		return (free(color), NULL);
	color->r = ft_atoi(split[0]);
	color->g = ft_atoi(split[1]);
	color->b = ft_atoi(split[2]);
	ft_free_array(split);
	return (color);
}

t_coords	*split_coords(char *str)
{
	t_coords	*coords;
	char		**split;

	coords = malloc(sizeof(t_coords));
	if (!coords)
		return (NULL);
	split = ft_split(str, ',');
	if (!split)
	{
		free(coords);
		return (NULL);
	}
	coords->x = ft_atof(split[0]);
	coords->y = ft_atof(split[1]);
	coords->z = ft_atof(split[2]);
	ft_free_array(split);
	return (coords);
}
