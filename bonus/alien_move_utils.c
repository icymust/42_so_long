/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alien_move_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmustone <mmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:14:00 by mmustone          #+#    #+#             */
/*   Updated: 2025/12/09 15:28:43 by mmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_bonus.h"

int	check_alien_move(t_map *m, int ny, int nx, t_pos *d)
{
	char	c;

	if (ny < 0 || ny >= m->height || nx < 0 || nx >= m->width)
	{
		d->x = -d->x;
		d->y = -d->y;
		return (0);
	}
	c = m->grid[ny][nx];
	if (c == '1' || c == 'E' || c == 'C')
	{
		d->x = -d->x;
		d->y = -d->y;
		return (0);
	}
	return (1);
}
