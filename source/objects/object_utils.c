#include "../../includes/miniRT.h"

double	solve_quadratic(double a, double b, double c)
{
	double	discriminant;
	double	sqrt_discriminant;
	double	t1;
	double	t2;

	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (-1);
	sqrt_discriminant = sqrt(discriminant);
	t1 = (-b + sqrt_discriminant) / (2 * a);
	t2 = (-b - sqrt_discriminant) / (2 * a);
	if (t1 >= 0 && t2 >= 0)
	{
		if (t1 < t2)
			return (t1);
		return (t2);
	}
	if (t1 >= 0)
		return (t1);
	if (t2 >= 0)
		return (t2);
	return (-1);
}