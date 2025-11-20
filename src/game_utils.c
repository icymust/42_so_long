/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmustone <mmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 18:22:29 by mmustone          #+#    #+#             */
/*   Updated: 2025/11/20 18:36:52 by mmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int close_win(t_game *game) {
    printf("Close window\n");
    if (game->player.img)
        mlx_destroy_image(game->vars.mlx, game->player.img);
    if (game->vars.win)
        mlx_destroy_window(game->vars.mlx, game->vars.win);
    free_map(&game->map);
    exit(0);
    return (0);
}
