/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:57:44 by mhenin            #+#    #+#             */
/*   Updated: 2024/11/27 15:57:46 by mhenin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <mlx.h>

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	my_pixel_put(t_img *img, int x, int y, int color)
{
	int	offset;

	offset = (img->line_len * y) + (x * (img->bits_per_pixel / 8));
	*((unsigned int *)(offset + img->img_pixels_ptr)) = color;
}

static void	setup_mlx(t_var *vars, char *title, double c_x, double c_y)
{
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, WIDTH_LEN, HEIGHT_LEN, title);
	vars->img.img_ptr = mlx_new_image(vars->mlx, WIDTH_LEN, HEIGHT_LEN);
	vars->img.img_pixels_ptr = mlx_get_data_addr(vars->img.img_ptr,
			&vars->img.bits_per_pixel,
			&vars->img.line_len,
			&vars->img.endian);
	vars->decale.height = 0;
	vars->decale.width = 0;
	vars->decale.zoom = 500;
	vars->c_x = c_x;
	vars->c_y = c_y;
}

int	main(int ac, char **av)
{
	t_var	vars;

	if (ac == 1)
		write(1, "Utiliser 'mandelbrot' ou 'julia <reel> <imaginaire>'", 53);
	else if (!ft_strncmp(av[1], "mandelbrot", 10))
	{
		setup_mlx(&vars, "mandelbrot", 0, 0);
		mandelbrot_main(&vars);
	}
	else if (!ft_strncmp(av[1], "julia", 5))
	{
		if (ac != 4)
		{
			write(1, "utiliser 'julia <reel> <imaginaire>'", 37);
			return (0);
		}
		setup_mlx(&vars, "julia", ft_atoi(av[2]), ft_atoi(av[3]));
		julia_main(&vars);
	}
	return (0);
}
