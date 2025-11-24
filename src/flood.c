/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmustone <mmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 22:36:30 by martinmust        #+#    #+#             */
/*   Updated: 2025/11/24 11:40:21 by mmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void	flood_collect(t_flood *f, int y, int x)
{
	char	c;

	if (y < 0 || y >= f->map->height || x < 0 || x >= f->map->width)
		return ;
	c = f->grid[y][x];
	if (c == '1' || c == 'E' || c == 'V')
		return ;
	if (c == 'C')
		f->found_c++;
	f->grid[y][x] = 'V';
	flood_collect(f, y - 1, x);
	flood_collect(f, y + 1, x);
	flood_collect(f, y, x - 1);
	flood_collect(f, y, x + 1);
}

static void	flood_exit(t_flood *f, int y, int x)
{
	char	c;

	if (y < 0 || y >= f->map->height || x < 0 || x >= f->map->width)
		return ;
	c = f->grid[y][x];
	if (c == '1' || c == 'V')
		return ;
	if (c == 'E')
	{
		f->exit_ok = 1;
		return ;
	}
	f->grid[y][x] = 'V';
	flood_exit(f, y - 1, x);
	flood_exit(f, y + 1, x);
	flood_exit(f, y, x - 1);
	flood_exit(f, y, x + 1);
}

static int	run_collect(t_map *m, int sy, int sx)
{
	t_flood	f;

	f.map = m;
	f.grid = dup_grid(m);
	if (!f.grid)
		return (-1);
	f.found_c = 0;
	flood_collect(&f, sy, sx);
	free_grid_copy(f.grid, m->height);
	if (f.found_c != m->collectiable)
	{
		ft_printf("Error: collectibles unreachable\n");
		return (-1);
	}
	return (0);
}

static int	run_exit(t_map *m, int sy, int sx)
{
	t_flood	f;

	f.map = m;
	f.grid = dup_grid(m);
	if (!f.grid)
		return (-1);
	f.exit_ok = 0;
	flood_exit(&f, sy, sx);
	free_grid_copy(f.grid, m->height);
	if (!f.exit_ok)
	{
		ft_printf("Error: exit unreachable\n");
		return (-1);
	}
	return (0);
}

int	check_path(t_map *m)
{
	int	sy;
	int	sx;

	if (find_player(m, &sy, &sx) < 0)
		return (-1);
	if (run_collect(m, sy, sx) < 0)
		return (-1);
	if (run_exit(m, sy, sx) < 0)
		return (-1);
	return (0);
}
