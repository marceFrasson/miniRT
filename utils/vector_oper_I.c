/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_oper_I.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marce <marce@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 00:02:01 by mfrasson          #+#    #+#             */
/*   Updated: 2021/06/13 12:05:21 by marce            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/miniRT.h"

t_tpl	create_vec(double x, double y, double z)
{
	t_tpl	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

t_tpl	sub_vec(t_tpl a, t_tpl b)
{
	t_tpl	temp;

	temp.x = a.x - b.x;
	temp.y = a.y - b.y;
	temp.z = a.z - b.z;
	return (temp);
}

t_tpl	sum_vec(t_tpl a, t_tpl b)
{
	t_tpl	temp;

	temp.x = a.x + b.x;
	temp.y = a.y + b.y;
	temp.z = a.z + b.z;
	return (temp);
}

t_tpl	div_vec(t_tpl a, float scale)
{
	t_tpl	temp;

	temp.x = a.x / scale;
	temp.y = a.y / scale;
	temp.z = a.z / scale;
	return (temp);
}

t_tpl	mult_vec(t_tpl a, float scale)
{
	t_tpl	temp;

	temp.x = a.x * scale;
	temp.y = a.y * scale;
	temp.z = a.z * scale;
	return (temp);
}
