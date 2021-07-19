/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elem_III.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marce <marce@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 00:03:07 by mfrasson          #+#    #+#             */
/*   Updated: 2021/06/13 12:05:21 by marce            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/miniRT.h"

int	check_obj_cy(t_cy *cylinder, int i)
{
	if (!(sqrt(dot_prod(cylinder->norm, cylinder->norm))))
		return (error_print_II(5, i));
	else
		norm_vec(&cylinder->norm);
	if (cylinder->diam < 0)
		return (error_print_II(2, i));
	if (cylinder->heig < 0)
		return (error_print_II(3, i));
	if (!(check_color(cylinder->color)))
		return (error_print_II(4, i));
	return (1);
}

int	check_obj_tr(t_tr *triangle, int i)
{
	if (!(sqrt(dot_prod(triangle->norm, triangle->norm))))
		return (error_print_II(7, i));
	else
		norm_vec(&triangle->norm);
	if (!(check_color(triangle->color)))
		return (error_print_II(4, i));
	return (1);
}

int	check_obj_sq(t_sq *square, int i)
{
	if (!(sqrt(dot_prod(square->norm, square->norm))))
		return (error_print_II(5, i));
	else
		norm_vec(&square->norm);
	if (square->side < 0)
		return (error_print_II(6, i));
	if (!(check_color(square->color)))
		return (error_print_II(4, i));
	return (1);
}

int	check_obj_sp(t_sp *sphere, int i)
{
	if (sphere->diam < 0)
		return (error_print_II(2, i));
	if (!(check_color(sphere->color)))
		return (error_print_II(4, i));
	return (1);
}

int	check_obj_pl(t_pl *plane, int i)
{
	if (!(sqrt(dot_prod(plane->norm, plane->norm))))
		return (error_print_II(5, i));
	else
		norm_vec(&plane->norm);
	if (!(check_color(plane->color)))
		return (error_print_II(4, i));
	return (1);
}
