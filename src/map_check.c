/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmustone <mmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 18:17:14 by mmustone          #+#    #+#             */
/*   Updated: 2025/12/16 16:43:27 by mmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	check_border(t_map *m)
{
	int	i;

	i = 0;
	while (i < m->width)
	{
		if (m->grid[0][i] != '1' || m->grid[m->height - 1][i] != '1')
			return (-1);
		i++;
	}
	i = 0;
	while (i < m->height)
	{
		if (m->grid[i][0] != '1' || m->grid[i][m->width - 1] != '1')
			return (-1);
		i++;
	}
	return (0);
}

int	count_elems(t_map *m)
{
	int		y;
	int		x;
	char	c;

	m->spawn = 0;
	m->exit = 0;
	m->collectiable = 0;
	y = -1;
	while (++y < m->height)
	{
		x = -1;
		while (++x < m->width)
		{
			c = m->grid[y][x];
			if (c == 'P')
				m->spawn++;
			else if (c == 'E')
				m->exit++;
			else if (c == 'C')
				m->collectiable++;
			else if (c != '0' && c != '1')
				return (-1);
		}
	}
	return (0);
}

int	grid_check(t_map *m)
{
	if (check_border(m) < 0)
		return (-1);
	if (count_elems(m) < 0)
		return (-1);
	if (m->spawn != 1 || m->exit != 1 || m->collectiable < 1)
		return (-1);
	return (0);
}

int	find_player(t_map *m, int *sy, int *sx)
{
	t_pos	pos;

	pos.y = 0;
	while (pos.y < m->height)
	{
		pos.x = 0;
		while (pos.x < m->width)
		{
			if (m->grid[pos.y][pos.x] == 'P')
			{
				*sy = pos.y;
				*sx = pos.x;
				return (0);
			}
			pos.x++;
		}
		pos.y++;
	}
	return (-1);
}
