/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_II.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marce <marce@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 18:48:37 by marce             #+#    #+#             */
/*   Updated: 2021/06/13 18:52:52 by marce            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/miniRT.h"

void	get_vecs(t_tr *trng, char **info)
{
	get_vec(&trng->p1.x, &trng->p1.y, &trng->p1.z, info[1]);
	get_vec(&trng->p2.x, &trng->p2.y, &trng->p2.z, info[2]);
	get_vec(&trng->p3.x, &trng->p3.y, &trng->p3.z, info[3]);
	get_vec(&trng->color.x, &trng->color.y, &trng->color.z, info[4]);
}
