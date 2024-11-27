#include "fractol.h"
#include <mlx.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

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
			if (in_mandelbrot((j - WIDTH_LEN/2 + data->decale.width) / (data->decale.zoom),
								(i - HEIGHT_LEN/2 + data->decale.height) / (data->decale.zoom)))
				my_pixel_put(&data->img, j, i, 0x000000);
			else
				my_pixel_put(&data->img, j, i, 0xFFFFFFFF);
			j++;
		}
		i++;
	}
}

#include <stdio.h>

int	mouse_hook(int keysym, int x, int y, t_var *data)
{
    double old_zoom;
    double new_zoom;
    double zoom_factor;

    old_zoom = data->decale.zoom;

    if (keysym == 4)
    {
        data->decale.zoom *= 1.5;
    }
    else if (keysym == 5)
    {
        data->decale.zoom /= 1.5;
    }

    if (keysym == 4 || keysym == 5)
    {
        new_zoom = data->decale.zoom;
        zoom_factor = (double)new_zoom / (double)old_zoom;
        data->decale.width = (data->decale.width + x - WIDTH_LEN / 2) * zoom_factor - (x - WIDTH_LEN / 2);
        data->decale.height = (data->decale.height + y - HEIGHT_LEN / 2) * zoom_factor - (y - HEIGHT_LEN / 2);

        render_mandelbrot(data);
        mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);
    }

    printf("\n zoom : %f", data->decale.zoom);
    printf("\n h : %f", data->decale.height);
    printf("\n w : %f", data->decale.width);
    return (0);
}

int	f(int keysym, t_var *data)
{
	if (keysym == XK_Up)
	{
		write(1, "h", 1);
		data->decale.height += -200;
	}
	else if (keysym == XK_Down)
	{
		write(1, "b", 1);
		data->decale.height += 200;
	}
	else if (keysym == XK_Left)
	{
		write(1, "g", 1);
		data->decale.width += -200;
	}
	else if (keysym == XK_Right)
	{
		write(1, "d", 1);
		data->decale.width += 200;
	}
	else if (keysym == XK_Escape)
	{
		if (data->img.img_ptr)
			mlx_destroy_image(data->mlx, data->img.img_ptr);
	    if (data->win)
			mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		exit(1);
	}

	if (keysym == XK_Up || keysym == XK_Down
		|| keysym == XK_Left || keysym == XK_Right)
	{
		render_mandelbrot(data);
		mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);
	}

	return (0);
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

	vars.decale.height = 0;
	vars.decale.width = 0;
	vars.decale.zoom = 500;

	render_mandelbrot(&vars);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img_ptr, 0, 0);

	mlx_key_hook(vars.win, f, &vars);
	mlx_mouse_hook(vars.win, mouse_hook, &vars);
	mlx_loop(vars.mlx);
}
