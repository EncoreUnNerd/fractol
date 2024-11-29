/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenin <mhenin@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:29:10 by mhenin            #+#    #+#             */
/*   Updated: 2024/11/29 16:40:38 by mhenin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	render_julia(t_var *data)
{
	int		i;
	int		j;
	int		iterations;

	i = 0;
	while (i < HEIGHT_LEN)
	{
		j = 0;
		while (j < WIDTH_LEN)
		{
			iterations = in_julia((j - WIDTH_LEN / 2 + data->decale.width) \
				/ data->decale.zoom,
					(i - HEIGHT_LEN / 2 + data->decale.height) \
				/ data->decale.zoom, data->c_x, data->c_y);
			if (iterations == 0)
				my_pixel_put(&data->img, j, i, 0x000000);
			else
				my_pixel_put(&data->img, j, i, \
					get_color(iterations));
			j++;
		}
		i++;
	}
}

static int	mouse_hook(int keysym, int x, int y, t_var *data)
{
	double	old_zoom;
	double	new_zoom;
	double	zoom_factor;

	old_zoom = data->decale.zoom;
	if (keysym == 4)
		data->decale.zoom *= 1.5;
	else if (keysym == 5)
		data->decale.zoom /= 1.5;
	if (keysym == 4 || keysym == 5)
	{
		new_zoom = data->decale.zoom;
		zoom_factor = (double)new_zoom / (double)old_zoom;
		data->decale.width = (data->decale.width + x - WIDTH_LEN / 2) \
						* zoom_factor - (x - WIDTH_LEN / 2);
		data->decale.height = (data->decale.height + y - HEIGHT_LEN / 2) \
						* zoom_factor - (y - HEIGHT_LEN / 2);
		render_julia(data);
		mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);
	}
	return (0);
}

static int	f(int keysym, t_var *data)
{
	if (keysym == XK_Up)
		data->decale.height += -200;
	else if (keysym == XK_Down)
		data->decale.height += 200;
	else if (keysym == XK_Left)
		data->decale.width += -200;
	else if (keysym == XK_Right)
		data->decale.width += 200;
	else if (keysym == XK_Escape)
		destroy(data);
	if (keysym == XK_Up || keysym == XK_Down
		|| keysym == XK_Left || keysym == XK_Right)
	{
		render_julia(data);
		mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);
	}
	return (0);
}

int	julia_main(t_var *vars)
{
	render_julia(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img_ptr, 0, 0);
	mlx_key_hook(vars->win, f, vars);
	mlx_hook(vars->win, 17, 0, destroy, vars);
	mlx_mouse_hook(vars->win, mouse_hook, vars);
	mlx_loop(vars->mlx);
	return (0);
}
