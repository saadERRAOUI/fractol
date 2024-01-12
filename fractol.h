/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serraoui <serraoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 10:23:40 by serraoui          #+#    #+#             */
/*   Updated: 2024/01/12 22:10:44 by serraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>
# include <stdio.h>
# include <mlx.h>

# define WIDTH 1000
# define HEIGHT 900
# define TITLE "Fractol"
# define JULIA "Julia"
# define MAX_ITER 100
# define MANDELBROT "Mandelbrot"
# define MANDELBAR "Mandelbar"
# define ESC_VAL 4
# define BLACK 0x000000
# define WHITE 0xFFFFFF
# define ESC_KEY 53
# define AR_U_KEY 126
# define AR_D_KEY 125
# define AR_L_KEY 123
# define AR_R_KEY 124
# define MOUSE_IN_KEY 4
# define MOUSE_OUT_KEY 5

typedef struct s_fractol t_fractol;

typedef int (*t_func)(t_fractol *);

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

typedef struct s_fractol
{
    double      ratio;
	void        *mlx_ptr;
	void        *win_ptr;
	int         f_nbr;
	t_data      *img;
	int         max_iter;
	double      esc_val;
	t_complex	c;
	t_complex	z_init;
	t_func      f_fract;
	double      x_min;
	double      x_max;
	double      y_min;
	double      y_max;
	double      x_shift;
	double      y_shift;
    double      z_coeff;
}				t_fractol;

int			ft_strcmp(const char *s1, const char *s2);
int			ft_atof(const char *s, double *arg);
int			init(int ac, char **av, t_fractol *fract);
int			render_fract(t_fractol *fract);
void		my_pixel_put(t_data *img, int x, int y, int color);
int     	iter_Mandelbrot(t_fractol *fract);
int			iter_julia(t_fractol *fract);
int			iter_Mandelbar(t_fractol *fract);
int			f_key_listner(int keycode, t_fractol *fract);
t_complex	complex_mul(t_complex cmp1, t_complex cmp2);
t_complex	complex_bar(t_complex cmp);
t_complex	complex_sum(t_complex cmp1, t_complex cmp2);
int			init_mandel(t_fractol *fract, int ac, int f_nbr);
int			init_julia(t_fractol *fract, int ac, char **av);
int         f_mouse_listner(int button, int x, int y, t_fractol *fract);
void        calc_coeffs(t_fractol *fract, int x, int y, int sign);
double      scale_nbr(double nbr, double n_max, double n_min, double o_min, double o_max);

#endif