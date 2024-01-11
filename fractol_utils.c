/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serraoui <serraoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 10:27:12 by serraoui          #+#    #+#             */
/*   Updated: 2024/01/11 22:07:47 by serraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

static int valid_str(char *s)
{
	int i;
	int count;
	
	i = 0;
	count = 0;
	while (s[i])
	{
		if (!((s[i] >= '0' && s[i] <= '9') || s[i] == '.' || s[i] == '-' || s[i] == '+'))
			return (0);
		if (s[i] == '.')
			count++;
		i++;
	}
	return ((count == 1 || count == 0));
}

int ft_atof(const char *s, double *arg)
{
	int i;
	int sign;
	double dec;
	int flag;

	if (!valid_str((char *)s))
		return (0);
	sign = 1;
	flag = 0;
	dec = 0.1;
	i = 0;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	while (s[i])
	{
		if (flag == 0 && (s[i] >= '0' && s[i] <= '9'))
			(*arg) = (*arg) * 10 + s[i] - '0';
		else if (flag == 1 && (s[i] >= '0' && s[i] <= '9'))
		{
			(*arg) = (*arg) + dec * (s[i] - '0');
			dec *= 0.1; 
		}
		else if (s[i] == '.')
			flag = 1;
		i++;
	}
	return ((*arg) *= sign, 1);
}

int color_gener(int iter, int m_iter) {
	int m_color_val = 255;
	int r = (iter * m_color_val) / m_iter;
	int g = (iter * m_color_val * 2) / m_iter;
	int b = (iter * m_color_val * 3) / m_iter;
	int color = (r << 16) | (g << 8) | b;

	return color;
}


double scale_nbr(double nbr, double n_max, double n_min, double o_min, double o_max)
{
	return (((nbr - o_min) * (n_max - n_min)) / (o_max - o_min)) + n_min;
}

void    iterate(t_fractol *fract, int x, int y)
{
	int  color;
	
	if (fract->f_nbr == 0 || fract->f_nbr == 2)//corresponds to Mandelbrot or Mandelbar
	{
		fract->z_init = (t_complex){0, 0};
		fract->c = (t_complex){
			scale_nbr(x, fract->x_max, fract->x_min, 0, WIDTH) + fract->x_shift, 
			scale_nbr(y, fract->y_max, fract->y_min, 0, HEIGHT) + fract->y_shift
		};
	}
	else if (fract->f_nbr == 1) // corresponds to Julia
	{
		fract->z_init = (t_complex){
			scale_nbr(x, fract->x_max, fract->x_min, 0, WIDTH) + fract->x_shift, 
			scale_nbr(y, fract->y_max, fract->y_min, 0, HEIGHT) + fract->y_shift
		};
	}
	color = fract->f_fract(fract);
	my_pixel_put(fract->img, x, y, color);
}

int    render_fract(t_fractol *fract)
{
	int x;
	int y;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			iterate(fract, x, y);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(fract->mlx_ptr,
							fract->win_ptr,
							fract->img->img,
							0, 0);
	return (0);
}

int     iter_julia(t_fractol *fract)
{
	int         i;
	int			color;
	t_complex   z;

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
	return ((int) WHITE);
}

int     iter_Mandelbrot(t_fractol *fract)
{
	int         i;
	int			color;
	t_complex   z;

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
	return ((int)WHITE);
}

int     iter_Mandelbar(t_fractol *fract)
{
	int         i;
	int			color;
	t_complex   z;

	i = 0;
	z = fract->z_init;
	// fract->c.r = scale_nbr(x, -2, +2, 0, WIDTH - 1);
	// fract->c.i = scale_nbr(y, +2, -2, 0, HEIGHT - 1);
	//printf("!!! **** point_c [%lf][%lf][%lf]\n", fract->c.r, fract->c.i, fract->esc_val); //!:
	while (i < fract->max_iter)
	{
		//printf("point [%d][%d]\n", x, y); //!:
		z = complex_bar(complex_sum(complex_mul(z, z), fract->c));
	   // printf(" *** z_complex - reel[%lf][%lf]\n", z.r, z.i);
		if (((z.r * z.r) + (z.i * z.i)) > fract->esc_val)
		{
			//put the pixel to the img
			//printf("::::::::::::::::::::: Enters here !!!\n");
			color = color_gener(i, fract->max_iter);
			return (color);
		}
		i++;
	}
	//my_pixel_put(fract->img, x, y, WHITE);
	return ((int)WHITE);
}

double abs_val(double arg)
{
	if (arg >= 0)
		return (arg);
	return (arg * -1);
}

void	calc_coeffs(t_fractol *fract, double x, double y, int sign)
{

	double coeff = 1.0125;
	if (sign == -1)
		coeff = 0.0125;
	fract->x_min =  abs_val(x + 2) * coeff * fract->x_min;
	fract->x_max =  abs_val(x - 2) * coeff * fract->x_max;
	fract->y_min =  abs_val(y - 2) * coeff * fract->y_min;
	fract->y_max =  abs_val(y + 2) * coeff * fract->y_max;

	// printf("sign %i\n", sign);
	// printf("new x_min %lf\n", fract->x_min);
	// printf("new x_max %lf\n", fract->x_max);
	// printf("new y_min %lf\n", fract->y_min);
	// printf("new y_max %lf\n", fract->y_max);

	mlx_clear_window(fract->mlx_ptr, fract->win_ptr);
    render_fract(fract);
}