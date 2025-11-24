/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmustone <mmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 18:22:29 by mmustone          #+#    #+#             */
/*   Updated: 2025/11/24 16:12:15 by mmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_bonus.h"

void	null_images(t_game *g)
{
	g->player.img = NULL;
	g->player.imgl = NULL;
	g->player.imgu = NULL;
	g->img_wall = NULL;
	g->img_floor = NULL;
	g->img_exit = NULL;
	g->img_key = NULL;
	g->img_al = NULL;
}

void	destroy_images(t_game *g)
{
	if (!g || !g->vars.mlx)
		return ;
	if (g->player.img)
		mlx_destroy_image(g->vars.mlx, g->player.img);
	if (g->player.imgl)
		mlx_destroy_image(g->vars.mlx, g->player.imgl);
	if (g->player.imgu)
		mlx_destroy_image(g->vars.mlx, g->player.imgu);
	if (g->img_wall)
		mlx_destroy_image(g->vars.mlx, g->img_wall);
	if (g->img_floor)
		mlx_destroy_image(g->vars.mlx, g->img_floor);
	if (g->img_exit)
		mlx_destroy_image(g->vars.mlx, g->img_exit);
	if (g->img_key)
		mlx_destroy_image(g->vars.mlx, g->img_key);
	if (g->img_al)
		mlx_destroy_image(g->vars.mlx, g->img_al);
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
