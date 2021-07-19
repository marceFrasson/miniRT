/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elem_I.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marce <marce@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 00:02:51 by mfrasson          #+#    #+#             */
/*   Updated: 2021/06/13 12:05:21 by marce            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/miniRT.h"

int	check_color(t_tpl vec)
{
	if (vec.x < 0 || vec.x > 255)
		return (0);
	if (vec.y < 0 || vec.y > 255)
		return (0);
	if (vec.z < 0 || vec.z > 255)
		return (0);
	return (1);
}

int	error_print_II(int indicator, int i)
{
	printf("Error\n");
	if (indicator == 1)
		printf("There's nothing in the scene\n");
	if (indicator == 2)
		printf("Diameter of object %d\n", i);
	if (indicator == 3)
		printf("Height of object %d\n", i);
	if (indicator == 4)
		printf("Color of object %d\n", i);
	if (indicator == 5)
		printf("Normal of object %d\n", i);
	if (indicator == 6)
		printf("Side of object %d\n", i);
	if (indicator == 7)
		printf("Object %d is not a triangle\n", i);
	return (0);
}

int	error_print_I(int indicator, int i)
{
	printf("Error\n");
	if (indicator == 1)
		printf("No resolution\n");
	if (indicator == 2)
		printf("No light \n");
	if (indicator == 3)
		printf("Light force\n");
	if (indicator == 4)
		printf("Ambient light color\n");
	if (indicator == 5)
		printf("Force of light %d\n", i);
	if (indicator == 6)
		printf("Color of light %d\n", i);
	if (indicator == 7)
		printf("No camera\n");
	if (indicator == 8)
		printf("Field of vision of camera %d must be between 0 and 180\n", i);
	if (indicator == 9)
		printf("No direction of cam %d\n", i);
	return (0);
}

int	check_rt(t_rt *rt)
{
	if (!(check_screan_ambl(rt)))
		return (0);
	if (!(check_lght(rt)))
		return (0);
	if (!(check_cam(rt)))
		return (0);
	if (!(check_objs_I(rt)))
		return (0);
	return (1);
}
