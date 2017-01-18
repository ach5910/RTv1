/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahunt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 12:41:46 by ahunt             #+#    #+#             */
/*   Updated: 2017/01/17 12:41:54 by ahunt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec3	vec_sub(t_vec3 *v1, t_vec3 *v2)
{
	t_vec3	result;

	result.x = v1->x - v2->x;
	result.y = v1->y - v2->y;
	result.z = v1->z - v2->z;
	return (result);
}

float	vec_dot(t_vec3 *v1, t_vec3 *v2)
{
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}

t_vec3	vec_scale(float c, t_vec3 *v)
{
	t_vec3	result;

	result.x = v->x * c;
	result.y = v->y * c;
	result.z = v->z * c;
	return (result);
}

t_vec3	vec_add(t_vec3 *v1, t_vec3 *v2)
{
	t_vec3	result;

	result.x = v1->x + v2->x;
	result.y = v1->y + v2->y;
	result.z = v1->z + v2->z;
	return (result);
}

int		inter_sphere(t_ray *r, t_sphere *s, float *t)
{
	float A = vec_dot(&r->dir, &r->dir);
	t_vec3 dist = vec_sub(&r->start, &s->pos);
	float B = 2 * vec_dot(&r->dir, &dist);
	float C = vec_dot(&dist, &dist) - (s->radius * s->radius);
	float discr = B * B - 4 * A * C;
	if (discr < 0)
	{
		printf("First Return A = %f B = %f C = %f\n", A, B, C);
		return (0);
	}
	float sqr_discr = sqrtf(discr);
	float t0 = (-B + sqr_discr) / 2;
	float t1 = (-B - sqr_discr) / 2;
	if (t0 > t1)
		t0 = t1;
	if ((t0 > 0.001f ) && (t0 < *t))
	{
		*t = t0;
		return (1);
	}
	return (0);
}

int		main(int argc, char **argv)
{
	t_env *e;
	t_ray r;
	int x;
	int y;
	int init;

	e = init_environment();
	t_material materials[3];
	materials[0].diffuse.red = 1;
	materials[0].diffuse.green = 0;
	materials[0].diffuse.blue = 0;
	materials[0].reflection = 0.2;

	materials[1].diffuse.red = 0;
	materials[1].diffuse.green = 1;
	materials[1].diffuse.blue = 0;
	materials[1].reflection = 0.5;

	materials[2].diffuse.red = 0;
	materials[2].diffuse.green = 0;
	materials[2].diffuse.blue = 1;
	materials[2].reflection = 0.9;

	t_sphere spheres[3];
	spheres[0].pos.x = 200;
	spheres[0].pos.y = 300;
	spheres[0].pos.z = 0;
	spheres[0].radius = 100;
	spheres[0].material = 0;

	spheres[1].pos.x = 400;
	spheres[1].pos.y = 400;
	spheres[1].pos.z = 0;
	spheres[1].radius = 100;
	spheres[1].material = 1;

	spheres[2].pos.x = 500;
	spheres[2].pos.y = 140;
	spheres[2].pos.z = 0;
	spheres[2].radius = 100;
	spheres[2].material = 2;

	t_light lights[3];

	lights[0].pos.x = 0;
	lights[0].pos.y = 240;
	lights[0].pos.z = -100;
	lights[0].intensity.red = 1;
	lights[0].intensity.green = 1;
	lights[0].intensity.blue = 1;

	lights[1].pos.x = 3200;
	lights[1].pos.y = 3000;
	lights[1].pos.z = -1000;
	lights[1].intensity.red = 0.6;
	lights[1].intensity.green = 0.7;
	lights[1].intensity.blue = 1;

	lights[2].pos.x = 600;
	lights[2].pos.y = 0;
	lights[2].pos.z = -100;
	lights[2].intensity.red = 0.3;
	lights[2].intensity.green = 0.5;
	lights[2].intensity.blue = 1;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			float red  = 0;
			float green = 0;
			float blue = 0;
			int level = 0;
			float coef = 1.0f;
			r.start.x = x;
			r.start.y = y;
			r.start.z = -2000.0f;
			r.dir.x = 0;
			r.dir.y = 0;
			r.dir.z = 1;
			init = 1;
			while (((coef > 0.0f) && (level < 15)) || init == 1)
			{
				init = 0;
				float t = 20000.0f;
				int cur_sphere = -1;
				int i = 0;
				while (i < 3)
				{
					if (inter_sphere(&r, &spheres[i], &t))
						cur_sphere = i;
					i++;
				}
				if (cur_sphere == -1)
				{
					// printf("Break1\n");
					break ;
				}
				printf("NOT Break1\n");
				t_vec3 scaled = vec_scale(t, &r.dir);
				t_vec3 new_start = vec_add(&r.start, &scaled);
				t_vec3 n = vec_sub(&new_start, &spheres[cur_sphere].pos);
				float temp = vec_dot(&n, &n);
				if (temp == 0)
				{
					printf("Break2\n");
					break;
				}
				temp = 1.0f / sqrtf(temp);
				n = vec_scale(temp, &n);
				t_material cur_mat = materials[spheres[cur_sphere].material];
				int j = 0;
				while (j < 3)
				{
					t_light cur_light = lights[j];
					t_vec3 dist = vec_sub(&cur_light.pos, &new_start);
					if (vec_dot(&n, &dist) <= 0.0f)
						continue ;
					float t = sqrt(vec_dot(&dist, &dist));
					if (t <= 0.0f)
						continue;
					t_ray light_ray;
					light_ray.start = new_start;
					light_ray.dir = vec_scale((1.0f / t), &dist);
					float lambert = vec_dot(&light_ray.dir, &n) * coef;
					printf("Lamber %f\n", lambert);
					red += lambert * cur_light.intensity.red * cur_mat.diffuse.red;
					green += lambert * cur_light.intensity.green * cur_mat.diffuse.green;
					blue += lambert * cur_light.intensity.blue * cur_mat.diffuse.blue;
					j++;
				}
				coef *= cur_mat.reflection;
				r.start = new_start;
				float reflect = 2.0f * vec_dot(&r.dir, &n);
				t_vec3 tmp = vec_scale(reflect, &n);
				r.dir = vec_sub(&r.dir, &tmp);
				level++;
			}
			int	p;
			p = (x * 4) + (y * e->img->size_line);
			e->img->data[p] = (char)MIN(red * 255.0f, 255.0f);
			e->img->data[++p] = (char)MIN(green * 255.0f, 255.0f);
			e->img->data[++p] = (char)MIN(blue * 255.0f, 255.0f);
			//printf("X = %d Red = %f Green %f Blue %f\n", x, red * 255.0f, green * 255.0f, blue * 255.0f);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(e->mlx, e->win, e->img->i_ptr, 0, 0);
	mlx_destroy_image(e->mlx, e->img->i_ptr);
	e->img->i_ptr = mlx_new_image(e->mlx, WIDTH, HEIGHT);
	mlx_loop(e->mlx);
	return (0);
}
