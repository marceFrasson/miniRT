/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marce <marce@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 00:03:39 by mfrasson          #+#    #+#             */
/*   Updated: 2021/06/13 12:05:21 by marce            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/miniRT.h"

t_tpl	color_ambiente(t_ambl ambl)
{
	t_tpl	color;

	color_norm(&ambl.color, 1);
	color = mult_vec(ambl.color, ambl.forc);
	return (color);
}

t_tpl	color_difuse(t_ray *ray, t_ray light)
{
	t_tpl	color;
	double	t;

	t = dot_prod(ray->norm, light.dir) * light.forc;
	color = mult_vec(light.color, t);
	return (color);
}

t_tpl	color_especular(t_ray *ray, t_ray light)
{
	t_tpl	reflex;
	t_tpl	color;
	double	t;

	t = dot_prod(ray->norm, light.dir) * 2;
	reflex = sub_vec(mult_vec(ray->norm, t), light.dir);
	norm_vec(&reflex);
	t = -dot_prod(ray->dir, reflex);
	if (t < 0)
		return (create_vec(0, 0, 0));
	t = pow(t, C_ESPECULAR) * light.forc;
	color = mult_vec(light.color, t);
	return (color);
}
