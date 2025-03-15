#include "../../includes/miniRT.h"

int	handle_error(int error_code, t_map *map)
{
	free_map(map);
	if (error_code == ERR_NOMEM)
		printf("Memory allocation error\n");
	else if (error_code == ERR_INVAL)
		printf("Invalid argument\n");
	else if (error_code == ERR_ARGC)
		printf("Wrong number of arguments\n");
	else if (error_code == ERR_FDFILE)
		printf("Unable to open File\n");
	else if (error_code == ERR_NOTRT)
		printf("File is not a .rt file\n");
	return (error_code);
}
