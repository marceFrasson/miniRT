/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 23:16:41 by mfrasson          #+#    #+#             */
/*   Updated: 2021/06/09 14:00:59 by mfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*dst;
	int		i;

	i = 0;
	dst = malloc(ft_strlen(str) + 1);
	if (!dst)
		return (NULL);
	while (str[i] != '\0')
	{
		dst[i] = str[i];
		i++;
	}
	dst[i] = '\0';
	return ((char *)dst);
}
