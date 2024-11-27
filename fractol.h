#ifndef FRACTOL_H
# define FRACTOL_H

# include <mlx.h>
# include <X11/keysym.h>
# include <stdlib.h>
# include <unistd.h>

# define	MALLOC_ERROR	1
# define	WIDTH_LEN		1920.0
# define	HEIGHT_LEN		1080.0
# define	MAX_ITERATION	42

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
	double 	width;
	double 	height;
	double 	zoom;
}				t_decale;

typedef struct	s_var
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_decale	decale;
}				t_var;



int	in_mandelbrot(double x, double y);

#endif
