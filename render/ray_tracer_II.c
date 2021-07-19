/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracer_II.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marce <marce@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 00:03:45 by mfrasson          #+#    #+#             */
/*   Updated: 2021/06/13 16:18:44 by marce            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/miniRT.h"

static void	adapt_screen(void *ptr, t_rt *rt)
{
	int	x;
	int	y;

	mlx_get_screen_size(ptr, &x, &y);
	if (rt->R[0] > x)
		rt->R[0] = x;
	if (rt->R[1] > y)
		rt->R[1] = y;
}

void	init_render(int argc, t_rt *rt)
{
	t_hook	loop;
	t_list	*cam;
	t_img	*img;
	int		i;

	loop.mlx = mlx_init();
	loop.imgs = NULL;
	adapt_screen(loop.mlx, rt);
	cam = rt->cam;
	i = 1;
	printf("\n");
	while (cam)
	{
		printf("| 	    Rendering camera %d 	\t|\n", i);
		img = make_image(rt, (t_cam *)cam->vol, loop.mlx);
		ft_lstadd_back(&loop.imgs, ft_lstnew(img));
		cam = cam->next;
		i++;
	}
	printf("| 	    Rendering complete 	\t|\n\n");
	if (argc == 2)
		windows_control(&loop, rt);
	else
		bitmap_control(&loop, rt);
}
