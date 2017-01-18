/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahunt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 07:52:33 by ahunt             #+#    #+#             */
/*   Updated: 2017/01/18 07:52:37 by ahunt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/* A simple ray tracer */
#include "rtv1.h"
#include <stdio.h>
#include <stdbool.h> /* Needed for boolean datatype */
#include <math.h>

#define min(a,b) (((a) < (b)) ? (a) : (b))

/* Width and height of out image */
// #define WIDTH  800
// #define HEIGHT 600

// /* The vector structure */
// typedef struct{
// 	float x,y,z;
// }vector;
//
// /* The sphere */
// typedef struct{
//         vector pos;
//         float  radius;
// 	int material;
// }sphere;
//
// /* The ray */
// typedef struct{
//         vector start;
//         vector dir;
// }ray;
//
// /* Colour */
// typedef struct{
// 	float red, green, blue;
// }colour;
//
// /* Material Definition */
// typedef struct{
// 	colour diffuse;
// 	float reflection;
// }material;
//
// /* Lightsource definition */
// typedef struct{
// 	vector pos;
// 	colour intensity;
// }light;
//
// /* Subtract two vectors and return the resulting vector */
// vector vectorSub(vector *v1, vector *v2){
// 	vector result = {v1->x - v2->x, v1->y - v2->y, v1->z - v2->z };
// 	return result;
// }
//
// /* Multiply two vectors and return the resulting scalar (dot product) */
// float vectorDot(vector *v1, vector *v2){
// 	return v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
// }
//
// /* Calculate Vector x Scalar and return resulting Vector*/
// vector vectorScale(float c, vector *v){
//         vector result = {v->x * c, v->y * c, v->z * c };
//         return result;
// }
//
// /* Add two vectors and return the resulting vector */
// vector vectorAdd(vector *v1, vector *v2){
//         vector result = {v1->x + v2->x, v1->y + v2->y, v1->z + v2->z };
//         return result;
// }
//
// /* Check if the ray and sphere intersect */
// bool intersectRaySphere(ray *r, sphere *s, float *t){
//
// 	bool retval = false;
//
// 	/* A = d.d, the vector dot product of the direction */
// 	float A = vectorDot(&r->dir, &r->dir);
//
// 	/* We need a vector representing the distance between the start of
// 	 * the ray and the position of the circle.
// 	 * This is the term (p0 - c)
// 	 */
// 	vector dist = vectorSub(&r->start, &s->pos);
//
// 	/* 2d.(p0 - c) */
// 	float B = 2 * vectorDot(&r->dir, &dist);
//
// 	/* (p0 - c).(p0 - c) - r^2 */
// 	float C = vectorDot(&dist, &dist) - (s->radius * s->radius);
//
// 	/* Solving the discriminant */
// 	float discr = B * B - 4 * A * C;
//
// 	/* If the discriminant is negative, there are no real roots.
// 	 * Return false in that case as the ray misses the sphere.
// 	 * Return true in all other cases (can be one or two intersections)
// 	 * t represents the distance between the start of the ray and
// 	 * the point on the sphere where it intersects.
// 	 */
// 	if(discr < 0)
// 		retval = false;
// 	else{
// 		float sqrtdiscr = sqrtf(discr);
// 		float t0 = (-B + sqrtdiscr)/(2);
// 		float t1 = (-B - sqrtdiscr)/(2);
//
// 		/* We want the closest one */
// 		if(t0 > t1)
// 			t0 = t1;
//
// 		/* Verify t1 larger than 0 and less than the original t */
// 		if((t0 > 0.001f) && (t0 < *t)){
// 			*t = t0;
// 			retval = true;
// 		}else
// 			retval = false;
// 	}
//
// return retval;
// }

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
		return (0);
	float sqr_discr = sqrtf(discr);
	float t0 = (-B + sqr_discr) / 2;//(A * 2);
	float t1 = (-B - sqr_discr) / 2;//(A * 2);
	if (t0 > t1)
		t0 = t1;
	if ((t0 > 0.001f ) && (t0 < *t))
	{
		*t = t0;
		return (1);
	}
	return (0);
}


int main(int argc, char **argv)
{
	t_env *e;

	e = init_environment();
	ray_tracer(e);
	mlx_expose_hook(e->win, expose_hook, e);
	mlx_hook(e->win, 2, 0, my_key_pressed, e);
	mlx_loop_hook(e->mlx, my_loop_hook, e);
	mlx_loop(e->mlx);
	return 0;
}

