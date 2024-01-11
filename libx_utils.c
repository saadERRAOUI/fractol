/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libx_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serraoui <serraoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:02:41 by serraoui          #+#    #+#             */
/*   Updated: 2024/01/11 22:08:40 by serraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int init(int ac, char **av, t_fractol *fract)
{
    fract->mlx_ptr = mlx_init();
    fract->win_ptr = mlx_new_window(fract->mlx_ptr, WIDTH, HEIGHT, TITLE);
    fract->img->img = mlx_new_image(fract->mlx_ptr, WIDTH, HEIGHT);
    fract->img->addr = mlx_get_data_addr(fract->img->img, 
                                                    &fract->img->bpp, 
                                                    &fract->img->l_len, 
                                                    &fract->img->endian);
    fract->esc_val = ESC_VAL;
    fract->max_iter = MAX_ITER;
    fract->x_min = -2;
    fract->x_max = +2;
    fract->y_min = +2;
    fract->y_max = -2;
    fract->x_shift = 0;
    fract->y_shift = 0;                                                    
	if (ft_strcmp(JULIA, av[1]) == 0)
        return (init_julia(fract, ac, av));
	else if (ft_strcmp(MANDELBROT, av[1]) == 0)
        return (init_mandel(fract, ac, 0));
    else if (ft_strcmp(MANDELBAR, av[1]) == 0)
        return (init_mandel(fract, ac, 2));
	return (0);
}

void hndl_view_move(int key, t_fractol *fract)
{
   // printf("Handle arrow press %d \n", key);
    if (key == AR_U_KEY) //manage to add +0.125 to the y value
        fract->y_shift += 0.0125;
    if (key == AR_D_KEY) //manage to remove -0.125 to the y value
        fract->y_shift -= 0.0125;
    if (key == AR_L_KEY) //manage to add +0.125 to the x value
        fract->x_shift -= 0.0125;
    if (key == AR_R_KEY) //manage to remove -0.125 to the x value
        fract->x_shift += 0.0125;
    mlx_clear_window(fract->mlx_ptr, fract->win_ptr);
    render_fract(fract);
}

void	my_pixel_put(t_data *img, int x, int y, int color)
{
	int	offset;

	offset = (img->l_len * y) + (x * (img->bpp / 8));
	*((unsigned int *)(offset + img->addr)) = color;
}

int f_key_listner(int keycode, t_fractol *fract)
{
    if (keycode == ESC_KEY)
        exit(1);
    else if (keycode == AR_U_KEY || keycode == AR_D_KEY || keycode == AR_L_KEY || keycode == AR_R_KEY)
        hndl_view_move(keycode, fract);
    return (0);
}

int f_mouse_listner(int button, int x, int y, t_fractol *fract)
{
    //!Todo : protect from other mouse events
    double _x, _y;
    int sign = 0;
    _x = scale_nbr(x, fract->x_max, fract->x_min, 0, HEIGHT);
    _y = scale_nbr(y, fract->y_max, fract->y_min, 0, WIDTH);
    if (button == MOUSE_IN_KEY)
        sign = 1;
    else if (button == MOUSE_OUT_KEY)
        sign = -1;
    calc_coeffs(fract, _x, _y, sign);
    return (0);
}