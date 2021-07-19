/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_III.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marce <marce@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 00:04:30 by mfrasson          #+#    #+#             */
/*   Updated: 2021/06/13 18:53:51 by marce            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/miniRT.h"

int	get_pln(char **info, t_rt *rt)
{
	t_pl	*pln;
	int		i;

	i = 0;
	while (info[i])
		i++;
	if (i != 4)
		return (0);
	pln = (t_pl *)malloc(sizeof(t_pl));
	if (pln == NULL)
		return (0);
	get_vec(&pln->orig.x, &pln->orig.y, &pln->orig.z, info[1]);
	get_vec(&pln->norm.x, &pln->norm.y, &pln->norm.z, info[2]);
	get_vec(&pln->color.x, &pln->color.y, &pln->color.z, info[3]);
	if (!(check_rgb(pln->color.x, pln->color.y, pln->color.z)))
		return (0);
	pln->type = PLANE;
	ft_lstadd_back(&rt->objs, ft_lstnew(pln));
	rt->o += 1;
	return (1);
}

int	get_sph(char **info, t_rt *rt)
{
	t_sp	*sph;
	int		i;

	i = 0;
	while (info[i])
		i++;
	if (i != 4)
		return (0);
	sph = (t_sp *)malloc(sizeof(t_sp));
	if (sph == NULL)
		return (0);
	get_vec(&sph->orig.x, &sph->orig.y, &sph->orig.z, info[1]);
	get_double(&sph->diam, info[2]);
	get_vec(&sph->color.x, &sph->color.y, &sph->color.z, info[3]);
	if (!(check_rgb(sph->color.x, sph->color.y, sph->color.z)))
		return (0);
	sph->type = SPHERE;
	ft_lstadd_back(&rt->objs, ft_lstnew(sph));
	rt->o += 1;
	return (1);
}

int	get_sqr(char **info, t_rt *rt)
{
	t_sq	*sqr;
	int		i;

	i = 0;
	while (info[i])
		i++;
	if (i != 5)
		return (0);
	sqr = (t_sq *)malloc(sizeof(t_sq));
	if (sqr == NULL)
		return (0);
	get_vec(&sqr->orig.x, &sqr->orig.y, &sqr->orig.z, info[1]);
	get_vec(&sqr->norm.x, &sqr->norm.y, &sqr->norm.z, info[2]);
	get_double(&sqr->side, info[3]);
	get_vec(&sqr->color.x, &sqr->color.y, &sqr->color.z, info[4]);
	if (!(check_rgb(sqr->color.x, sqr->color.y, sqr->color.z)))
		return (0);
	sqr->type = SQUARE;
	ft_lstadd_back(&rt->objs, ft_lstnew(sqr));
	rt->o += 1;
	return (1);
}

int	get_cyl(char **info, t_rt *rt)
{
	t_cy	*cyl;
	int		i;

	i = 0;
	while (info[i])
		i++;
	if (i != 6)
		return (0);
	cyl = (t_cy *)malloc(sizeof(t_cy));
	if (cyl == NULL)
		return (0);
	get_vec(&cyl->orig.x, &cyl->orig.y, &cyl->orig.z, info[1]);
	get_vec(&cyl->norm.x, &cyl->norm.y, &cyl->norm.z, info[2]);
	get_double(&cyl->diam, info[3]);
	get_double(&cyl->heig, info[4]);
	get_vec(&cyl->color.x, &cyl->color.y, &cyl->color.z, info[5]);
	if (!(check_rgb(cyl->color.x, cyl->color.y, cyl->color.z)))
		return (0);
	cyl->type = CYLINDER;
	ft_lstadd_back(&rt->objs, ft_lstnew(cyl));
	rt->o += 1;
	return (1);
}

int	get_trng(char **info, t_rt *rt)
{
	t_tr	*trng;
	int		i;
	t_tpl	v1;
	t_tpl	v2;

	i = 0;
	while (info[i])
		i++;
	if (i != 5)
		return (0);
	trng = (t_tr *)malloc(sizeof(t_tr));
	if (trng == NULL)
		return (0);
	get_vecs(trng, info);
	if (!(check_rgb(trng->color.x, trng->color.y, trng->color.z)))
		return (0);
	v1 = sub_vec(trng->p2, trng->p1);
	v2 = sub_vec(trng->p3, trng->p1);
	trng->norm = cross_vec(v1, v2);
	trng->type = TRIANGLE;
	ft_lstadd_back(&rt->objs, ft_lstnew(trng));
	rt->o += 1;
	return (1);
}
