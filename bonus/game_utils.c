/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmustone <mmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 18:22:29 by mmustone          #+#    #+#             */
/*   Updated: 2025/12/09 14:51:31 by mmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_bonus.h"

void	null_images(t_game *g)
{
	g->player.img[0] = NULL;
	g->player.img[1] = NULL;
	g->player.imgl[0] = NULL;
	g->player.imgl[1] = NULL;
	g->player.imgu = NULL;
	g->img_wall = NULL;
	g->img_floor = NULL;
	g->img_exit = NULL;
	g->img_key[0] = NULL;
	g->img_key[1] = NULL;
	g->enemy.frames[0] = NULL;
	g->enemy.frames[1] = NULL;
}

void	destroy_images(t_game *g)
{
	if (!g || !g->vars.mlx)
		return ;
	mlx_destroy_image(g->vars.mlx, g->player.img[0]);
	mlx_destroy_image(g->vars.mlx, g->player.img[1]);
	mlx_destroy_image(g->vars.mlx, g->player.imgl[0]);
	mlx_destroy_image(g->vars.mlx, g->player.imgl[1]);
	mlx_destroy_image(g->vars.mlx, g->player.imgu);
	mlx_destroy_image(g->vars.mlx, g->img_wall);
	mlx_destroy_image(g->vars.mlx, g->img_floor);
	mlx_destroy_image(g->vars.mlx, g->img_exit);
	mlx_destroy_image(g->vars.mlx, g->img_key[0]);
	mlx_destroy_image(g->vars.mlx, g->img_key[1]);
	mlx_destroy_image(g->vars.mlx, g->enemy.frames[0]);
	mlx_destroy_image(g->vars.mlx, g->enemy.frames[1]);
	null_images(g);
}

int	close_win(t_game *game)
{
	if (!game)
		exit(0);
	destroy_images(game);
	if (game->vars.mlx && game->vars.win)
	{
		mlx_destroy_window(game->vars.mlx, game->vars.win);
		game->vars.win = NULL;
	}
	free_map(&game->map);
	exit(0);
	return (0);
}

static long	now_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000L);
}

int	loop_tick(void *param)
{
	t_game		*game;
	static long	last = 0;
	long		t;
	const long	delay_ms = 450;

	game = (t_game *)param;
	if (!game || !game->vars.mlx)
		return (0);
	t = now_ms();
	if (last == 0)
		last = t;
	if (t - last >= delay_ms)
	{
		alien_update(game);
		if (game->end_game == 0)
			render_map(game);
		else
			render_map_end(game);
		last = t;
	}
	return (0);
}
