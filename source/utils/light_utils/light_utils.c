#include "../../../includes/miniRT.h"

int	color_to_int(t_color color)
{
	return ((color.r << 16) | (color.g << 8) | color.b);
}

t_color	light_hit_color(t_color light_color, double brightness, t_color color)
{
	color.r *= (light_color.r * brightness) / 255;
	color.g *= (light_color.g * brightness) / 255;
	color.b *= (light_color.b * brightness) / 255;
	return (color);
}

t_light_data	light_plus_light(t_color light1, double brightness1, 
					t_color light2, double brightness2)
{
	t_light_data	result;

	result.color.r = light1.r * brightness1 + light2.r * brightness2;
	result.color.g = light1.g * brightness1 + light2.g * brightness2;
	result.color.b = light1.b * brightness1 + light2.b * brightness2;
	result.color.r = fmin(result.color.r, 255);
	result.color.g = fmin(result.color.g, 255);
	result.color.b = fmin(result.color.b, 255);
	result.brightness = brightness1 + brightness2;
	return (result);
}
