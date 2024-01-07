/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serraoui <serraoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 10:23:07 by serraoui          #+#    #+#             */
/*   Updated: 2024/01/07 16:46:28 by serraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int ac, char **av)
{
	double f1, f2;
	
	if (ac > 1)
	{
		if (ft_strcmp("Julia", av[1]))
		{
			//Todo : should accept 2 args (doubles)
			//Todo : call the function julia_fract()...
			//check wether the number of args is exactly 4
			//and check if the 2 last args are floats arguments;
			//ex : ./fractol -0.21 1.0 --> valid input
			f1 = 0;
			f2 = 0;
			if (ac == 4 && ft_atof(av[2], &f1) && ft_atof(av[3], &f2))
			{
				//calls function Julia with julia(atof(av[2], av[]))
				init();
				
			}
			//else
			//!error-path : display the options you have and errors 
				 
		}
		else if (ft_strcmp("Mandelbrot", av[1]))
		{
			//Todo : verify that only one argument is passed to the main function
			//Todo : call the function mandelbrot_fract()...
			
		}
		//! We'll see if the bonus we add another fract
		//! ********************************************
		else
		{
			//Todo : exit and error path -- print "ERROR!"
		}
	}
	return (0);	
}