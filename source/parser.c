#include "../includes/miniRT.h"

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

	(void)map;
	(void)mlx_data;
	fd = -1;
	error_check = open_file(argc, argv, &fd);
	if (error_check)
		return (error_check);
	error_check = fill_params(fd, &params);
	if (error_check)
		return (error_check);
	//convert 
	//init_map
	//init_mlx_data
	return (error_check);
}
