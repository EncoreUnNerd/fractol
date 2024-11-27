#include "fractol.h"

int	in_mandelbrot(double x, double y)
{
	double	t_x;
	double	t_y;
	double	temp_x;
	int	i;

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
		if ((t_x * t_x + t_y * t_y) > 4)
            return 0;
		i++;
	}
	return (1);
}
