/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serraoui <serraoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 10:23:07 by serraoui          #+#    #+#             */
/*   Updated: 2024/01/03 11:53:03 by serraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int ac, char **av)
{
	if (ac > 1)
	{
		if (ft_strcmp("Julia", av[1]))
		{
			//Todo : should accept 2 args (doubles)
			//Todo : call the function julia_fract()...
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