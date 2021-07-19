/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracer_III.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marce <marce@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 00:03:13 by mfrasson          #+#    #+#             */
/*   Updated: 2021/06/13 12:05:21 by marce            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/miniRT.h"

static void	image_pixel_put(t_img *img, int x, int y, t_tpl color)
{
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
	char			*pixel;

	red = (unsigned char)color.x;
	green = (unsigned char)color.y;
	blue = (unsigned char)color.z;
	pixel = img->addr + y * img->line_len + x * (img->bits_pixel / 8);
	*(unsigned int *)pixel = (red << 16 | green << 8 | blue);
}

static void	image_create(t_img *img, void *mlx, int width, int height)
{
	int	bp;
	int	ll;
	int	ed;

	img->ptr = mlx_new_image(mlx, width, height);
	img->addr = mlx_get_data_addr(img->ptr, &bp, &ll, &ed);
	img->bits_pixel = bp;
	img->line_len = ll;
	img->endian = ed;
}

static void	image_view(double *R, t_cam *cam, t_view *view)
{
	t_mat	mat;
	double	c_width;
	double	c_height;

	c_width = 2 * tan((cam->ang * M_PI) / (180 * 2));
	c_height = c_width * R[1] / R[0];
	if (cam->dir.y == 1 || cam->dir.y == -1)
		mat.c1 = create_vec(1, 0, 0);
	else
		mat.c1 = cross_vec(cam->dir, create_vec(0, 1, 0));
	norm_vec(&mat.c1);
	mat.c2 = cross_vec(mat.c1, cam->dir);
	mat.c3 = cam->dir;
	mat.c1 = mult_vec(mat.c1, c_width);
	mat.c2 = mult_vec(mat.c2, c_height);
	view->init = sub_vec(cam->orig, div_vec(mat.c1, 2));
	view->init = sum_vec(view->init, div_vec(mat.c2, 2));
	view->init = sum_vec(view->init, mat.c3);
	view->mat = mat;
	view->cam = *cam;
}

t_img	*make_image(t_rt *rt, t_cam *cam, void *mlx)
{
	t_view	view;
	t_img	*img;
	t_tpl	color;
	int		x;
	int		y;

	img = (t_img *)malloc(sizeof(t_img));
	if (!(img))
		return (img);
	image_view(rt->R, cam, &view);
	image_create(img, mlx, rt->R[0], rt->R[1]);
	y = 0;
	while (y < rt->R[1])
	{
		x = 0;
		while (x < rt->R[0])
		{
			color = raytracer(rt, view, x, y);
			image_pixel_put(img, x, y, color);
			x++;
		}
		y++;
	}
	return (img);
}
