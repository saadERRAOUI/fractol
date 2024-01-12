/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_iterators.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serraoui <serraoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 23:16:14 by serraoui          #+#    #+#             */
/*   Updated: 2024/01/12 23:20:35 by serraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	iter_julia(t_fractol *fract)
{
	int			i;
	int			color;
	t_complex	z;

	i = 0;
	z = fract->z_init;
	while (i < fract->max_iter)
	{
		z = complex_sum(complex_mul(z, z), fract->c);
		if (((z.r * z.r) + (z.i * z.i)) > fract->esc_val)
		{
			color = color_gener(i, fract->max_iter);
			return (color);
		}
		i++;
	}
	return (WHITE);
}

int	iter_mandelbrot(t_fractol *fract)
{
	int			i;
	int			color;
	t_complex	z;

	i = 0;
	z = fract->z_init;
	while (i < fract->max_iter)
	{
		z = complex_sum(complex_mul(z, z), fract->c);
		if (((z.r * z.r) + (z.i * z.i)) > fract->esc_val)
		{
			color = color_gener(i, fract->max_iter);
			return (color);
		}
		i++;
	}
	return (WHITE);
}

int	iter_mandelbar(t_fractol *fract)
{
	int			i;
	int			color;
	t_complex	z;

	i = 0;
	z = fract->z_init;
	while (i < fract->max_iter)
	{
		z = complex_bar(complex_sum(complex_mul(z, z), fract->c));
		if (((z.r * z.r) + (z.i * z.i)) > fract->esc_val)
		{
			color = color_gener(i, fract->max_iter);
			return (color);
		}
		i++;
	}
	return (WHITE);
}
