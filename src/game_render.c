/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martinmust <martinmust@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 16:58:23 by martinmust        #+#    #+#             */
/*   Updated: 2025/11/23 18:45:16 by martinmust       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int init_textures(t_game *game)
{
    int w, h;

    if (!game || !game->vars.mlx)
        return (0);

    game->img_wall  = mlx_png_file_to_image(game->vars.mlx, "textures/wall.png",  &w, &h);
    if (!game->img_wall) { fprintf(stderr, "Failed load: textures/wall.png\n"); return 0; }

    game->img_floor = mlx_png_file_to_image(game->vars.mlx, "textures/floor.png", &w, &h);
    if (!game->img_floor) { fprintf(stderr, "Failed load: textures/floor.png\n"); return 0; }

    game->img_exit  = mlx_png_file_to_image(game->vars.mlx, "textures/exit.png",  &w, &h);
    if (!game->img_exit) { fprintf(stderr, "Failed load: textures/exit.png\n"); return 0; }

    game->img_key  = mlx_png_file_to_image(game->vars.mlx, "textures/key.png",  &w, &h);
    if (!game->img_key) { fprintf(stderr, "Failed load: textures/key.png\n"); return 0; }

    game->player.img = mlx_png_file_to_image(game->vars.mlx, "textures/player.png", &w, &h);
    if (!game->player.img) { fprintf(stderr, "Failed load: textures/player.png\n"); return 0; }

    return 1;
}

void render_map(t_game *game)
{
    t_map *map;
    int x, y;
    void *img;
    int px, py;

    if (!game || !game->vars.mlx || !game->vars.win)
        return;
    map = &game->map;
    y = 0;
    while (y < map->height)
    {
        x = 0;
        while (x < map->width)
        {
            char c = map->grid[y][x];
            px = x * TILE_SIZE;
            py = y * TILE_SIZE;
            img = NULL;
            if (c == '1')
                img = game->img_wall;
            else if (c == '0')
                img = game->img_floor;
            else if (c == 'E')
                img = game->img_exit;
            else if (c == 'C')
                img = game->img_key;
            else if (c == 'P')
                img = game->player.img;
            else
                img = game->img_floor;
            if (img)
                mlx_put_image_to_window(game->vars.mlx, game->vars.win, img, px, py);
            x++;
        }
        y++;
    }
}