int ray_tracer(t_env *e)
{
	t_ray r;

	t_material materials[9];
	materials[0].diffuse.red = 0.3725;
	materials[0].diffuse.green = 0.078;//0;
	materials[0].diffuse.blue = 0.3764;//0;
	materials[0].reflection = 0.2f;

	materials[1].diffuse.red = 255.0f / 255.0f;//0;
	materials[1].diffuse.green = 255.0f / 255.0f;
	materials[1].diffuse.blue = 150.0f / 255.0f;//0;
	materials[1].reflection = 0.0f;//0.5;

	materials[2].diffuse.red = 255.0f / 255.0f;//0;
	materials[2].diffuse.green = 140.0f / 255.0f;//0;
	materials[2].diffuse.blue = 0.0f / 255.0f;
	materials[2].reflection = 0.7f;

	materials[3].diffuse.red = 152.0f / 255.0f;//0;
	materials[3].diffuse.green = 251.0f / 255.0f;//0;
	materials[3].diffuse.blue = 152.0f / 255.0f;
	materials[3].reflection = 0.2f;

	materials[4].diffuse.red = 166.0f / 255.0f;//0;
	materials[4].diffuse.green = 216.0f / 255.0f;//0;
	materials[4].diffuse.blue = 252.0f / 255.0f;
	materials[4].reflection = 0.01f;

	materials[5].diffuse.red = 252.0f / 255.0f;//0;
	materials[5].diffuse.green = 166.0f / 255.0f;//0;
	materials[5].diffuse.blue = 166.0f / 255.0f;
	materials[5].reflection = 0.5f;

	materials[6].diffuse.red = 29.0f / 255.0f;//0;
	materials[6].diffuse.green = 14.0f / 255.0f;//0;
	materials[6].diffuse.blue = 163.0f / 255.0f;
	materials[6].reflection = 0.3f;

	materials[7].diffuse.red = 163.0f / 255.0f;//0;
	materials[7].diffuse.green = 14.0f / 255.0f;//0;
	materials[7].diffuse.blue = 14.0f / 255.0f;
	materials[7].reflection = 0.05f;

	materials[8].diffuse.red = 63.0f / 255.0f;//0;
	materials[8].diffuse.green = 255.0f / 255.0f;//0;
	materials[8].diffuse.blue = 0.0f / 255.0f;
	materials[8].reflection = 0.05f;


	t_sphere spheres[9];
	spheres[0].pos.x = 200;
	spheres[0].pos.y = 300;
	spheres[0].pos.z = 0;
	spheres[0].radius = 100;
	spheres[0].material = 0;

	spheres[1].pos.x = 800;
	spheres[1].pos.y = 600;
	spheres[1].pos.z = 0;
	spheres[1].radius = 200;
	spheres[1].material = 3;
	
	spheres[2].pos.x = 500;
	spheres[2].pos.y = 140;
	spheres[2].pos.z = 0;
	spheres[2].radius = 100;
	spheres[2].material = 2;

	spheres[3].pos.x = 400;//e->posX;
	spheres[3].pos.y = 300;//e->posY;
	spheres[3].pos.z = 150;//0;
	spheres[3].radius = 10;//100;
	spheres[3].material = 1;

	spheres[4].pos.x = 100;
	spheres[4].pos.y = 100;
	spheres[4].pos.z = 300;//0;
	spheres[4].radius = 30;//100;
	spheres[4].material = 4;

	spheres[5].pos.x = 600;
	spheres[5].pos.y = 100;
	spheres[5].pos.z = -100;//0;
	spheres[5].radius = 50;//100;
	spheres[5].material = 5;

	spheres[6].pos.x = 25;
	spheres[6].pos.y = 500;
	spheres[6].pos.z = -200;//0;
	spheres[6].radius = 80;//100;
	spheres[6].material = 6;

	spheres[7].pos.x = 450;
	spheres[7].pos.y = 525;
	spheres[7].pos.z = 200;//0;
	spheres[7].radius = 120;//100;
	spheres[7].material = 7;

	spheres[8].pos.x = 675;
	spheres[8].pos.y = 340;
	spheres[8].pos.z = 300;//0;
	spheres[8].radius = 150;//100;
	spheres[8].material = 8;

	t_light lights[3];

	lights[0].pos.x = e->posX;//0;
	lights[0].pos.y = e->posY;//240;
	lights[0].pos.z = e->posZ;
	lights[0].intensity.red = 1.0f;
	lights[0].intensity.green = 1.0f;
	lights[0].intensity.blue = 1.0f;

	// lights[1].pos.x = 10;//600;
	// lights[1].pos.y = 10;
	// lights[1].pos.z = 0;//-1000;//-100
	// lights[1].intensity.red = 1;//0.3;
	// lights[1].intensity.green = 1;//0.5;
	// lights[1].intensity.blue = 1;

	lights[1].pos.x = 3200;
	lights[1].pos.y = 3000;
	lights[1].pos.z = -1000;
	lights[1].intensity.red = 1.0;//0.6;
	lights[1].intensity.green = 1.0;//0.7;
	lights[1].intensity.blue = 1;

	lights[2].pos.x = 10;//600;
	lights[2].pos.y = 10;
	lights[2].pos.z = 0;//-1000;//-100
	lights[2].intensity.red = 1;//0.3;
	lights[2].intensity.green = 1;//0.5;
	lights[2].intensity.blue = 1;

	/* Will contain the raw image */
	// unsigned char img[3*WIDTH*HEIGHT];


	int y = 0;
	while(y < HEIGHT)
	{
		int x = 0;
		while (x < WIDTH)
		{

			float red = 0;
			float green = 0;
			float blue = 0;

			int level = 0;
			float coef = 1.0;

			r.start.x = x;
			r.start.y = y;
			r.start.z = -2000;

			r.dir.x = 0;
			r.dir.y = 0;
			r.dir.z = 1;

			int init = 1;
			while(((coef > 0.001f) && (level < 15)) || init == 1)
			{
				init = 0;
				/* Find closest intersection */
				float t = 20000.0f;
				int currentSphere = -1;

				int i = -1;
				while(++i < 9)
				{
					if(inter_sphere(&r, &spheres[i], &t))
						currentSphere = i;
				}
				if(currentSphere == -1) break;

				t_vec3 scaled = vec_scale(t, &r.dir);
				t_vec3 newStart = vec_add(&r.start, &scaled);

				/* Find the normal for this new vector at the point of intersection */
				t_vec3 n = vec_sub(&newStart, &spheres[currentSphere].pos);
				float temp = vec_dot(&n, &n);
				if(temp == 0)
					break ;
				temp = 1.0f / sqrtf(temp);
				n = vec_scale(temp, &n);

				/* Find the material to determine the colour */
				t_material currentMat = materials[spheres[currentSphere].material];

				/* Find the value of the light at this point */
				int j = -1;
				while (++j < 3)
				{
					t_light currentLight = lights[j];
					t_vec3 dist = vec_sub(&currentLight.pos, &newStart);
					if(vec_dot(&n, &dist) <= 0.0f) continue;
					float t = sqrtf(vec_dot(&dist,&dist));
					if(t <= 0.0f) continue;

					t_ray lightRay;
					lightRay.start = newStart;
					lightRay.dir = vec_scale((1/t), &dist);

					/* Calculate shadows */
					int inShadow = 0;
					int k = -1;
					while (++k < 9)
					{
						if (inter_sphere(&lightRay, &spheres[k], &t))
						{
							inShadow = 1;
							break;
						}
					}
					if (!inShadow){
						/* Lambert diffusion */
						float lambert = vec_dot(&lightRay.dir, &n) * coef;
						red += lambert * currentLight.intensity.red * currentMat.diffuse.red;
						green += lambert * currentLight.intensity.green * currentMat.diffuse.green;
						blue += lambert * currentLight.intensity.blue * currentMat.diffuse.blue;
					}
				}
				/* Iterate over the reflection */
				coef *= currentMat.reflection;

				/* The reflected ray start and direction */
				r.start = newStart;
				float reflect = 2.0f * vec_dot(&r.dir, &n);
				t_vec3 tmp = vec_scale(reflect, &n);
				r.dir = vec_sub(&r.dir, &tmp);

				level++;

			}

			// if (level > 1 ) printf("Level = %d\t",level);
			int	p;
			p = (x * 4) + (y * e->img->size_line);
			e->img->data[p] = (char)min(blue * 255.0f, 255.0f);
			e->img->data[++p] = (char)min(green * 255.0f, 255.0f);
			e->img->data[++p] = (char)min(red * 255.0f, 255.0f);
			x++;
		}
		y++;
	}
	int	p;
	p = (e->posX * 4) + (e->posY * e->img->size_line);
	e->img->data[p] = 0xFF;
	e->img->data[++p] = 0xFF;
	e->img->data[++p] = 0xFF;
	mlx_put_image_to_window(e->mlx, e->win, e->img->i_ptr, 0, 0);
	mlx_destroy_image(e->mlx, e->img->i_ptr);
	e->img->i_ptr = mlx_new_image(e->mlx, WIDTH, HEIGHT);
	return (0);
}

