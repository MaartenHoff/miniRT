#include "../../../includes/miniRT.h"

int	color_to_int(t_color color)
{
	// if (color.r > 255)
	// 	color.r = 255;
	// if (color.g > 255)
	// 	color.g = 255;
	// if (color.b > 255)
	// 	color.b = 255;
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

	result.color.r = (light1.r * brightness1 + light2.r * brightness2) / 2;
	result.color.g = (light1.g * brightness1 + light2.g * brightness2) / 2;
	result.color.b = (light1.b * brightness1 + light2.b * brightness2) / 2;
	result.brightness = (brightness1 + brightness2) / 2;
	return (result);
}
