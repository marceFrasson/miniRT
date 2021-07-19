/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obs_intersec_II.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marce <marce@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 00:03:27 by mfrasson          #+#    #+#             */
/*   Updated: 2021/06/13 12:05:21 by marce            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/miniRT.h"

static int	sq_intersection_II(t_sq *sq, t_ray *ray, double t)
{
	t_mat	mat;
	t_tpl	hit;
	t_tpl	vec;

	hit = sum_vec(ray->orig, mult_vec(ray->dir, t));
	hit = sub_vec(hit, sq->orig);
	if (sq->norm.y == 1 || sq->norm.y == -1)
		mat.c1 = create_vec(1, 0, 0);
	else
		mat.c1 = cross_vec(create_vec(0, 1, 0), sq->norm);
	norm_vec(&mat.c1);
	mat.c2 = cross_vec(sq->norm, mat.c1);
	mat.c3 = sq->norm;
	mat = mat_invert(mat);
	vec = mat_dot_prod(mat, hit);
	if (fabs(vec.x) <= (sq->side / 2) && fabs(vec.y) <= (sq->side / 2))
		return (1);
	return (0);
}

void	sq_intersection_I(t_sq *sq, t_ray *ray)
{
	t_tpl	v1;
	double	i[3];
	double	t;

	if (dot_prod(sq->norm, ray->dir))
	{
		if (dot_prod(sq->norm, ray->dir) > 0)
			sq->norm = mult_vec(sq->norm, -1);
		i[0] = dot_prod(sq->norm, ray->orig);
		i[1] = dot_prod(sq->norm, sq->orig);
		i[2] = dot_prod(sq->norm, ray->dir);
		t = (i[1] - i[0]) / i[2];
		if (t > 0 && t < ray->t && (sq_intersection_II(sq, ray, t)))
		{
			ray->t = t;
			ray->norm = sq->norm;
			v1 = mult_vec(ray->dir, ray->t);
			ray->hit = sum_vec(ray->orig, v1);
			v1 = mult_vec(ray->norm, EPSILON);
			ray->hit = sum_vec(ray->hit, v1);
			ray->color = sq->color;
		}
	}
}

static int	tr_intersection_III(t_tpl norm, t_tpl hit, t_tpl v1, t_tpl v2)
{
	t_tpl	left;
	t_tpl	right;
	t_tpl	cross;

	left = sub_vec(hit, v1);
	right = sub_vec(v2, v1);
	cross = cross_vec(left, right);
	if (dot_prod(norm, cross) > 0)
		return (1);
	return (0);
}

static int	tr_intersection_II( t_tr *tr, t_ray *ray, double t)
{
	t_tpl	hit;

	hit = sum_vec(ray->orig, mult_vec(ray->dir, t));
	if ((tr_intersection_III(tr->norm, hit, tr->p1, tr->p2)
			&& tr_intersection_III(tr->norm, hit, tr->p2, tr->p3)
			&& tr_intersection_III(tr->norm, hit, tr->p3, tr->p1))
		|| (tr_intersection_III(tr->norm, hit, tr->p1, tr->p3)
			&& tr_intersection_III(tr->norm, hit, tr->p3, tr->p2)
			&& tr_intersection_III(tr->norm, hit, tr->p2, tr->p1)))
		return (1);
	return (0);
}

void	tr_intersection_I( t_tr *tr, t_ray *ray)
{
	t_tpl	v1;
	double	i[3];
	double	t;

	if (dot_prod(tr->norm, ray->dir))
	{
		if (dot_prod(tr->norm, ray->dir) > 0)
			tr->norm = mult_vec(tr->norm, -1);
		i[0] = dot_prod(tr->norm, ray->orig);
		i[1] = dot_prod(tr->norm, tr->p1);
		i[2] = dot_prod(tr->norm, ray->dir);
		t = (i[1] - i[0]) / i[2];
		if (t > 0 && t < ray->t && (tr_intersection_II(tr, ray, t)))
		{
			ray->t = t;
			ray->norm = tr->norm;
			v1 = mult_vec(ray->dir, ray->t);
			ray->hit = sum_vec(ray->orig, v1);
			v1 = mult_vec(ray->norm, EPSILON);
			ray->hit = sum_vec(ray->hit, v1);
			ray->color = tr->color;
		}
	}
}
