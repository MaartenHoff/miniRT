#include "../../includes/miniRT.h"

void	handle_param_error(int error_code)
{
	if (error_code == ERR_PARAM)
		printf("Incorrect parameter format or count\n");
	else if (error_code == ERR_A)
		printf("Invalid ambient parameters\n");
	else if (error_code == ERR_C)
		printf("Invalid camera parameters\n");
	else if (error_code == ERR_L)
		printf("Invalid light parameters\n");
	else if (error_code == ERR_SP)
		printf("Invalid sphere parameters\n");
	else if (error_code == ERR_PL)
		printf("Invalid plane parameters\n");
	else if (error_code == ERR_CY)
		printf("Invalid cylinder parameters\n");
	else if (error_code == ERR_OBJ)
		printf("No object\n");
}

int	handle_error(int error_code, t_map *map)
{
	free_map(map);
	if (error_code > 131)
		handle_param_error(error_code);
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
