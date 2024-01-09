/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serraoui <serraoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 10:27:12 by serraoui          #+#    #+#             */
/*   Updated: 2024/01/08 23:52:39 by serraoui         ###   ########.fr       */
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
    // Adjust these parameters as needed
    int m_color_val = 255;

    // Calculate color intensity based on the iter count
    int r = (iter * m_color_val) / m_iter;
    int g = (iter * m_color_val * 2) / m_iter;
    int b = (iter * m_color_val * 3) / m_iter;

    // Combine the color intensities into a single integer
    int color = (r << 16) | (g << 8) | b;

    return color;
}

static t_complex   complex_sum(t_complex cmp1, t_complex cmp2)
{
    return (t_complex){cmp1.r + cmp2.r, cmp1.i + cmp2.i};    
}

static t_complex    complex_bar(t_complex cmp)
{
    return (t_complex){cmp.r, -1 * cmp.i};
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


static double scale_nbr(double nbr, double n_max, double n_min, double o_min, double o_max)
{
    return (((nbr - o_min) * (n_max - n_min)) / (o_max - o_min)) + n_min;
}

//function ; z^2 + c
//Mandelbrot 
//Todo : change the iterate() function to be generic;
//Todo : change the iteration logic to the a function as arg in t_fractol;
void    iterate(t_fractol *fract, int x, int y)
{
    int  color;
    
    if (fract->f_nbr == 0 || fract->f_nbr == 2)//corresponds to Mandelbrot or Mandelbar
    {
        fract->z_init = (t_complex){0, 0};
        fract->c = (t_complex){
            scale_nbr(x, -2, 2, 0, WIDTH), 
            scale_nbr(y, +2, -2, 0, HEIGHT)};
    }
    else if (fract->f_nbr == 1) // corresponds to Julia
    {
        fract->z_init = (t_complex){
            scale_nbr(x, -2, 2, 0, WIDTH), 
            scale_nbr(y, +2, -2, 0, HEIGHT)};
    }
    color = fract->f_fract(fract);
	my_pixel_put(fract->img, x, y, color);
}

void    render_fract(t_fractol *fract)
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
	//printf("bpp ---> [%i]\n", fract->img->bpp);
	// put the image to the window 
	mlx_put_image_to_window(fract->mlx_ptr,
							fract->win_ptr,
							fract->img->img,
							0, 0);
    //Todo :: Listen to key events and print key
    mlx_hook(fract->win_ptr, 2, 1L<<0, f_key_listner, fract);
    // (fract->win_ptr, f_key_listner, fract);
    if (fract->win_ptr != NULL && fract->mlx_ptr != NULL)
	    mlx_loop(fract->mlx_ptr);
}

int     iter_julia(t_fractol *fract)
{
    int         i;
	int			color;
    t_complex   z;

    i = 0;
	z = fract->z_init;
    // printf("#1 Enters Here JULIA initials ### %lf - %lf\n", z.r, z.i);
    // printf("#2 Enters Here JULIA constant ### %lf - %lf\n", fract->c.r, fract->c.i);

    while (i < fract->max_iter)
    {
        z = complex_sum(complex_mul(z, z), fract->c);
		if (((z.r * z.r) + (z.i * z.i)) > fract->esc_val)
		{
			color = color_gener(i, fract->max_iter);
            // printf("#3 Enters Here JULIA color ### %i\n", color);
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
	// fract->c.r = scale_nbr(x, -2, +2, 0, WIDTH - 1);
	// fract->c.i = scale_nbr(y, +2, -2, 0, HEIGHT - 1);
	//printf("!!! **** point_c [%lf][%lf][%lf]\n", fract->c.r, fract->c.i, fract->esc_val); //!:
    while (i < fract->max_iter)
    {
		//printf("point [%d][%d]\n", x, y); //!:
        z = complex_sum(complex_mul(z, z), fract->c);
       // printf(" *** z_complex - reel[%lf][%lf]\n", z.r, z.i);
		if (((z.r * z.r) + (z.i * z.i)) > fract->esc_val)
		{
			//put the pixel to the img
            //printf("::::::::::::::::::::: Enters here !!!\n");
			color = color_gener(i, fract->max_iter);
            //printf(":::: %i comb %i COLOR %i !!!\n", i, fract->max_iter, color);
			//my_pixel_put(fract->img, x, y, color);
			return (color);
		}
        i++;
    }
	//my_pixel_put(fract->img, x, y, WHITE);
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