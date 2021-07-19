/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_II.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marce <marce@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 00:04:25 by mfrasson          #+#    #+#             */
/*   Updated: 2021/06/13 12:05:21 by marce            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/miniRT.h"

int	get_res(char **info, t_rt *rt)
{
	int		i;

	i = 0;
	while (info[i] != NULL)
		i++;
	if (i != 3 || rt->R[2] == 1)
		return (0);
	get_double(&rt->R[0], info[1]);
	get_double(&rt->R[1], info[2]);
	rt->R[2] = 1;
	return (1);
}

int	get_ambl(char **info, t_rt *rt)
{
	int		i;

	i = 0;
	while (info[i])
		i++;
	if (i != 3 || rt->a == 1)
		return (0);
	get_double(&rt->ambl.forc, info[1]);
	if (rt->ambl.forc < 0 || rt->ambl.forc > 1)
		return (0);
	get_vec(&rt->ambl.color.x, &rt->ambl.color.y, &rt->ambl.color.z, info[2]);
	if (!(check_rgb(rt->ambl.color.x, rt->ambl.color.y, rt->ambl.color.z)))
		return (0);
	rt->a = 1;
	return (1);
}

int	get_cam(char **info, t_rt *rt)
{
	t_cam	*cam;
	int		i;

	i = 0;
	while (info[i])
		i++;
	if (i != 4)
		return (0);
	cam = (t_cam *)malloc(sizeof(t_cam));
	if (cam == NULL)
		return (0);
	rt->c += 1;
	get_vec(&cam->orig.x, &cam->orig.y, &cam->orig.z, info[1]);
	get_vec(&cam->dir.x, &cam->dir.y, &cam->dir.z, info[2]);
	get_double(&cam->ang, info[3]);
	if (cam->ang < 0 || cam->ang > 180)
		return (0);
	ft_lstadd_back(&rt->cam, ft_lstnew(cam));
	rt->c += 1;
	return (1);
}

int	get_lght(char **info, t_rt *rt)
{
	t_lght	*lght;
	int		i;

	i = 0;
	while (info[i])
		i++;
	if (i != 4)
		return (0);
	lght = (t_lght *)malloc(sizeof(t_lght));
	if (lght == NULL)
		return (0);
	get_vec(&lght->orig.x, &lght->orig.y, &lght->orig.z, info[1]);
	get_double(&lght->forc, info[2]);
	if (lght->forc < 0 || lght->forc > 1)
		return (0);
	get_vec(&lght->color.x, &lght->color.y, &lght->color.z, info[3]);
	if (!(check_rgb(lght->color.x, lght->color.y, lght->color.z)))
		return (0);
	ft_lstadd_back(&rt->lght, ft_lstnew(lght));
	rt->l += 1;
	return (1);
}
