/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martinmust <martinmust@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 15:42:11 by mmustone          #+#    #+#             */
/*   Updated: 2025/11/23 17:16:14 by martinmust       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
#define SO_LONG_H

#include "../lib/gnl/get_next_line.h"
#include "../lib/mlx/mlx.h"
#include "../lib/libft/libft.h"

#include <stdlib.h>
#include <fcntl.h>

//delete
#include <string.h>
#include <stdio.h>

#define TILE_SIZE 64

typedef struct s_vars {
    void    *mlx;
    void    *win;
    int     win_width;
    int     win_height;
} t_vars;

typedef struct s_map {
    char    **grid;   // массив строк, каждая строка = одна строка карты
    int     width;    // длина строки
    int     height;   // количество строк
    int     collectiable;
    int     spawn;
    int     exit;
} t_map;

typedef struct player{
    int pos_x;
    int pos_y;
    void *img;
    int steps;
} t_player;

typedef struct s_game {
    t_vars vars;
    t_player player;
    t_map map;
    void    *img_wall;
    void    *img_floor;
    void    *img_exit;
    void    *img_key;
} t_game;

int close_win(t_game *game);
void free_map(t_map *map);
int map_load(t_map *map, char *filename);
int grid_check(t_map *map);
int key_hook(int keycode, t_game *game);
int check_path(t_map *map);
int find_player(t_map *map, int *start_y, int *start_x);
int init_textures(t_game *game);
void render_map(t_game *game);

#endif
