/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marce <marce@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 00:04:10 by mfrasson          #+#    #+#             */
/*   Updated: 2021/06/13 12:05:21 by marce            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/miniRT.h"

int	check_info(char *info)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (info[i] != '\0')
	{
		if (info[i] == ',')
			j++;
		i++;
	}
	return (j);
}

int	get_double(double *val, char *info)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (info[0] == '-')
		i++;
	while (ft_isdigit(info[i]) || info[i] == '.')
	{
		if (info[i] == '.')
			j++;
		i++;
	}
	if (j > 1 || i != ft_strlen(info))
		return (0);
	*val = ft_atod(info);
	return (1);
}

int	get_xyz_values(double *x, double *y, double *z, char **numb)
{
	if (!(get_double(x, numb[0])))
		return (0);
	if (!(get_double(y, numb[1])))
		return (0);
	if (!(get_double(z, numb[2])))
		return (0);
	return (1);
}

int	get_vec(double *x, double *y, double *z, char *info)
{
	char	**numb;
	int		i;
	int		j;

	i = 0;
	j = check_info(info);
	if (j != 2)
		return (0);
	numb = ft_split(info, ',');
	while (numb[i] != NULL)
		i++;
	if (i != 3)
	{
		ft_free_split(numb);
		return (0);
	}
	if (!(get_xyz_values(x, y, z, numb)))
	{
		ft_free_split(numb);
		return (0);
	}
	ft_free_split(numb);
	return (1);
}

int	check_rgb(double r, double g, double b)
{
	if ((r < 0 || g < 0 || b < 0) || (r > 255 || g > 255 || b > 255))
		return (0);
	return (1);
}
