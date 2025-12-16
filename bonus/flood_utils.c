/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmustone <mmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 19:17:13 by mmustone          #+#    #+#             */
/*   Updated: 2025/12/12 19:17:14 by mmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_bonus.h"

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
		cp[y] = ft_strdup(m->grid[y]);
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
