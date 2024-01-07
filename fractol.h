/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serraoui <serraoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 10:23:40 by serraoui          #+#    #+#             */
/*   Updated: 2024/01/07 18:28:36 by serraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>
# include <mlx.h>

# define WIDTH 800
# define HEIGHT 600
# define TITLE "Fractol"
# define JULIA "Julia"
# define MAX_ITER 250 //Just for display quality
# define MANDELBROT "Mandelbrot"

typedef struct	s_init
{
	void	*mlx;
	void	*win;
	t_data	img;
}				t_init;
typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		l_len;
	int		endian;
}				t_data;

typedef struct s_fractol
{
	//void	*mlx_ptr;
	//void	*win_ptr;
	///t_data	*img;
	// int		width;
	// int		height;
	// int		*color;
	int		max_iter;
	double 	esc_val; //value from where the fractal iteration goes to infinity
	// int		(*fractal)(struct s_fractol *fractol, double x, double y);
	// double	zoom;
	// double	x1;
	// double	y1;
	// double	x2;
	// double	y2;
	t_complex	c;
	// double	z_r;
	// double	z_i;
	// double	tmp;
}				t_fractol;

typedef struct	s_complex
{
	double	r;
	double	i;
}				t_complex;

int     ft_strcmp(const char *s1, const char *s2);
int     ft_atof(const char *s, double *arg);

#endif