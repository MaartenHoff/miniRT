/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maahoff <maahoff@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 20:06:03 by adiler            #+#    #+#             */
/*   Updated: 2025/03/18 12:23:43 by maahoff          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>

static void	process_whitespace_sign(char **ptr, int *sign)
{
	while (**ptr == ' ' || (**ptr >= '\t' && **ptr <= '\r'))
		(*ptr)++;
	*sign = 1;
	if (**ptr == '-')
		*sign = -(++(*ptr), 1);
	else if (**ptr == '+')
		(*ptr)++;
}

static double	process_integer_part(char **ptr)
{
	double	result;

	result = 0.0;
	while (**ptr >= '0' && **ptr <= '9')
		result = result * 10.0 + (*(*ptr)++ - '0');
	return (result);
}

static double	process_fraction_part(char **ptr)
{
	double	fraction;
	double	power;

	if (**ptr != '.')
		return (0.0);
	fraction = 0.0;
	power = 1.0;
	while (*(++*ptr) >= '0' && **ptr <= '9')
	{
		fraction = fraction * 10.0 + (**ptr - '0');
		power *= 10.0;
	}
	return (fraction / power);
}

static double	process_exponent(char **ptr)
{
	int	exp_sign;
	int	exp;

	exp = 0;
	exp_sign = 1;
	if (**ptr != 'e' && **ptr != 'E')
		return (1.0);
	if (*(++*ptr) == '-')
		exp_sign = -(++(*ptr), 1);
	else if (**ptr == '+')
		(*ptr)++;
	while (**ptr >= '0' && **ptr <= '9')
		exp = exp * 10 + (*(*ptr)++ - '0');
	return (pow(10, exp_sign * exp));
}

double	ft_atof(char *str)
{
	int		sign;
	double	result;

	process_whitespace_sign(&str, &sign);
	result = process_integer_part(&str);
	result += process_fraction_part(&str);
	result *= process_exponent(&str);
	return (sign * result);
}
