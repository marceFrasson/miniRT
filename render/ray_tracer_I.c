/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracer_I.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marce <marce@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 00:03:51 by mfrasson          #+#    #+#             */
/*   Updated: 2021/06/13 12:05:21 by marce            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/miniRT.h"

static t_tpl	pixel_dir(t_rt *rt, t_view view, int x, int y)
{
	t_tpl	dir;
	t_tpl	v_right;
	t_tpl	v_down;
	double	x1;
	double	y1;

	x1 = (double)(x + 0.5) / rt->R[0];
	y1 = (double)(y + 0.5) / rt->R[1];
	v_right = mult_vec(view.mat.c1, x1);
	v_down = mult_vec(view.mat.c2, -y1);
	dir = sum_vec(v_right, v_down);
	dir = sum_vec(view.init, dir);
	dir = sub_vec(dir, view.cam.orig);
	norm_vec(&dir);
	return (dir);
}

static t_ray	set_ray_primary(t_rt *rt, t_view view, int x, int y)
{
	t_ray	ray;

	ray.dir = pixel_dir(rt, view, x, y);
	ray.orig = view.cam.orig;
	ray.t = INFINITY;
	return (ray);
}

static t_ray	set_ray_secondary(t_ray *ray, t_lght lght)
{
	t_ray	light;

	light.dir = sub_vec(lght.orig, ray->hit);
	light.orig = ray->hit;
	light.t = sqrt(dot_prod(light.dir, light.dir));
	norm_vec(&light.dir);
	light.forc = lght.forc;
	light.color = lght.color;
	color_norm(&light.color, 1);
	return (light);
}

static void	color_shadow(t_ray *ray, t_lght *lght, t_list *objs, t_tpl *color)
{
	t_ray	light;
	double	t;

	light = set_ray_secondary(ray, *lght);
	t = light.t;
	set_intersection(objs, &light);
	if (light.t == t)
	{
		*color = sum_vec(*color, color_difuse(ray, light));
		*color = sum_vec(*color, color_especular(ray, light));
	}
}

t_tpl	raytracer(t_rt *rt, t_view view, int x, int y)
{
	t_list	*lst;
	t_ray	ray;
	t_tpl	color;

	color = create_vec(0, 0, 0);
	ray = set_ray_primary(rt, view, x, y);
	set_intersection(rt->objs, &ray);
	if (ray.t != INFINITY)
	{
		color = sum_vec(color, color_ambiente(rt->ambl));
		lst = rt->lght;
		while (lst)
		{
			color_shadow(&ray, (t_lght *)lst->vol, rt->objs, &color);
			lst = lst->next;
		}
		color_norm(&ray.color, 1);
		color = color_mult(ray.color, color);
		color_norm(&color, 0);
	}
	return (color);
}
