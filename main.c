/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenin <mhenin@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:57:44 by mhenin            #+#    #+#             */
/*   Updated: 2024/11/29 17:01:32 by mhenin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	check_validity(char	*str)
{
	int	i;

	i = 0;
	while ((str[i] >= '0' && str[i] <= '9') || \
		str[i] == '-' || str[i] == '.')
		i++;
	if (str[i] != '\0')
		return (0);
	return (1);
}

static void	ft_putstr(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
		i++;
	write(1, s, i * sizeof(char));
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
	vars->decale.zoom = 200;
	vars->c_x = c_x;
	vars->c_y = c_y;
}

int	main(int ac, char **av)
{
	t_var	vars;

	if (ac == 2 && !ft_strncmp(av[1], "mandelbrot", 10))
	{
		setup_mlx(&vars, "mandelbrot", 0, 0);
		mandelbrot_main(&vars);
	}
	else if ((ac == 4 && !ft_strncmp(av[1], "julia", 5)) && \
		(check_validity(av[2]) && check_validity(av[3])))
	{
		setup_mlx(&vars, "julia", ft_atoi(av[2]), ft_atoi(av[3]));
		julia_main(&vars);
	}
	else if (ac == 2 && !ft_strncmp(av[1], "burningship", 11))
	{
		setup_mlx(&vars, "burning ship", 0, 0);
		burningship_main(&vars);
	}
	else
		ft_putstr("->'mandelbrot' 'julia <reel> <imaginaire>' 'burningship'");
	return (0);
}
