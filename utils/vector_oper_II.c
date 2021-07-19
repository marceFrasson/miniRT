/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_oper_II.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marce <marce@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 00:02:22 by mfrasson          #+#    #+#             */
/*   Updated: 2021/06/13 12:05:21 by marce            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/miniRT.h"

void	norm_vec(t_tpl *vec)
{
	double	i;

	i = sqrt(dot_prod(*vec, *vec));
	if (i < 1 - EPSILON || i > 1 + EPSILON)
	{
		vec->x /= i;
		vec->y /= i;
		vec->z /= i;
	}
}

double	dot_prod(t_tpl v1, t_tpl v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_tpl	cross_vec(t_tpl v1, t_tpl v2)
{
	t_tpl	vec;

	vec.x = v1.y * v2.z - v1.z * v2.y;
	vec.y = v1.z * v2.x - v1.x * v2.z;
	vec.z = v1.x * v2.y - v1.y * v2.x;
	return (vec);
}

t_tpl	mat_dot_prod(t_mat mat, t_tpl vec)
{
	t_tpl	v1;

	v1.x = mat.c1.x * vec.x + mat.c2.x * vec.y + mat.c3.x * vec.z;
	v1.y = mat.c1.y * vec.x + mat.c2.y * vec.y + mat.c3.y * vec.z;
	v1.z = mat.c1.z * vec.x + mat.c2.z * vec.y + mat.c3.z * vec.z;
	return (v1);
}
