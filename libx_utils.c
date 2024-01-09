/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libx_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serraoui <serraoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:02:41 by serraoui          #+#    #+#             */
/*   Updated: 2024/01/09 01:11:53 by serraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int init(int ac, char **av, t_fractol *fract, t_init vars)
{
	if (ft_strcmp(JULIA, av[1]) == 0)
	{
		(*fract).c.r = 0;
		(*fract).c.i = 0;
		if (ac == 4 && ft_atof(av[2], &(*fract).c.r) && ft_atof(av[3], &(*fract).c.i))
		{
			//Todo : init all the required vars in the *f;
			fract->mlx_ptr = vars.mlx;
			fract->win_ptr = vars.win;
			fract->img = &vars.img;
            fract->f_nbr = 1;
            fract->esc_val = ESC_VAL;
			fract->max_iter = MAX_ITER;
            fract->f_fract = iter_julia;
			//if done return 1 --> success
			return (1);
		}
		else
			return (0);
		//!error-path : display the options you have and errors
		//!return 0 --> error
				
	}
	else if (ft_strcmp(MANDELBROT, av[1]) == 0)
	{
		//Todo : verify that only one argument is passed to the main function
		//Todo : call the function mandelbrot_fract()...
		fract->mlx_ptr = vars.mlx;
		fract->win_ptr = vars.win;
		fract->img = &vars.img;
        fract->f_nbr = 0;
		fract->max_iter = MAX_ITER;
        fract->esc_val = ESC_VAL;
		fract->z_init = (t_complex){0, 0};
        fract->f_fract = iter_Mandelbrot;

		return (1);
	}
    else if (ft_strcmp(MANDELBAR, av[1]) == 0)
    {
        fract->mlx_ptr = vars.mlx;
		fract->win_ptr = vars.win;
		fract->img = &vars.img;
        fract->f_nbr = 2;
        fract->max_iter = MAX_ITER;
        fract->esc_val = ESC_VAL;
		fract->z_init = (t_complex){0, 0};
        fract->f_fract = iter_Mandelbar;
        return (1);
    }

	return (0);
}

void	my_pixel_put(t_data *img, int x, int y, int color)
{
	int	offset;

	offset = (img->l_len * y) + (x * (img->bpp / 8));
	*((unsigned int *)(offset + img->addr)) = color;
}

int    f_key_listner(int keycode, t_fractol fract)
{
    printf("[NOTIF] -> this key is pressed -> [%d]\n", keycode);
    if (keycode == ESCAPE_KEY)
    {
        printf("%p -- %p \n", fract.mlx_ptr, fract.win_ptr);
        mlx_destroy_window(fract.mlx_ptr, fract.win_ptr);
        mlx_destroy_image(fract.mlx_ptr, fract.img->img);
        free(fract.mlx_ptr);
        fract.mlx_ptr = NULL;
    }
    return (0);
}