/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_render_end.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmustone <mmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 12:32:41 by mmustone          #+#    #+#             */
/*   Updated: 2025/12/09 12:35:27 by mmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_bonus.h"

void	render_map_end(t_game *game)
{
	char	*str;

	if (!game || !game->vars.mlx || !game->vars.win)
		return ;
	str = ft_itoa(game->player.steps);
	if (!str)
		return ;
	mlx_clear_window(game->vars.mlx, game->vars.win);
	if (game->end_game == 1)
		mlx_string_put(game->vars.mlx, game->vars.win, game->vars.win_width / 2,
			game->vars.win_height / 2, 0xFFFFFF, "You escaped the spaceship");
	else
		mlx_string_put(game->vars.mlx, game->vars.win, game->vars.win_width / 2,
			game->vars.win_height / 2, 0xFFFFFF,
			"You lost, Alien reached you");
	mlx_string_put(game->vars.mlx, game->vars.win, game->vars.win_width / 2,
		game->vars.win_height / 2 + 10, 0xFFFFFF, "Moves");
	mlx_string_put(game->vars.mlx, game->vars.win, game->vars.win_width / 2
		+ 40, game->vars.win_height / 2 + 10, 0xFFFFFF, str);
	free(str);
}
