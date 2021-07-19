/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obs_intersec_III.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marce <marce@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 00:03:33 by mfrasson          #+#    #+#             */
/*   Updated: 2021/06/13 12:05:21 by marce            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/miniRT.h"

static int	cy_intersection_IV(t_cy *cy, t_ray *ray, double t)
{
	t_tpl	hit;
	t_tpl	v1;
	t_tpl	v2;

	hit = sum_vec(ray->orig, mult_vec(ray->dir, t));
	v1 = sub_vec(hit, cy->orig);
	v2 = sum_vec(cy->orig, mult_vec(cy->norm, cy->heig));
	v2 = sub_vec(hit, v2);
	if (dot_prod(cy->norm, v1) >= 0 && dot_prod(cy->norm, v2) <= 0)
		return (1);
	return (0);
}

static void	cy_intersection_III( t_cy *cy, t_ray *ray, double *t)
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
		if (t[1] < t[0] && t[1] > 0 && cy_intersection_IV(cy, ray, t[1]))
			t[0] = t[1];
	}
	if (!(cy_intersection_IV(cy, ray, t[0])) || t[0] < 0 || delta < 0)
		t[0] = 0;
}

static void	cy_intersection_II( t_cy *cy, t_ray *ray, double *t)
{
	t_tpl	vecx;
	double	v[3];
	double	a;
	double	b;
	double	c;

	vecx = sub_vec(ray->orig, cy->orig);
	v[0] = dot_prod(ray->dir, ray->dir);
	v[1] = pow(dot_prod(ray->dir, cy->norm), 2);
	a = v[0] - v[1];
	v[0] = dot_prod(ray->dir, vecx);
	v[1] = dot_prod(ray->dir, cy->norm);
	v[2] = dot_prod(vecx, cy->norm);
	b = 2 * (v[0] - v[1] * v[2]);
	v[0] = dot_prod(vecx, vecx);
	v[1] = dot_prod(vecx, cy->norm);
	c = v[0] - pow(v[1], 2) - pow(cy->diam / 2, 2);
	t[0] = a;
	t[1] = b;
	t[2] = c;
}

void	cy_intersection_I( t_cy *cy, t_ray *ray)
{
	t_tpl	v1;
	double	t[3];
	double	m;

	cy_intersection_II(cy, ray, t);
	cy_intersection_III(cy, ray, t);
	if (t[0] > 0 && t[0] < ray->t)
	{
		ray->t = t[0];
		v1 = mult_vec(ray->dir, ray->t);
		ray->hit = sum_vec(ray->orig, v1);
		m = dot_prod(cy->norm, ray->hit) - dot_prod(cy->orig, cy->norm);
		v1 = sum_vec(cy->orig, mult_vec(cy->norm, m));
		ray->norm = sub_vec(ray->hit, v1);
		norm_vec(&ray->norm);
		if (dot_prod(ray->norm, ray->dir) > 0)
			ray->norm = mult_vec(ray->norm, -1);
		v1 = mult_vec(ray->norm, EPSILON);
		ray->hit = sum_vec(ray->hit, v1);
		ray->color = cy->color;
	}
}

void	set_intersection(t_list *objs, t_ray *ray)
{
	t_list	*lst;

	lst = objs;
	while (lst)
	{
		if (((t_pl *)lst->vol)->type == PLANE)
			pl_intersection_I(((t_pl *)lst->vol), ray);
		if (((t_sp *)lst->vol)->type == SPHERE)
			sp_intersection_I(((t_sp *)lst->vol), ray);
		if (((t_sq *)lst->vol)->type == SQUARE)
			sq_intersection_I(((t_sq *)lst->vol), ray);
		if (((t_tr *)lst->vol)->type == TRIANGLE)
			tr_intersection_I(((t_tr *)lst->vol), ray);
		if (((t_cy *)lst->vol)->type == CYLINDER)
			cy_intersection_I(((t_cy *)lst->vol), ray);
		lst = lst->next;
	}
}
