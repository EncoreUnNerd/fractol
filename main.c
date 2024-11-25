#include "fractol.h"
#include <stdio.h>
#include <math.h>

int	get_absolut(t_complex complex)
{
	return(sqrt((complex.imaginary * complex.imaginary) + (complex.real * complex.real)));
}

int	in_mandelbrot(t_complex c)
{
	t_complex	z;
	double		temp_real;
	int			i;

	z.real = 0;
	z.imaginary = 0;
	while (50 > i)
	{
		temp_real = (z.real * z.real) - (z.imaginary * z.imaginary);
		z.imaginary = 2 * z.real * z.imaginary;
		z.real = temp_real;
		z.real += c.real;
		z.imaginary += c.imaginary;
		if (get_absolut(z) > 2)
			return (0);
		i++;
	}
	return (1);
}

int main()
{
	t_complex	c;

	c.real = 3;
	c.imaginary = 0;
	if (in_mandelbrot(c))
		printf("ok");
	else
		printf("pas ok");
}
