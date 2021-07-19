/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obs_intersec_I.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marce <marce@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 00:03:20 by mfrasson          #+#    #+#             */
/*   Updated: 2021/06/13 12:05:21 by marce            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/miniRT.h"

void	pl_intersection_I(t_pl *pl, t_ray *ray)
{
	t_tpl	v1;
	double	i[3];
	double	t;

	if (dot_prod(pl->norm, ray->dir))
	{
		if (dot_prod(pl->norm, ray->dir) > 0)
			pl->norm = mult_vec(pl->norm, -1);
		i[0] = dot_prod(pl->norm, ray->orig);
		i[1] = dot_prod(pl->norm, pl->orig);
		i[2] = dot_prod(pl->norm, ray->dir);
		t = (i[1] - i[0]) / i[2];
		if (t > 0 && t < ray->t)
		{
			ray->t = t;
			ray->norm = pl->norm;
			v1 = mult_vec(ray->dir, ray->t);
			ray->hit = sum_vec(ray->orig, v1);
			v1 = mult_vec(ray->norm, EPSILON);
			ray->hit = sum_vec(ray->hit, v1);
			ray->color = pl->color;
		}
	}
}

static void	sp_intersection_III(double *t)
{
	double	delta;
	double	a;
	double	b;
	double	c;

	a = t[0];
	b = t[1];
	c = t[2];
	delta = pow(b, 2) - 4 * a * c;
	if (delta == 0)
	{
		if ((-b) / (2 * a) > 0)
			t[0] = (-b) / (2 * a);
	}
	else if (delta > 0)
	{
		t[0] = (-b + sqrt(delta)) / (2 * a);
		t[1] = (-b - sqrt(delta)) / (2 * a);
		if (t[1] < t[0] && t[1] > 0)
			t[0] = t[1];
	}
	if (t[0] < 0 || delta < 0)
		t[0] = 0;
}

static void	sp_intersection_II( t_sp *sp, t_ray *ray, double *t)
{
	t_tpl	vec[2];
	double	a;
	double	b;
	double	c;

	a = dot_prod(ray->dir, ray->dir);
	vec[0] = mult_vec(ray->dir, 2);
	vec[1] = sub_vec(ray->orig, sp->orig);
	b = dot_prod(vec[0], vec[1]);
	vec[0] = sub_vec(ray->orig, sp->orig);
	vec[1] = sub_vec(ray->orig, sp->orig);
	c = dot_prod(vec[0], vec[1]) - pow((sp->diam) / 2, 2);
	t[0] = a;
	t[1] = b;
	t[2] = c;
}

void	sp_intersection_I( t_sp *sp, t_ray *ray)
{
	t_tpl	v1;
	double	t[3];

	sp_intersection_II(sp, ray, t);
	sp_intersection_III(t);
	if (t[0] > 0 && t[0] < ray->t)
	{
		ray->t = t[0];
		v1 = mult_vec(ray->dir, ray->t);
		ray->hit = sum_vec(ray->orig, v1);
		ray->norm = sub_vec(ray->hit, sp->orig);
		norm_vec(&ray->norm);
		if (dot_prod(ray->norm, ray->dir) > 0)
			ray->norm = mult_vec(ray->norm, -1);
		v1 = mult_vec(ray->norm, EPSILON);
		ray->hit = sum_vec(ray->hit, v1);
		ray->color = sp->color;
	}
}
