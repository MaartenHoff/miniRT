/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiler <adiler@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:42:02 by maahoff           #+#    #+#             */
/*   Updated: 2025/02/16 21:42:51 by adiler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"
#include "../includes/structs.h"

int	init_window(t_window *window)
{
	window->mlx = mlx_init();
	if (!window->mlx)
		return (1);
	window->win = mlx_new_window(window->mlx, WIDTH, HEIGHT, "miniRT");
	if (!window->win)
		return (1);
	window->img = mlx_new_image(window->mlx, WIDTH, HEIGHT);
	window->addr = mlx_get_data_addr(window->img, 
			&window->bits_per_pixel, &window->line_length, &window->endian);
	return (0);
}

t_vec3	normalize(t_vec3 vec)
{
	double	length;
	t_vec3	normalized;

	length = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	normalized.x = vec.x / length;
	normalized.y = vec.y / length;
	normalized.z = vec.z / length;
	return (normalized);
}

t_vec3 vec_sub(t_vec3 a, t_vec3 b)
{
	t_vec3	sub;

	sub.x = a.x - b.x;
	sub.y = a.y - b.y;
	sub.z = a.z - b.z;
	return (sub);
}

double vec_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

int	intersect_sphere(t_vec3 camera, t_vec3 ray_dir, t_sphere sphere)
{
	t_vec3	oc;
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	t1;
	double	t2;
	
	oc = vec_sub(camera, sphere.center);
	a = vec_dot(ray_dir, ray_dir);
	b = 2 * vec_dot(oc, ray_dir);
	c = vec_dot(oc, oc) - sphere.radius * sphere.radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (0);
	t1 = (-b + sqrt(discriminant)) / (2 * a);
	t2 = (-b - sqrt(discriminant)) / (2 * a);
	if (t1 > 0 || t2 > 0)
		return (1);
	return (0);
	
}

int	ray_hit(int x, int y, t_vec3 camera, t_sphere sphere)
{
	int	image_x;
	int	image_y;
	int	focal_length;
	t_vec3	ray;
	t_vec3	ray_dir;

	image_x = x - WIDTH / 2;
	image_y = HEIGHT / 2 - y;
	focal_length = 1000;

	ray.x = image_x;
	ray.y = image_y;
	ray.z = focal_length;
	ray_dir = normalize(ray);
	return (intersect_sphere(camera, ray_dir, sphere));
}

void	fill_window(t_window *window)
{
	int	x;
	int	y;
	int	color;
	int	pixel;
	int hit;
	t_sphere	sphere;
	t_vec3		camera;

	sphere.center.x = 0;
	sphere.center.y = 0;
	sphere.center.z = 10;
	sphere.radius = 1;
	sphere.color = 0x00FF0000;

	camera.x = 0;
	camera.y = 0;
	camera.z = 0;

	hit = 0;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (ray_hit(x, y, camera, sphere))
				color = sphere.color;
			else
				color = 0xFFFFFF;
			pixel = y * (window->line_length / 4) + x;
			*((int *)window->addr + pixel) = color;	
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(window->mlx, window->win, window->img, 0, 0);
}

int	main(void)
{
	t_window	*window;

	window = malloc(sizeof(t_window));
	if (init_window(window))
		return (1);
	fill_window(window);
	//mlx_key_hook(window->win, (void *)exit, NULL);
	mlx_loop(window->mlx);
	free(window->mlx);
	free(window);
	return (0);
}
