/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serraoui <serraoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 10:23:07 by serraoui          #+#    #+#             */
/*   Updated: 2024/01/12 23:01:38 by serraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int ac, char **av)
{
	t_fractol	fract;

	if (ac <= 1 || !init(ac, av, &fract))
		return (0);
	fract.mlx_ptr = mlx_init();
	fract.win_ptr = mlx_new_window(fract.mlx_ptr, WIDTH, HEIGHT, TITLE);
	fract.img->img = mlx_new_image(fract.mlx_ptr, WIDTH, HEIGHT);
	fract.img->addr = mlx_get_data_addr(fract.img->img,
			&fract.img->bpp,
			&fract.img->l_len,
			&fract.img->endian);
	render_fract(&fract);
	mlx_mouse_hook(fract.win_ptr, f_mouse_listner, &fract);
	mlx_hook(fract.win_ptr, 2, 1L << 0, f_key_listner, &fract);
	mlx_loop(fract.mlx_ptr);
	return (0);
}
