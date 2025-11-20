/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmustone <mmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 13:24:35 by mmustone          #+#    #+#             */
/*   Updated: 2025/11/20 18:42:39 by mmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"



int main(int ac, char **av)
{
    t_game game;
    char *path = "./textures/player.png";
    int img_width = 64;
    int img_height = 64;

    if (ac < 2) {
        printf("Usage: %s <map_file>\n", av[0]);
        return (1);
    }

    // обнуляем всю структуру игры, чтобы все указатели были NULL
    ft_memset(&game, 0, sizeof(t_game));

    if (!map_load(&game.map, av[1])) {
        printf("Failed in map_load\n");
        return (1);
    }

    printf("Map loaded: %d x %d\n", game.map.width, game.map.height);

    // -- MLX --

    game.vars.mlx = mlx_init();
    if (!game.vars.mlx) {
        free_map(&game.map);
        printf("Error: Failed to initialize MiniLibX\n");
        return (1);
    }

    game.player.img = mlx_png_file_to_image(game.vars.mlx,
                                            path,
                                            &img_width,
                                            &img_height);
    if (!game.player.img) {
        free_map(&game.map);
        printf("Error: Failed to load image '%s'\n", path);
        return (1);
    }

    game.vars.win = mlx_new_window(game.vars.mlx, 500, 500, "Escape from aliens");
    mlx_put_image_to_window(game.vars.mlx, game.vars.win,
                            game.player.img, 0, 0);

    mlx_hook(game.vars.win, 2, 0, key_hook, &game);
    mlx_hook(game.vars.win, 17, 0, close_win, &game);

    mlx_loop(game.vars.mlx);
    return (0);
}
