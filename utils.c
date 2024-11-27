/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:26:28 by mhenin            #+#    #+#             */
/*   Updated: 2024/11/27 16:26:29 by mhenin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static double	parse_integer_part(const char *str, int *i)
{
	double	result;

	result = 0.0;
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		result = result * 10.0 + (str[*i] - '0');
		(*i)++;
	}
	return (result);
}

static double	parse_fractional_part(const char *str, int *i)
{
	double	fraction;
	double	divisor;

	fraction = 0.0;
	divisor = 1.0;
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		fraction = fraction * 10.0 + (str[*i] - '0');
		divisor *= 10.0;
		(*i)++;
	}
	return (fraction / divisor);
}

double	ft_atoi(const char *str)
{
	int		i;
	int		signe;
	double	result;

	i = 0;
	signe = 1.0;
	result = 0.0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe = -1.0;
		i++;
	}
	result = parse_integer_part(str, &i);
	if (str[i] == '.')
	{
		i++;
		result += parse_fractional_part(str, &i);
	}
	return (signe * result);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n && (s1[i] != '\0' || s2[i] != '\0'))
	{
		if (s1[i] != s2[i])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		++i;
	}
	return (0);
}

int	destroy(t_var *data)
{
	if (data->img.img_ptr)
		mlx_destroy_image(data->mlx, data->img.img_ptr);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(1);
	return (1);
}
