/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serraoui <serraoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 10:27:12 by serraoui          #+#    #+#             */
/*   Updated: 2024/01/07 21:56:30 by serraoui         ###   ########.fr       */
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

static t_complex   complex_sum(t_complex cmp1, t_complex cmp2)
{
    return (t_complex){cmp1.r + cmp2.r, cmp1.i + cmp2.i};    
}

static t_complex   complex_mul(t_complex cmp1, t_complex cmp2)
{
    // (a + bi) * (c + di)
    // ac + adi + bci - bd
    // r : (a * c - (b * d)) ; i : (a * d) + (b * c)
    return (t_complex){
        (cmp1.r * cmp2.r) - (cmp1.i * cmp2.i), 
        (cmp1.r * cmp2.i) + (cmp1.i * cmp2.r)    
    };
}

static double	scale_nbr(double nbr, double n_max, double n_min, double o_min, double o_max)
{
	return (((nbr - o_min) * (n_max * n_min) / (o_max - o_min)) - n_min);
}

//function ; z^2 + c
void    iterate(t_fractol *fract, int x, int y)
{
    int         i;
	int			color;
    t_complex   z;

    i = 0;
	z = fract->z_init;
	fract->c.r = scale_nbr(x, -2, 2, 0, WIDTH - 1);
	fract->c.i = scale_nbr(y, 2, -2, 0, HEIGHT - 1);
	//printf("**** point_c [%lf][%lf]\n", fract->c.r, fract->c.i); //!:
    while (i < fract->max_iter)
    {
		//printf("point [%d][%d]\n", x, y); //!:
        z = complex_sum(complex_mul(z, z), (*fract).c);
		if ((z.r * z.r) + (z.i * z.i) > fract->esc_val)
		{
			//put the pixel to the img
			color = scale_nbr(i, WHITE, BLACK, 0, fract->max_iter);
			my_pixel_put(fract->img, x, y, color);
			return ;
		}
        i++;
    }
	my_pixel_put(fract->img, x, y, BLACK);
}

void render_fract(t_fractol *fract)
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

	//!verif
	printf("bpp ---> [%i]\n", fract->img->bpp);
	//put the image to the window 
	//mlx_put_image_to_window(fract->mlx_ptr,
							// fract->win_ptr,
							// fract->img->img,
							// 0, 0);

	// mlx_loop(fract->mlx_ptr);
}