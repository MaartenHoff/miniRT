#include "../../includes/miniRT.h"

t_color	split_color(char *str)
{
	t_color	color;
	char	**split;

	split = ft_split(str, ',');
	if (!split)
		return ((t_color){});
	color.r = ft_atoi(split[0]);
	color.g = ft_atoi(split[1]);
	color.b = ft_atoi(split[2]);
	ft_free_array(split);
	return (color);
}

t_coords	split_coords(char *str)
{
	t_coords	coords;
	char		**split;

	split = ft_split(str, ',');
	if (!split)
		return ((t_coords){});
	coords.x = ft_atof(split[0]);
	coords.y = ft_atof(split[1]);
	coords.z = ft_atof(split[2]);
	ft_free_array(split);
	return (coords);
}

int	is_valid_color(const char *str)
{
	char	**col;
	int		i;
	int		n;

	col = ft_split(str, ',');
	if (!col)
		return (0);
	i = 0;
	while (col[i])
	{
		n = ft_atoi(col[i]);
		if (n < 0 || n > 255) 
			return (ft_free_array(col), 0);
		i++;
	}
	if (i != 3)
		return (ft_free_array(col), 0);
	ft_free_array(col);
	return (1);
}

static int	is_valid_double(const char *s)
{
	int	i;
	int	digit_found;

	i = 0;
	digit_found = 0;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i] && ft_isdigit(s[i]))
	{
		digit_found = 1;
		i++;
	}
	if (s[i] == '.')
	{
		i++;
		while (s[i] && ft_isdigit(s[i]))
		{
			digit_found = 1;
			i++;
		}
	}
	if (!digit_found || s[i] != '\0')
		return (0);
	return (1);
}

int	is_valid_coordinates(const char *str)
{
	char	**coords;
	int		i;
	int		count;
	int		valid;

	coords = ft_split(str, ',');
	if (!coords)
		return (0);
	count = 0;
	while (coords[count])
		count++;
	if (count != 3)
		valid = 0;
	else
	{
		valid = 1;
		i = 0;
		while (i < count && valid)
		{
			if (!is_valid_double(coords[i]))
				valid = 0;
			i++;
		}
	}
	return (ft_free_array(coords), valid);
}
