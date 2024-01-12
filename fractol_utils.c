/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serraoui <serraoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 10:27:12 by serraoui          #+#    #+#             */
/*   Updated: 2024/01/12 23:27:00 by serraoui         ###   ########.fr       */
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

static int	valid_str(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (!((s[i] >= '0' && s[i] <= '9')
				|| s[i] == '.'
				|| s[i] == '-'
				|| s[i] == '+'))
			return (0);
		if (s[i] == '.')
			count++;
		i++;
	}
	return ((count == 1 || count == 0));
}

int	ft_atof(const char *s, double *arg)
{
	int		i;
	int		sign;
	double	dec;
	int		flag;

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

void	iterate(t_fractol *fract, int x, int y)
{
	int	color;

	if (fract->f_nbr == 0 || fract->f_nbr == 2)
	{
		fract->z_init = (t_complex){0, 0};
		fract->c = (t_complex){
			scale_nbr(x, fract->x_max, fract->x_min, WIDTH) + fract->x_shift,
			scale_nbr(y, fract->y_max, fract->y_min, HEIGHT) + fract->y_shift
		};
	}
	else if (fract->f_nbr == 1)
	{
		fract->z_init = (t_complex){
			scale_nbr(x, fract->x_max, fract->x_min, WIDTH) + fract->x_shift,
			scale_nbr(y, fract->y_max, fract->y_min, HEIGHT) + fract->y_shift
		};
	}
	color = fract->f_fract(fract);
	my_pixel_put(fract->img, x, y, color);
}

int	render_fract(t_fractol *fract)
{
	int	x;
	int	y;

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
