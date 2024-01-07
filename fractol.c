/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serraoui <serraoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 10:23:07 by serraoui          #+#    #+#             */
/*   Updated: 2024/01/07 21:42:53 by serraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int ac, char **av)
{
    t_fractol fract;
    t_init vars;
	
	if (ac > 1)
	{
        vars.mlx = mlx_init();
        vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, TITLE);
        vars.img.img = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
        vars.img.addr = mlx_get_data_addr(vars.img.img, 
                                                        &vars.img.bpp, 
                                                        &vars.img.l_len, 
                                                        &vars.img.endian);
        if (init(ac, av, &fract, vars))
		{
			printf("Enters here ### ");
			render_fract(&fract);
		}
		else
		{
			//Todo : exit and error path -- print "ERROR!"
            //!Important !! 
            //Todo : Bundle this logic into one function 
            free(vars.mlx);
            free(vars.win);
            // free(vars.img);
            //free(t_init);
            
		}
	}
	return (0);	
}