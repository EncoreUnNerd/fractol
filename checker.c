/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:29:48 by mhenin            #+#    #+#             */
/*   Updated: 2024/11/27 16:29:49 by mhenin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	in_mandelbrot(double x, double y)
{
	double	t_x;
	double	t_y;
	double	temp_x;
	int		i;

	t_x = 0;
	t_y = 0;
	i = 0;
	while (MAX_ITERATION > i)
	{
		temp_x = (t_x * t_x) - (t_y * t_y);
		t_y = 2 * t_x * t_y;
		t_x = temp_x;
		t_x += x;
		t_y += y;
		i++;
		if ((t_x * t_x + t_y * t_y) > 4)
			return (i);
	}
	return (0);
}

int	in_julia(double x, double y, double c_x, double c_y)
{
	double	t_x;
	double	t_y;
	double	temp_x;
	int		i;

	t_x = 0;
	t_y = 0;
	i = 0;
	while (MAX_ITERATION > i)
	{
		temp_x = (x * x) - (y * y);
		y = 2 * x * y;
		x = temp_x;
		x += c_x;
		y += c_y;
		i++;
		if ((x * x + y * y) > 4)
			return (i);
	}
	return (0);
}
