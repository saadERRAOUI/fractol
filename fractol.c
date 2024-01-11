/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serraoui <serraoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 10:23:07 by serraoui          #+#    #+#             */
/*   Updated: 2024/01/11 22:07:51 by serraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int ac, char **av)
{
    t_fractol fract;
	
	if (ac > 1)
    {
        if (init(ac, av, &fract))
        {
			render_fract(&fract);
            mlx_hook(fract.win_ptr, 2, 1L<<0, f_key_listner, &fract); 
            //! - 2 reference to onkeydown event 
            //! - 1L<<0 Mask references to keyPress 
            mlx_mouse_hook(fract.win_ptr, f_mouse_listner, &fract);
            //mlx_loop_hook(fract.mlx_ptr, render_fract, &fract);
            mlx_loop(fract.mlx_ptr);
        }
		else
		{
			//Todo : exit and error path -- print "ERROR!"
            //!Important !! 
            //Todo : Bundle this logic into one function 
            // free(vars.mlx);
            // free(vars.win);
            // free(vars.img);
            //free(t_init);
            
		}
	}
	return (0);	
}