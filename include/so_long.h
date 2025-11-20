/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmustone <mmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 15:42:11 by mmustone          #+#    #+#             */
/*   Updated: 2025/11/20 18:42:20 by mmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
#define SO_LONG_H

#include "../lib/gnl/get_next_line.h"
#include "../lib/mlx/mlx.h"
#include "../lib/libft/libft.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

typedef struct s_vars {
    void  *mlx;
    void  *win;
    int x;
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
} t_game;

int close_win(t_game *game);
void free_map(t_map *map);
int map_load(t_map *map, char *filename);
int grid_check(t_map *map);
int key_hook(int keycode, t_game *game);
int check_path(t_map *map);

#endif
