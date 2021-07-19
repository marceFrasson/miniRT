/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_oper_III.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marce <marce@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 00:02:29 by mfrasson          #+#    #+#             */
/*   Updated: 2021/06/13 12:05:21 by marce            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/miniRT.h"

t_tpl	color_mult(t_tpl v1, t_tpl v2)
{
	return (create_vec(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z));
}

void	color_norm(t_tpl *vec, int i)
{
	if (i)
		*vec = div_vec(*vec, 255);
	else
		*vec = mult_vec(*vec, 255);
	if (vec->x > 255)
		vec->x = 255;
	else if (vec->x < 0)
		vec->x = 0;
	if (vec->y > 255)
		vec->y = 255;
	else if (vec->y < 0)
		vec->y = 0;
	if (vec->z > 255)
		vec->z = 255;
	else if (vec->z < 0)
		vec->z = 0;
}

double	mat_det(t_mat mat)
{
	double	t[4];

	t[0] = mat.c1.x * mat.c2.y * mat.c3.z;
	t[1] = mat.c2.x * mat.c3.y * mat.c1.z;
	t[2] = mat.c3.x * mat.c1.y * mat.c2.z;
	t[3] = t[0] + t[1] + t[2];
	t[0] = mat.c2.x * mat.c1.y * mat.c3.z;
	t[1] = mat.c1.x * mat.c3.y * mat.c2.z;
	t[2] = mat.c3.x * mat.c2.y * mat.c1.z;
	t[3] = t[3] - t[0] - t[1] - t[2];
	return (t[3]);
}

t_mat	mat_invert(t_mat mat)
{
	t_mat	m1;
	double	t[4];

	t[3] = mat_det(mat);
	t[0] = (mat.c2.y * mat.c3.z - mat.c3.y * mat.c2.z) / t[3];
	t[1] = -(mat.c1.y * mat.c3.z - mat.c3.y * mat.c1.z) / t[3];
	t[2] = (mat.c1.y * mat.c2.z - mat.c2.y * mat.c1.z) / t[3];
	m1.c1 = create_vec(t[0], t[1], t[2]);
	t[0] = -(mat.c2.x * mat.c3.z - mat.c3.x * mat.c2.z) / t[3];
	t[1] = (mat.c1.x * mat.c3.z - mat.c3.x * mat.c1.z) / t[3];
	t[2] = -(mat.c1.x * mat.c2.z - mat.c2.x * mat.c1.z) / t[3];
	m1.c2 = create_vec(t[0], t[1], t[2]);
	t[0] = (mat.c2.x * mat.c3.y - mat.c3.x * mat.c2.y) / t[3];
	t[1] = -(mat.c1.x * mat.c3.y - mat.c3.x * mat.c1.y) / t[3];
	t[2] = (mat.c1.x * mat.c2.y - mat.c2.x * mat.c1.y) / t[3];
	m1.c3 = create_vec(t[0], t[1], t[2]);
	return (m1);
}
