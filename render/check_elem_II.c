/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elem_II.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marce <marce@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 00:03:00 by mfrasson          #+#    #+#             */
/*   Updated: 2021/06/13 12:05:21 by marce            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/miniRT.h"

static int	check_objs_II(t_list *lst, int i)
{
	while (lst)
	{
		if (((t_pl *)lst->vol)->type == PLANE)
			if (!(check_obj_pl((t_pl *)lst->vol, i)))
				return (0);
		if (((t_sp *)lst->vol)->type == SPHERE)
			if (!(check_obj_sp((t_sp *)lst->vol, i)))
				return (0);
		if (((t_sq *)lst->vol)->type == SQUARE)
			if (!(check_obj_sq((t_sq *)lst->vol, i)))
				return (0);
		if (((t_tr *)lst->vol)->type == TRIANGLE)
			if (!(check_obj_tr((t_tr *)lst->vol, i)))
				return (0);
		if (((t_cy *)lst->vol)->type == CYLINDER)
			if (!(check_obj_cy((t_cy *)lst->vol, i)))
				return (0);
		lst = lst->next;
		i++;
	}
	return (1);
}

int	check_objs_I(t_rt *rt)
{
	t_list	*lst;
	int		i;

	if (!(rt->o))
		return (error_print_I(1, 0));
	i = 1;
	lst = rt->objs;
	return (check_objs_II(lst, i));
}

int	check_cam(t_rt *rt)
{
	t_list	*lst;
	t_cam	*cam;
	int		i;

	if (!(rt->c))
		return (error_print_I(7, 0));
	i = 1;
	lst = rt->cam;
	while (lst)
	{
		cam = (t_cam *)lst->vol;
		if (cam->ang < 0 || cam->ang > 180)
			return (error_print_I(8, i));
		if (!(sqrt(dot_prod(cam->dir, cam->dir))))
			return (error_print_I(9, i));
		else
			norm_vec(&cam->dir);
		lst = lst->next;
		i++;
	}
	return (1);
}

int	check_lght(t_rt *rt)
{
	t_list	*lst;
	t_lght	*lght;
	int		i;

	if (rt->l)
	{
		lst = rt->lght;
		i = 1;
		while (lst)
		{
			lght = (t_lght *)lst->vol;
			if (lght->forc < 0 || lght->forc > 1)
				return (error_print_I(5, i));
			if (!(check_color(lght->color)))
				return (error_print_I(6, i));
			lst = lst->next;
			i++;
		}
	}
	else
		printf("There's no light\n");
	return (1);
}

int	check_screan_ambl(t_rt *rt)
{
	if (!(rt->R[2]))
		return (error_print_I(1, 0));
	if (!(rt->a))
		return (error_print_I(2, 0));
	if (rt->ambl.forc < 0 || rt->ambl.forc > 1)
		return (error_print_I(3, 0));
	if (!(check_color(rt->ambl.color)))
		return (error_print_I(4, 0));
	return (1);
}
