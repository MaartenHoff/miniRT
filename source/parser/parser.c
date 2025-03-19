#include "../../includes/miniRT.h"

int	calculate_viewport(t_map **map)
{
	t_coords	vec_right;
	t_coords	vec_up;
	t_coords	center;

	(*map)->viewport = malloc(sizeof(t_viewport));
	if (!(*map)->viewport)
		return (ERR_NOMEM);
	(*map)->viewport->height = fabs(tan((*map)->camera->fov / 2) * 2);
	if (WIDTH > HEIGHT)
		(*map)->viewport->width = (*map)->viewport->height * (WIDTH / HEIGHT);
	else
	{
		(*map)->viewport->width = (*map)->viewport->height;
		(*map)->viewport->height = (*map)->viewport->width * (HEIGHT / WIDTH);
	}
	vec_right = vec_mul(vec_norm(vec_cross((*map)->camera->vector, (t_coords){0, 1, 0})), (*map)->viewport->width / 2);
	vec_up = vec_mul(vec_norm(vec_cross(vec_right, (*map)->camera->vector)), (*map)->viewport->height / 2);
	center = vec_add((*map)->camera->coords, (*map)->camera->vector);
	(*map)->viewport->start = vec_add(center, 
			vec_add(vec_mul(vec_right, -1), vec_up));
	(*map)->viewport->x_vector = vec_mul(vec_norm(vec_right), 
			(*map)->viewport->width / WIDTH);
	(*map)->viewport->y_vector = vec_mul(vec_norm(vec_up), -1 * 
			(*map)->viewport->height / HEIGHT);
	return (0);
}

int	open_file(int argc, char **argv, int *fd)
{
	if (argc != 2)
		return (ERR_ARGC);
	*fd = open(argv[1], O_RDONLY);
	if (*fd < 0)
		return (ERR_FDFILE);
	if (ft_strlen(argv[1]) < 4 || ft_strcmp(".rt", argv[1] + 
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
	return (check_params(params));
}

int	parser(t_mlx_data **mlx_data, t_map **map, int argc, char **argv)
{
	int		error_check;
	int		fd;
	char	***params;

	fd = -1;
	if (argc < 2)
		return (ERR_ARGC);
	error_check = open_file(argc, argv, &fd);
	if (error_check)
		return (error_check);
	error_check = fill_params(fd, &params);
	if (error_check)
		return (error_check);
	init_mlx_data(mlx_data);
	error_check = init_map(params, map);
	free_params(params);
	error_check = calculate_viewport(map);
	return (error_check);
}
