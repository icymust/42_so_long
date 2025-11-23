/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martinmust <martinmust@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 18:22:29 by mmustone          #+#    #+#             */
/*   Updated: 2025/11/23 17:42:49 by martinmust       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int close_win(t_game *game) {
    if (!game)
        exit(0);
    if (game->vars.mlx)
    {
        if (game->player.img)
        {
            mlx_destroy_image(game->vars.mlx, game->player.img);
            game->player.img = NULL;
        }
        if (game->img_wall) { mlx_destroy_image(game->vars.mlx, game->img_wall); game->img_wall = NULL; }
        if (game->img_floor) { mlx_destroy_image(game->vars.mlx, game->img_floor); game->img_floor = NULL; }
        if (game->img_exit) { mlx_destroy_image(game->vars.mlx, game->img_exit); game->img_exit = NULL; }
        if (game->img_key) { mlx_destroy_image(game->vars.mlx, game->img_key); game->img_key = NULL; }
    }
    if (game->vars.mlx && game->vars.win)
    {
        mlx_destroy_window(game->vars.mlx, game->vars.win);
        game->vars.win = NULL;
    }
    printf("Close win\n");
    free_map(&game->map);
    exit(0);
    return (0);
}
