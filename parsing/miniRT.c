/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marce <marce@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 00:04:52 by mfrasson          #+#    #+#             */
/*   Updated: 2021/06/13 12:04:45 by marce            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/miniRT.h"

void	free_rt(t_rt *rt)
{
	ft_lstclear(&rt->cam, free);
	ft_lstclear(&rt->lght, free);
	ft_lstclear(&rt->objs, free);
}

static void	set_rt(t_rt *rt)
{
	rt->R[2] = 0;
	rt->a = 0;
	rt->c = 0;
	rt->cam = NULL;
	rt->l = 0;
	rt->lght = NULL;
	rt->o = 0;
	rt->objs = NULL;
}

static int	check_args(int n, char **str)
{
	int	i;

	i = 0;
	if (n < 2 || n > 3)
		return (0);
	if (n == 3 && ft_strncmp(*(str + 2), "--save", ft_strlen(*(str + 2))))
		return (0);
	while (*(*(str + 1) + i) != '\0')
		i++;
	if (*(*(str + 1) + i - 1) == 't')
		if (*(*(str + 1) + i - 2) == 'r')
			if (*(*(str + 1) + i - 3) == '.')
				return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_rt	rt;

	set_rt(&rt);
	if (!(check_args(argc, argv)))
	{
		printf("Error\nArguments\n");
		return (-1);
	}
	if (!(make_rt(*(argv + 1), &rt)))
	{
		printf("Error\n.rt format\n");
		free_rt(&rt);
		return (-1);
	}
	if (!(check_rt(&rt)))
	{
		printf("Error\nElement value\n");
		free_rt(&rt);
		return (-1);
	}
	init_render(argc, &rt);
	return (0);
}
