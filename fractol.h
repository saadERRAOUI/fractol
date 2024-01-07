/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serraoui <serraoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 10:23:40 by serraoui          #+#    #+#             */
/*   Updated: 2024/01/07 21:43:01 by serraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>
# include <stdio.h>
# include "mlx/mlx.h"

# define WIDTH 800
# define HEIGHT 600
# define TITLE "Fractol"
# define JULIA "Julia"
# define MAX_ITER 250 //Just for display quality
# define MANDELBROT "Mandelbrot"
# define BLACK 0x000000
# define WHITE 0xFFFFFF

typedef struct	s_complex
{
	double	r;
	double	i;
}				t_complex;

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		l_len;
	int		endian;
}				t_data;

typedef struct	s_init
{
	void	*mlx;
	void	*win;
	t_data	img;
}				t_init;

typedef struct s_fractol
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_data	*img;
	int		max_iter;
	double 	esc_val; //value from where the fractal iteration goes to infinity
	t_complex	c;
	t_complex	z_init;
}				t_fractol;

int     ft_strcmp(const char *s1, const char *s2);
int     ft_atof(const char *s, double *arg);
int		init(int ac, char **av, t_fractol *fract, t_init vars);
void	render_fract(t_fractol *fract);
void	my_pixel_put(t_data *img, int x, int y, int color);

#endif