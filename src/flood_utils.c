/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martinmust <martinmust@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 22:33:14 by martinmust        #+#    #+#             */
/*   Updated: 2025/11/23 22:42:37 by martinmust       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

char	**dup_grid(t_map *m)
{
	char	**cp;
	int		y;

	cp = malloc(sizeof(char *) * (m->height + 1));
	if (!cp)
		return (NULL);
	y = 0;
	while (y < m->height)
	{
		cp[y] = strdup(m->grid[y]);
		if (!cp[y])
		{
			while (--y >= 0)
				free(cp[y]);
			free(cp);
			return (NULL);
		}
		y++;
	}
	cp[y] = NULL;
	return (cp);
}

void	free_grid_copy(char **cp, int h)
{
	int	i;

	i = 0;
	while (i < h)
	{
		free(cp[i]);
		i++;
	}
	free(cp);
}
