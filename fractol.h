/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serraoui <serraoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 10:23:40 by serraoui          #+#    #+#             */
/*   Updated: 2024/01/07 16:47:53 by serraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>
# include <mlx.h>

# define WIDTH 800
# define HEIGHT 600

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;


typedef struct s_fractol
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_data	*img;
	int		width;
	int		height;
	// int		*color;
	int		max_iter;
	// int		(*fractal)(struct s_fractol *fractol, double x, double y);
	// double	zoom;
	// double	x1;
	// double	y1;
	// double	x2;
	// double	y2;
	// double	c_r;
	// double	c_i;
	// double	z_r;
	// double	z_i;
	// double	tmp;
}				t_fractol;

int     ft_strcmp(const char *s1, const char *s2);
int     ft_atof(const char *s, double *arg);

#endif