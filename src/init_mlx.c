/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahunt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 08:43:18 by ahunt             #+#    #+#             */
/*   Updated: 2017/01/16 08:43:31 by ahunt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_img	*init_image(t_env *e)
{
	t_img *img;

	img = (t_img*)malloc(sizeof(t_img));
	img->i_ptr = mlx_new_image(e->mlx, WIDTH, HEIGHT);
	img->w = WIDTH / 2;
	img->h = HEIGHT / 2;
	img->data = mlx_get_data_addr(img->i_ptr, &img->bpp, &img->size_line,
		&img->endian);
	return (img);
}

t_env	*init_environment(void)
{
	t_env			*e;

	e = (t_env*)malloc(sizeof(t_env));
	e->mlx = mlx_init();
	mlx_do_key_autorepeatoff(e->mlx);
	e->win = mlx_new_window(e->mlx, WIDTH, HEIGHT, "RTv1");
	e->flags = 0;
	e->posX = 0.0f;
	e->posY = 0.0f;
	e->posZ = -500.0f;
	e->theta = 0;
	e->img = init_image(e);
	return (e);
}
