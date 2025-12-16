/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alien_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmustone <mmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 19:17:03 by mmustone          #+#    #+#             */
/*   Updated: 2025/12/12 19:17:07 by mmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_bonus.h"

static int	can_walk_horiz(t_map *m, int y, int x)
{
	int	left;
	int	right;

	left = (x - 1 >= 0 && m->grid[y][x - 1] != '1' && m->grid[y][x - 1] != 'E');
	right = (x + 1 < m->width && m->grid[y][x + 1] != '1' && m->grid[y][x
			+ 1] != 'E');
	return (left || right);
}

static int	can_walk_vert(t_map *m, int y, int x)
{
	int	up;
	int	down;

	up = (y - 1 >= 0 && m->grid[y - 1][x] != '1' && m->grid[y - 1][x] != 'E');
	down = (y + 1 < m->height && m->grid[y + 1][x] != '1' && m->grid[y
			+ 1][x] != 'E');
	return (up || down);
}

static t_pos	pick_dir(t_map *m, int y, int x)
{
	t_pos	d;

	d.x = 0;
	d.y = 0;
	if (can_walk_horiz(m, y, x))
		d.x = 1;
	else if (can_walk_vert(m, y, x))
		d.y = 1;
	return (d);
}

static void	alien_step(t_game *game, int ay, int ax, t_pos *d)
{
	t_map	*m;
	int		ny;
	int		nx;

	m = &game->map;
	ny = ay + d->y;
	nx = ax + d->x;
	if (!check_alien_move(m, ny, nx, d))
		return ;
	if (m->grid[ny][nx] == 'P' && game->end_game == 0)
	{
		game->end_game = 2;
		return ;
	}
	m->grid[ay][ax] = '0';
	m->grid[ny][nx] = 'A';
}

void	alien_update(t_game *game)
{
	static int		init;
	static t_pos	dir;
	int				ay;
	int				ax;

	if (!game || !game->map.grid)
		return ;
	if (find_player(&game->map, &ay, &ax, 'A') == -1)
		return ;
	if (!init)
	{
		dir = pick_dir(&game->map, ay, ax);
		init = 1;
	}
	if (dir.x == 0 && dir.y == 0)
		return ;
	alien_step(game, ay, ax, &dir);
	game->enemy.current_frame++;
	if (game->enemy.current_frame >= 2)
		game->enemy.current_frame = 0;
}
