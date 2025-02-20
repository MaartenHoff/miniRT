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

t_coords *split_coords(char *str)
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
	coords->x = ft_atoi(split[0]);
	coords->y = ft_atoi(split[1]);
	coords->z = ft_atoi(split[2]);
	ft_free_array(split);
	return (coords);
}

t_color *split_color(char *str)
{
	t_color	*color;
	char	**split;

	color = malloc(sizeof(t_color));
	if (!color)
		return (NULL);
	split = ft_split(str, ',');
	if (!split)
	{
		free(color);
		return (NULL);
	}
	color->r = ft_atoi(split[0]);
	color->g = ft_atoi(split[1]);
	color->b = ft_atoi(split[2]);
	ft_free_array(split);
	return (color);
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
	ambient->brightness = ft_atof(params[1]);
	ambient->color = split_color(params[2]);
	if (!ambient->color)
	{
		free(ambient);
		return (ERR_NOMEM);
	}

	(*map)->ambient = ambient;
	return (error_check);
}

int init_camera(char **params, t_map **map)
{
	t_camera	*camera;
	char		**split;
	int			error_check;

	error_check = 0;
	camera = malloc(sizeof(t_camera));
	if (!camera)
		return (ERR_NOMEM);
	camera->coords = split_coords(params[1]);
	if (!camera->coords)
	{
		free(camera);
		return (ERR_NOMEM);
	}
	camera->vector = split_coords(params[2]);
	if (!camera->vector)
	{
		free(camera->coords);
		free(camera);
		return (ERR_NOMEM);
	}
	camera->fov = ft_atoi(params[3]);
	(*map)->camera = camera;
	return (error_check);
}

int	init_light(char **params, t_map **map)
{
	t_light		*light;
	char		**split;
	int			error_check;

	error_check = 0;
	light = malloc(sizeof(t_light));
	if (!light)
		return (ERR_NOMEM);
	light->source = split_coords(params[1]);
	if (!light->source)
		free_map(*map);
	light->brightness = ft_atof(params[2]);
	light->color = split_color(params[3]);
	if (!light->color)
		free_map(*map);
	(*map)->light = light;
	return (error_check);
}

int	alloc_shere(t_objects **objects)
{
	t_spheres	*spheres;

	*objects = malloc(sizeof(t_objects));
	if (!(*objects))
		return (ERR_NOMEM);
	spheres = malloc(sizeof(t_spheres));
	if (!spheres)
		return (ERR_NOMEM);
	(*objects)->type = SPHERE;
	(*objects)->spheres = spheres;
	(*objects)->next = NULL;
	return (0);
}

int	init_sphere(char **params, t_map **map)
{
	t_objects	*objects;
	char		**split;
	int			error_check;

	error_check = 0;
	objects = alloc_sphere(map);
	if (!objects)
		return (error_check);
	objects->spheres->center = split_coords(params[1]);
	if (!objects->spheres->center)
		free_map(*map);
	objects->spheres->diameter = ft_atoi(params[2]);
	objects->spheres->color = split_color(params[3]);
	if (!objects->spheres->color)
		free_map(*map);
	ft_lstadd_back(&(*map)->objects, objects);
	return (error_check);
}

int alloc_plane(t_objects **objects)
{
    t_planes *plane;

    *objects = malloc(sizeof(t_objects));
    if (!(*objects))
        return (ERR_NOMEM);
    plane = malloc(sizeof(t_planes));
    if (!plane)
        return (ERR_NOMEM);
    (*objects)->type = PLANE;
    (*objects)->plane = plane;
    (*objects)->next = NULL;
    return (0);
}

int alloc_cylinder(t_objects **objects)
{
    t_cylinder *cylinder;

    *objects = malloc(sizeof(t_objects));
    if (!(*objects))
        return (ERR_NOMEM);
    cylinder = malloc(sizeof(t_cylinder));
    if (!cylinder)
        return (ERR_NOMEM);
    (*objects)->type = CYLINDER;
    (*objects)->cylinder = cylinder;
    (*objects)->next = NULL;
    return (0);
}

int init_plane(char **params, t_map **map)
{
    t_objects *objects;
    int error_check = alloc_plane(&objects);
    if (error_check)
        return error_check;
    
    objects->plane->point = split_coords(params[1]);
    if (!objects->plane->point)
        free_map(*map);
    objects->plane->vector = split_coords(params[2]);
    if (!objects->plane->vector)
        free_map(*map);
    objects->plane->color = split_color(params[3]);
    if (!objects->plane->color)
        free_map(*map);
    
    ft_lstadd_back(&(*map)->objects, objects);
    return 0;
}

int init_cylinder(char **params, t_map **map)
{
    t_objects *objects;
    int error_check = alloc_cylinder(&objects);
    if (error_check)
        return error_check;
    
    objects->cylinder->base = split_coords(params[1]);
    if (!objects->cylinder->base)
        free_map(*map);
    objects->cylinder->vector = split_coords(params[2]);
    if (!objects->cylinder->vector)
        free_map(*map);
    objects->cylinder->diameter = ft_atoi(params[3]);
    objects->cylinder->height = ft_atoi(params[4]);
    objects->cylinder->color = split_color(params[5]);
    if (!objects->cylinder->color)
        free_map(*map);
    
    ft_lstadd_back(&(*map)->objects, objects);
    return 0;
}
