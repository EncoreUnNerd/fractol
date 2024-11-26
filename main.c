#include "fractol.h"

/*
 * IMAGE DATA
 *
 ***WHY LINE_LEN?
 * Can i just make SIDE_LEN * 4 to get the bytes into a line? Nope...due to...
 *
 * 								👀 Alignment optimization 👀
 * ~https://www.youtube.com/watch?v=iz958I8Xb2g&list=PLc4DnsRQbs6ae27mFDLz5aJo6_p9uf3m-&index=51
 *
 * For instance, let's say an image is 5 pixels wide, and each pixel takes 4 bytes
 * (assuming 32 bits or 4 bytes per pixel for colors). So, you'd expect the image width
 * in memory to be 20 bytes. But due to the way memory alignment works, the line_length
 * could be 24 bytes or any other suitable value that the system deems efficient.
 *
 * TL;DR
 * 		"When working with image data in memory, especially in graphics programming,
 * 				it's crucial to be aware of how the data is aligned and stored"
 *
 ***ENDIAN?
 *  Consider the number 0x12345678:

	In Big-Endian: It's stored as 12 34 56 78 in memory.

	In Little-Endian: It's stored as 78 56 34 12 in memory.

	How does this apply to graphics and MiniLibX?
	When we're dealing with colors in graphics, we often represent them using
	multiple bytes. For example, ARGB format uses 4 bytes to represent a color:
	one byte each for the Alpha, Red, Green, and Blue components.
	If your system is Big-Endian, the ARGB value 0x12345678 would mean the alpha value
	is 0x12, the red value is 0x34, the green value is 0x56, and the blue value is 0x78.
		DO WE CARE? NO. 👀
	Direct Memory Manipulation: While the endian value becomes critical when doing
	direct memory manipulation byte-by-byte.
	The manipulation is done using (unsigned int *) for the entire color value, namely the pixel.
	This approach abstracts away the need for us to consider individual byte order for each color channel, thank god.
*/

void	my_pixel_put(t_img *img, int x, int y, int color)
{
	int	offset;

	offset = (img->line_len * y) + (x * (img->bits_per_pixel / 8));
	*((unsigned int *)(offset + img->img_pixels_ptr)) = color;
}

void	render_mandelbrot(t_var *data)
{
	int		i;
	int		j;

	i = 0;
	while (i < HEIGHT_LEN)
	{
		j = 0;
		while (j < WIDTH_LEN)
		{
			if (in_mandelbrot((double)(j - WIDTH_LEN / 1.5) / 500, (double)(i - HEIGHT_LEN / 2) / 500))
				my_pixel_put(&data->img, j, i, 0x000000);
			else
				my_pixel_put(&data->img, j, i, 0xFFFFFFFF);
			j++;
		}
		i++;
	}
}

int	f(int keysym, t_var *data)
{
	if (keysym == XK_Escape)
		exit(1);

	return 0;
}


int	main()
{
	t_var	vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIDTH_LEN, HEIGHT_LEN, "mandelbrot");

	vars.img.img_ptr = mlx_new_image(vars.mlx, WIDTH_LEN, HEIGHT_LEN);
	vars.img.img_pixels_ptr = mlx_get_data_addr(vars.img.img_ptr,
												&vars.img.bits_per_pixel,
												&vars.img.line_len,
												&vars.img.endian);

	render_mandelbrot(&vars);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img_ptr, 0, 0);

	mlx_key_hook(vars.win, f, &vars);
	mlx_loop(vars.mlx);
}
