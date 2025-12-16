/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmustone <mmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 19:16:38 by mmustone          #+#    #+#             */
/*   Updated: 2025/12/12 19:16:43 by mmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	destroy_images(t_game *g)
{
	if (!g || !g->vars.mlx)
		return ;
	if (g->player.img)
		mlx_destroy_image(g->vars.mlx, g->player.img);
	if (g->img_wall)
		mlx_destroy_image(g->vars.mlx, g->img_wall);
	if (g->img_floor)
		mlx_destroy_image(g->vars.mlx, g->img_floor);
	if (g->img_exit)
		mlx_destroy_image(g->vars.mlx, g->img_exit);
	if (g->img_key)
		mlx_destroy_image(g->vars.mlx, g->img_key);
	g->player.img = NULL;
	g->img_wall = NULL;
	g->img_floor = NULL;
	g->img_exit = NULL;
	g->img_key = NULL;
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
