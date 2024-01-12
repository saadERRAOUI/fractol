/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serraoui <serraoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:56:12 by serraoui          #+#    #+#             */
/*   Updated: 2024/01/12 23:27:40 by serraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_complex	complex_sum(t_complex cmp1, t_complex cmp2)
{
	return ((t_complex){cmp1.r + cmp2.r, cmp1.i + cmp2.i});
}

t_complex	complex_bar(t_complex cmp)
{
	return ((t_complex){cmp.r, -1 * cmp.i});
}

t_complex	complex_mul(t_complex cmp1, t_complex cmp2)
{
	return ((t_complex){
		(cmp1.r * cmp2.r) - (cmp1.i * cmp2.i),
		(cmp1.r * cmp2.i) + (cmp1.i * cmp2.r)
	});
}

int	init_julia(t_fractol *fract, int ac, char **av)
{
	(*fract).c.r = 0;
	(*fract).c.i = 0;
	if (ac == 4
		&& ft_atof(av[2], &(*fract).c.r)
		&& ft_atof(av[3], &(*fract).c.i))
	{
		fract->f_nbr = 1;
		fract->f_fract = iter_julia;
		return (1);
	}
	return (0);
}

int	init_mandel(t_fractol *fract, int ac, int f_nbr)
{
	if (ac == 2)
	{
		fract->f_nbr = f_nbr;
		fract->z_init = (t_complex){0, 0};
		if (!f_nbr)
			fract->f_fract = iter_mandelbrot;
		else
			fract->f_fract = iter_mandelbar;
		return (1);
	}
	return (0);
}
