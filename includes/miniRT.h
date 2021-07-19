/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marce <marce@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 00:01:35 by mfrasson          #+#    #+#             */
/*   Updated: 2021/06/13 18:54:16 by marce            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define _USE_MATH_DEFINES
# define EPSILON 0.00001
# define M_PI 3.14159265358979323846

# define SPHERE 1
# define PLANE 2
# define SQUARE 3
# define CYLINDER 4
# define TRIANGLE 5

# define C_ESPECULAR 100

# define LEFT_ARROW 65361
# define RIGHT_ARROW 65363
# define ESC_BUTTON 65307

# include <mlx.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdint.h>
# include "./../libft/libft.h"

typedef struct s_tpl
{
	double	x;
	double	y;
	double	z;

}			t_tpl;

typedef struct s_mat
{
	t_tpl	c1;
	t_tpl	c2;
	t_tpl	c3;

}			t_mat;

typedef struct s_ambl
{
	double	forc;
	t_tpl	color;
}			t_ambl;

typedef struct s_rt
{
	double	R[3];
	int		a;
	t_ambl	ambl;
	int		c;
	t_list	*cam;
	int		l;
	t_list	*lght;
	int		o;
	t_list	*objs;
}			t_rt;

typedef struct s_lght
{
	t_tpl	orig;
	double	forc;
	t_tpl	color;
}			t_lght;

typedef struct s_cam
{
	t_tpl	orig;
	t_tpl	dir;
	double	ang;
}			t_cam;

typedef struct s_pl
{
	int		type;
	t_tpl	orig;
	t_tpl	norm;
	t_tpl	color;
}			t_pl;

typedef struct s_sp
{
	int		type;
	t_tpl	orig;
	double	diam;
	t_tpl	color;
}			t_sp;

typedef struct s_sq
{
	int		type;
	t_tpl	orig;
	t_tpl	norm;
	double	side;
	t_tpl	color;
}			t_sq;

typedef struct s_cy
{
	int		type;
	t_tpl	orig;
	t_tpl	norm;
	double	diam;
	double	heig;
	t_tpl	color;
}			t_cy;

typedef struct s_tr
{
	int		type;
	t_tpl	p1;
	t_tpl	p2;
	t_tpl	p3;
	t_tpl	norm;
	t_tpl	color;
}			t_tr;

typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		bits_pixel;
	int		line_len;
	int		endian;
}				t_img;

typedef struct s_view
{
	t_mat	mat;
	t_cam	cam;
	t_tpl	init;
}			t_view;

typedef struct s_ray
{
	double	t;
	t_tpl	orig;
	t_tpl	dir;
	t_tpl	hit;
	t_tpl	norm;
	double	forc;
	t_tpl	color;
}			t_ray;

typedef struct s_hook
{
	void	*mlx;
	void	*wind;
	t_list	*imgs;
}			t_hook;

typedef struct s_bitmap
{
	uint16_t	type;
	uint32_t	size;
	uint16_t	reserved1;
	uint16_t	reserved2;
	uint32_t	offset;
	uint32_t	dib_header_size;
	int32_t		width_px;
	int32_t		height_px;
	uint16_t	num_planes;
	uint16_t	bits_per_pixel;
	uint32_t	compression;
	uint32_t	image_size_bytes;
	int32_t		x_resolution_ppm;
	int32_t		y_resolution_ppm;
	uint32_t	num_colors;
	uint32_t	important_colors;
}				t_bitmap;

t_tpl	create_vec(double x, double y, double z);
t_tpl	sub_vec(t_tpl a, t_tpl b);
t_tpl	sum_vec(t_tpl a, t_tpl b);
t_tpl	div_vec(t_tpl a, float scale);
t_tpl	mult_vec(t_tpl a, float scale);
void	norm_vec(t_tpl *vec);
double	dot_prod(t_tpl v1, t_tpl v2);
t_tpl	cross_vec(t_tpl v1, t_tpl v2);

t_tpl	color_mult(t_tpl v1, t_tpl v2);
void	color_norm(t_tpl *vec, int i);

t_tpl	mat_dot_prod(t_mat mat, t_tpl vec);
double	mat_det(t_mat mat);
t_mat	mat_invert(t_mat mat);

int		check_info(char *info);
int		get_double(double *val, char *info);
int		get_vec(double *x, double *y, double *z, char *info);
void	get_vecs(t_tr *trng, char **info);
int		check_rgb(double r, double g, double b);

int		get_res(char **info, t_rt *rt);
int		get_ambl(char **info, t_rt *rt);
int		get_cam(char **info, t_rt *rt);
int		get_lght(char **info, t_rt *rt);
int		get_pln(char **info, t_rt *rt);
int		get_sph(char **info, t_rt *rt);
int		get_sqr(char **info, t_rt *rt);
int		get_cyl(char **info, t_rt *rt);
int		get_trng(char **info, t_rt *rt);

int		make_rt(char *file, t_rt *rt);

int		check_obj_cy(t_cy *cylinder, int i);
int		check_obj_tr(t_tr *triangle, int i);
int		check_obj_sq(t_sq *square, int i);
int		check_obj_sp(t_sp *sphere, int i);
int		check_obj_pl(t_pl *plane, int i);
int		check_objs_I(t_rt *rt);
int		check_cam(t_rt *rt);
int		check_lght(t_rt *rt);
int		check_screan_ambl(t_rt *rt);

int		check_color(t_tpl vec);
int		error_print_II(int indicator, int i);
int		error_print_I(int indicator, int i);
int		check_rt(t_rt *rt);

void	cy_intersection_I( t_cy *cy, t_ray *ray);
void	tr_intersection_I( t_tr *tr, t_ray *ray);
void	sq_intersection_I(t_sq *sq, t_ray *ray);
void	sp_intersection_I( t_sp *sp, t_ray *ray);
void	pl_intersection_I(t_pl *pl, t_ray *ray);
void	set_intersection(t_list *objs, t_ray *ray);

t_img	*make_image(t_rt *rt, t_cam *cam, void *mlx);

t_tpl	color_ambiente(t_ambl ambl);
t_tpl	color_difuse(t_ray *ray, t_ray light);
t_tpl	color_especular(t_ray *ray, t_ray light);
t_tpl	raytracer(t_rt *rt, t_view view, int x, int y);

void	init_render(int argc, t_rt *rt);

int		windows_control(t_hook *loop, t_rt *rt);

void	bitmap_control(t_hook *loop, t_rt *rt);

void	free_rt(t_rt *rt);

#endif
