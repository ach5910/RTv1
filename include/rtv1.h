/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahunt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 08:33:08 by ahunt             #+#    #+#             */
/*   Updated: 2017/01/16 08:33:10 by ahunt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H
# include "libft.h"
# include "mlx.h"
# include <math.h>
# define WIDTH 800//512
# define HEIGHT 600//384
# define mapWidth 24
# define mapHeight 24
# define TRAN_H	0x01
# define TRAN_V	0x02
# define SIGN	0x04
# define MIN(a,b) (((a) < (b)) ? (a) : (b))

typedef struct		s_vec3
{
	float			x;
	float			y;
	float			z;
}					t_vec3;

typedef struct		s_sphere
{
	t_vec3			pos;
	float			radius;
	int 			material;
}					t_sphere;

typedef struct		s_ray
{
	t_vec3			start;
	t_vec3			dir;
}					t_ray;

typedef struct		s_color
{
	float			red;
	float			green;
	float			blue;
}					t_color;

typedef struct		s_material
{
	t_color			diffuse;
	float			reflection;
}					t_material;

typedef struct		s_light
{
	t_vec3			pos;
	t_color			intensity;
}					t_light;

typedef struct		s_img
{
	void			*i_ptr;
	int				bpp;
	int				size_line;
	int				endian;
	char			*data;
	int				w;
	int				h;
}					t_img;

typedef struct		s_line
{
	double			dx;
	double			dy;
	double			p;
	double			i;
	double			j;
	double			j_incr;
	t_vec3			*end;
	t_vec3			*start;
}					t_line;

typedef struct		s_env
{
	void			*mlx;
	void			*win;
	t_img			*img;
	double			zoom;
	unsigned int	flags;
	double			posX;
	double			posY;
	double			dirX;
	double			dirY;
	double			planeX;
	double			planeY;
	double			moveSpeed;
	double			rotSpeed;
}					t_env;

int	main(int argc, char **argv);
t_env	*init_environment(void);
t_img	*init_image(t_env *e);
int		ray_tracer(t_env *e);
int		expose_hook(t_env *e);
int		my_loop_hook(t_env *e);
int		my_key_pressed(int keycode, t_env *e);
// void    verLine(t_env *e, int x, int drawStart, int drawEnd, int color);
// void    draw_lines_y(t_env *e, t_vec2 *p1, t_vec2 * p2, int color);
// void    put_pixel_img(t_env *e, int i, int j, int color);
// t_line	*get_line_params_y(t_env *e, t_vec2 *p1, t_vec2 *p2);
// int my_key_pressed(int k, t_env *e);
// int redraw_game(t_env *e);
// int expose_hook(t_env *e);
// int		my_loop_hook(t_env *e);

#endif
