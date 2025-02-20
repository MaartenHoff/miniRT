#include "../includes/miniRT.h"

#define GROUPS 60
#define FEATURES 6

int	init_map(char ***params, t_map **map);

int	open_file(int argc, char **argv, int *fd)
{
	if (argc != 2)
		return (ERR_ARGC);
	*fd = open(argv[1], O_RDONLY);
	if (*fd < 0)
		return (ERR_FDFILE);
	if (ft_strlen(argv[1]) < 4 && ft_strcmp(".rt", argv[1] + 
			(ft_strlen(argv[1]) - 3)))
		return (ERR_NOTRT);
	return (0);
}

int	fill_params(int fd, char ****params)
{
	char	*line;
	int		i;

	*params = malloc(sizeof(char **) * MAX_INPUT);
	if (!params)
		return (ERR_NOMEM);
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		(*params)[i] = tokenizer(line);
		if (!(*params)[i]) 
			return (ERR_NOMEM);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	(*params)[i] = NULL;
	return (0);
}


int	parser(t_mlx_data **mlx_data, t_map **map, int argc, char **argv)
{
	int		error_check;
	int		fd;
	char	***params;
	
	fd = -1;
	error_check = open_file(argc, argv, &fd);
	if (error_check)
		return (error_check);
	error_check = fill_params(fd, &params);
	if (error_check)
		return (error_check);
	init_mlx_data(mlx_data);
	error_check = init_map(params, map);
	return (error_check);
}

int	init_map(char ***params, t_map **map)
{
	int groups;
	int error_check;

	error_check = 0;
	groups = 0;
	*map = malloc(sizeof(t_map));
	if (!map)
		return (ERR_NOMEM);
	(*map)->ambient = NULL;
	(*map)->camera = NULL;
	(*map)->objects = NULL;
	(*map)->light = NULL;
	while(params[groups])
	{
		if (params[groups][0] == "A")
			error_check = init_ambient(params[groups], map);
		else if (params[groups][0] == "C")
			error_check = init_camera(params[groups], map);
		else if (params[groups][0] == "L")
			error_check = init_light(params[groups], map);
		else if (params[groups][0] == "sp")
			error_check = init_sphere(params[groups], map);
		else if (params[groups][0] == "pl")
			error_check = init_plane(params[groups], map);
		else if (params[groups][0] == "cy")
			error_check = init_cylinder(params[groups], map);
		groups++;
	}
	return (0);
}

int	init_ambient(char **params, t_map **map)
{
	t_ambient	*ambient;
	char		**split;
	int			error_check;

	error_check = 0;
	ambient = malloc(sizeof(t_ambient));
	if (!ambient)
		return (ERR_NOMEM);
	split = ft_split(params[1], ',');
	ambient->brightness = ft_atof(split[0]); //ft_atof
	split = ft_split(params[2], ',');
	ambient->color.r = ft_atoi(split[0]);
	ambient->color.g = ft_atoi(split[1]);
	ambient->color.b = ft_atoi(split[2]);
	(*map)->ambient = ambient;
	return (error_check);
}

// int init_camera(char **params, t_map **map)
// {
	
// }
