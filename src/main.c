/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martinmust <martinmust@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 13:24:35 by mmustone          #+#    #+#             */
/*   Updated: 2025/11/23 18:44:16 by martinmust       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"



int main(int ac, char **av)
{
    t_game game;

    if (ac < 2 || ac > 2) {
        printf("Usage: %s <map_file>\n", av[0]);
        return (1);
    }

    ft_memset(&game, 0, sizeof(t_game));

    if (!map_load(&game.map, av[1])) {
        printf("Failed in map_load\n");
        return (1);
    }

    game.vars.win_height = game.map.height * TILE_SIZE;
    game.vars.win_width = game.map.width * TILE_SIZE;

    printf("Map loaded: %d x %d\n", game.map.width, game.map.height);

    game.vars.mlx = mlx_init();
    if (!game.vars.mlx) {
        free_map(&game.map);
        printf("Error: Failed to initialize MiniLibX\n");
        return (1);
    }

    if (!init_textures(&game))
    {
        close_win(&game);
        return (1);
    }

    game.vars.win = mlx_new_window(game.vars.mlx,
                                   game.vars.win_width,
                                   game.vars.win_height,
                                   "Escape spaceship");
    if (!game.vars.win)
    {
        close_win(&game);
        return (1);
    }

    int py, px;
    find_player(&game.map, &py, &px);
    game.player.pos_x = px * TILE_SIZE;
    game.player.pos_y = py * TILE_SIZE;

    render_map(&game);

    mlx_hook(game.vars.win, 2, 0, key_hook, &game);
    mlx_hook(game.vars.win, 17, 0, close_win, &game);

    mlx_loop(game.vars.mlx);
    return (0);
}