int expose_hook(t_env *e)
{
	ray_tracer(e);
	return (0);
}

int my_loop_hook(t_env *e)
{
	if (e->flags & SIGN)
	{
		if (e->flags & TRAN_V)
		{
			e->posY -= 5;
		}
		else if (e->flags & TRAN_H)
		{
			e->posX -= 5;
		}
		else if (e->flags & TRAN_Z)
			e->posZ -= 20;
	}
	else if (e->flags & TRAN_V)
	{
		e->posY += 5;
	}
	else if (e->flags & TRAN_H)
	{
		e->posX += 5;
	}
	else if (e->flags & TRAN_Z)
		e->posZ += 20;
	if (e->flags)
	{
		e->flags = 0;
		ray_tracer(e);
	}
	return (0);
}

int my_key_pressed(int keycode, t_env *e)
{

	if (keycode == 125)
	{
		e->flags |= TRAN_V;
	}
	else if (keycode == 126)
	{
		e->flags |= TRAN_V | SIGN;
	}
	else if (keycode == 123)
	{
		e->flags |= TRAN_H | SIGN;
	}
	else if (keycode == 124)
	{
		e->flags |= TRAN_H;
	}
	else if (keycode == 24)
	{
		e->flags |= TRAN_Z;
	}
	else if (keycode == 27)
	{
		e->flags |= TRAN_Z | SIGN;
	}

	return (0);
}
