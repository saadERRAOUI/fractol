/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serraoui <serraoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 23:04:51 by serraoui          #+#    #+#             */
/*   Updated: 2024/01/12 23:15:29 by serraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	color_gener(int iter, int m_iter)
{
	int	m_color_val;
	int	r;
	int	g;
	int	b;
	int	color;

	m_color_val = 255;
	r = (iter * m_color_val) / m_iter;
	g = (iter * m_color_val * 2) / m_iter;
	b = (iter * m_color_val * 3) / m_iter;
	color = (r << 16) | (g << 8) | b;
	return (color);
}

double	scale_nbr(double nbr, double n_max, double n_min, double o_max)
{
	return ((((nbr - 0) * (n_max - n_min)) / (o_max - 0)) + n_min);
}

void	calc_coeffs(t_fractol *fract, int x, int y, int sign)
{
	double	x_temp;
	double	y_temp;

	if (sign == 1)
		fract->ratio *= 1.1;
	else
		fract->ratio /= 1.1;
	x_temp = (fract->x_max - fract->x_min) / WIDTH;
	y_temp = (fract->y_max - fract->y_min) / HEIGHT;
	fract->x_min += x * x_temp * fract->z_coeff * sign;
	fract->x_max -= x_temp * (WIDTH - x) * fract->z_coeff * sign;
	fract->y_min += y * y_temp * fract->z_coeff * sign;
	fract->y_max -= y_temp * (HEIGHT - y) * fract->z_coeff * sign;
	mlx_clear_window(fract->mlx_ptr, fract->win_ptr);
	render_fract(fract);
}
