/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_I.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marce <marce@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 00:04:19 by mfrasson          #+#    #+#             */
/*   Updated: 2021/06/13 12:04:50 by marce            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/miniRT.h"

static int	set_element(char **info, t_rt *rt)
{
	if (info[0][0] == '\0')
		return (1);
	else if (info[0][0] == 'R' && info[0][1] == '\0')
		get_res(info, rt);
	else if (info[0][0] == 'A' && info[0][1] == '\0')
		get_ambl(info, rt);
	else if (info[0][0] == 'c' && info[0][1] == '\0')
		get_cam(info, rt);
	else if (info[0][0] == 'l' && info[0][1] == '\0')
		get_lght(info, rt);
	else if (info[0][0] == 'p' && info[0][1] == 'l' && info[0][2] == '\0')
		get_pln(info, rt);
	else if (info[0][0] == 's' && info[0][1] == 'p' && info[0][2] == '\0')
		get_sph(info, rt);
	else if (info[0][0] == 's' && info[0][1] == 'q' && info[0][2] == '\0')
		get_sqr(info, rt);
	else if (info[0][0] == 'c' && info[0][1] == 'y' && info[0][2] == '\0')
		get_cyl(info, rt);
	else if (info[0][0] == 't' && info[0][1] == 'r' && info[0][2] == '\0')
		get_trng(info, rt);
	else
		return (0);
	return (1);
}

static int	check_line(char *line, t_rt *rt)
{
	char	**info;
	int		i;

	if (*line == '\0')
		return (1);
	info = ft_split(line, ' ');
	if (*info == NULL)
		return (0);
	i = set_element(info, rt);
	ft_free_split(info);
	return (i);
}

int	make_rt(char *file, t_rt *rt)
{
	char	*line;
	int		fd;
	int		i;

	i = 1;
	line = NULL;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (0);
	while (i == 1)
	{
		i = get_next_line(fd, &line);
		if (i == -1 || !(check_line(line, rt)))
		{
			free(line);
			close(fd);
			return (0);
		}
		free(line);
	}
	close(fd);
	return (1);
}
