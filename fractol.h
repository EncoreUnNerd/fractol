/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenin <mhenin@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:29:36 by mhenin            #+#    #+#             */
/*   Updated: 2024/11/29 15:28:06 by mhenin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <mlx.h>
# include <X11/keysym.h>
# include <stdlib.h>
# include <unistd.h>

# define MALLOC_ERROR 1
# define WIDTH_LEN 1920.0
# define HEIGHT_LEN 1080.0
# define MAX_ITERATION 500

typedef struct s_img
{
	void	*img_ptr;
	char	*img_pixels_ptr;
	int		bits_per_pixel;
	int		endian;
	int		line_len;
}				t_img;

typedef struct s_decale
{
	double	width;
	double	height;
	double	zoom;
}				t_decale;

typedef struct s_var
{
	void		*mlx;
	void		*win;
	double		c_x;
	double		c_y;
	t_img		img;
	t_decale	decale;
}				t_var;

int		in_julia(double x, double y, double c_x, double c_y);
void	my_pixel_put(t_img *img, int x, int y, int color);
int		in_mandelbrot(double x, double y);
int		mandelbrot_main(t_var *vars);
int		julia_main(t_var *vars);
double	ft_atoi(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		create_trgb(int t, int r, int g, int b);
int		destroy(t_var *data);
int		in_burningship(double x, double y);
int		burningship_main(t_var *vars);

#endif
