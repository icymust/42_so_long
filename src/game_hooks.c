/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_hooks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmustone <mmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 18:15:25 by mmustone          #+#    #+#             */
/*   Updated: 2025/12/08 13:31:32 by mmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	compute_target(t_map *map, t_pos cur, char move, t_pos *tgt)
{
	if (!tgt || !map)
		return (0);
	*tgt = cur;
	if (move == 'r')
		tgt->x = cur.x + 1;
	else if (move == 'l')
		tgt->x = cur.x - 1;
	else if (move == 'u')
		tgt->y = cur.y - 1;
	else if (move == 'd')
		tgt->y = cur.y + 1;
	else
		return (0);
	return (1);
}

int	apply_move(t_game *game, t_pos cur, t_pos tgt)
{
	t_map	*map;
	char	cell;

	map = &game->map;
	cell = map->grid[tgt.y][tgt.x];
	if (cell == '1')
		return (0);
	if (cell == 'E')
	{
		if (map->collectiable == 0)
		{
			game->player.steps++;
			ft_printf("Moves:%i\n", game->player.steps);
			close_win(game);
		}
		return (0);
	}
	if (cell == 'C')
		map->collectiable--;
	map->grid[cur.y][cur.x] = '0';
	map->grid[tgt.y][tgt.x] = 'P';
	return (1);
}

int	move_in_grid(t_game *game, char move)
{
	t_map	*map;
	t_pos	cur;
	t_pos	tgt;
	int		ok;

	map = &game->map;
	find_player(map, &cur.y, &cur.x);
	ok = compute_target(map, cur, move, &tgt);
	if (!ok)
		return (0);
	return (apply_move(game, cur, tgt));
}

int	move_player(t_game *game, char c)
{
	int	moved;

	mlx_clear_window(game->vars.mlx, game->vars.win);
	moved = move_in_grid(game, c);
	if (moved)
	{
		if (c == 'r')
			game->player.pos_x += TILE_SIZE;
		else if (c == 'l')
			game->player.pos_x -= TILE_SIZE;
		else if (c == 'u')
			game->player.pos_y -= TILE_SIZE;
		else if (c == 'd')
			game->player.pos_y += TILE_SIZE;
		game->player.steps++;
		ft_printf("Moves:%i\n", game->player.steps);
	}
	render_map(game);
	return (0);
}

int	key_hook(int keycode, t_game *game)
{
	if (keycode == 53)
		close_win(game);
	else if (keycode == 2)
		move_player(game, 'r');
	else if (keycode == 0)
		move_player(game, 'l');
	else if (keycode == 13)
		move_player(game, 'u');
	else if (keycode == 1)
		move_player(game, 'd');
	return (0);
}
