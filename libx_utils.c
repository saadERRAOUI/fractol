/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libx_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serraoui <serraoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:02:41 by serraoui          #+#    #+#             */
/*   Updated: 2024/01/12 22:29:32 by serraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* ---------------------------------------------------------------------------
	@_PROTO_ : int init(int ac, char **av, t_fractol *fract)
	@_DESCRIPTTION_ :
		* Initialize the t_fractol struct var with the needed infos
		* Call different init_**fract** methods to assign specific vars
	@_AUTHOR_ : @saad_erraoui
	@_DATE_ : 12-01-2024
----------------------------------------------------------------------------- */
int	init(int ac, char **av, t_fractol *fract)
{
	fract->esc_val = ESC_VAL;
	fract->max_iter = MAX_ITER;
	fract->x_min = -2;
	fract->x_max = 2;
	fract->y_min = -2;
	fract->y_max = 2;
	fract->z_coeff = 0.15;
	fract->ratio = 1;
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

/* ---------------------------------------------------------------------------
	@_PROTO_ :  void hndl_view_move(int, t_fractol)
	@_DESCRIPTTION_ :
		* Handle the view move using arrow keys
		* Add/Remove the _CONSTANT=0.125 to the fract y_shift struct property
	@_AUTHOR_ : @saad_erraoui
	@_DATE_ : 12-01-2024
----------------------------------------------------------------------------- */
void	hndl_view_move(int key, t_fractol *fract)
{
	printf("fract->ratio == %lf\n", fract->ratio);
	if (key == AR_U_KEY)
		fract->y_shift -= 0.5 / fract->ratio;
	if (key == AR_D_KEY)
		fract->y_shift += 0.5 / fract->ratio;
	if (key == AR_L_KEY)
		fract->x_shift -= 0.5 / fract->ratio;
	if (key == AR_R_KEY)
		fract->x_shift += 0.5 / fract->ratio;
	mlx_clear_window(fract->mlx_ptr, fract->win_ptr);
	render_fract(fract);
}

/* ---------------------------------------------------------------------------
	@_PROTO_ :  void my_pixel_put(t_data *img, int x, int y, int color)
	@_DESCRIPTTION_ :
		* Put a pixel to my image t_data instance
		* Use memory alignment approach
	@_AUTHOR_ : @saad_erraoui
	@_DATE_ : 12-01-2024
----------------------------------------------------------------------------- */
void	my_pixel_put(t_data *img, int x, int y, int color)
{
	int	offset;

	offset = (img->l_len * y) + (x * (img->bpp / 8));
	*((unsigned int *)(offset + img->addr)) = color;
}

/* ---------------------------------------------------------------------------
	@_PROTO_ : int f_key_listner(int keycode, t_fractol *fract)
	@_DESCRIPTTION_ :
		* Handle the key press event
		* Call the hndl_view_move() func for the arrow keys events
		* Call the exit_path() func if the esc key is pressed
	@_AUTHOR_ : @saad_erraoui
	@_DATE_ : 12-01-2024
----------------------------------------------------------------------------- */
int	f_key_listner(int keycode, t_fractol *fract)
{
	if (keycode == ESC_KEY)
		exit(1);
	else if (keycode == AR_U_KEY
		|| keycode == AR_D_KEY
		|| keycode == AR_L_KEY
		|| keycode == AR_R_KEY)
		hndl_view_move(keycode, fract);
	return (0);
}

/* ---------------------------------------------------------------------------
	@_PROTO_ : int f_mouse_listner(int button, int x, int y, t_fractol *fract)
	@_DESCRIPTTION_ :
		* Handle the mouse up and down events
		* Check wether the event is a scroll down or up
		* Call calc_coeffs() func with different signs (-1, 1)
	@_AUTHOR_ : @saad_erraoui
	@_DATE_ : 12-01-2024
----------------------------------------------------------------------------- */
int	f_mouse_listner(int button, int x, int y, t_fractol *fract)
{
	if (button == MOUSE_OUT_KEY)
		calc_coeffs(fract, x, y, 1);
	else if (button == MOUSE_IN_KEY)
		calc_coeffs(fract, x, y, -1);
	return (0);
}
