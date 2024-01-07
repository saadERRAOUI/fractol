/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libx_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serraoui <serraoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:02:41 by serraoui          #+#    #+#             */
/*   Updated: 2024/01/07 21:40:58 by serraoui         ###   ########.fr       */
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
			fract->max_iter = MAX_ITER;
			
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
		fract->max_iter = MAX_ITER;
		fract->z_init = (t_complex){0, 0};

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