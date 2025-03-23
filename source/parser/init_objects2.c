#include "../../includes/miniRT.h"

int	add_cube_squares(t_cube *cube)
{
	cube->square1 = malloc(sizeof(t_planes));
	cube->square2 = malloc(sizeof(t_planes));
	cube->square3 = malloc(sizeof(t_planes));
	cube->square4 = malloc(sizeof(t_planes));
	cube->square5 = malloc(sizeof(t_planes));
	cube->square6 = malloc(sizeof(t_planes));
	cube->square1->point = vec_add(cube->center, (t_coords){cube->size / 2.0, 0,
			0});
	cube->square1->vector = (t_coords){1, 0, 0};
	cube->square2->point = vec_add(cube->center, (t_coords){-cube->size / 2.0,
			0, 0});
	cube->square2->vector = (t_coords){-1, 0, 0};
	cube->square3->point = vec_add(cube->center, (t_coords){0, cube->size / 2.0,
			0});
	cube->square3->vector = (t_coords){0, 1, 0};
	cube->square4->point = vec_add(cube->center, (t_coords){0, -cube->size
			/ 2.0, 0});
	cube->square4->vector = (t_coords){0, -1, 0};
	cube->square5->point = vec_add(cube->center, (t_coords){0, 0, cube->size
			/ 2.0});
	cube->square5->vector = (t_coords){0, 0, 1};
	cube->square6->point = vec_add(cube->center, (t_coords){0, 0, -cube->size
			/ 2.0});
	cube->square6->vector = (t_coords){0, 0, -1};
	return (0);
}

int	add_cube(char **params, t_objects **objects)
{
	(*objects)->next = NULL;
	(*objects)->type = CUBE;
	(*objects)->plane = NULL;
	(*objects)->spheres = NULL;
	(*objects)->cylinder = NULL;
	(*objects)->cube = malloc(sizeof(t_cube));
	if (!(*objects)->cube)
		return (ERR_NOMEM);
	(*objects)->cube->center = split_coords(params[1]);
	(*objects)->cube->vector = vec_norm(split_coords(params[2]));
	(*objects)->cube->size = ft_atof(params[3]);
	if (add_cube_squares((*objects)->cube) == ERR_NOMEM)
		return (ERR_NOMEM);
	(*objects)->cube->color = split_color(params[4]);
	return (0);
}
