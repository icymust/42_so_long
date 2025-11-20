/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmustone <mmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 18:17:14 by mmustone          #+#    #+#             */
/*   Updated: 2025/11/20 18:36:52 by mmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int grid_check(t_map *map)
{
    int x;
    int y;

    map->spawn = 0;
    map->exit = 0;
    map->collectiable = 0;

    // 1. проверка верхней и нижней строки на стены
    y = 0;
    x = 0;
    while (x < map->width)
    {
        if (map->grid[0][x] != '1'
            || map->grid[map->height - 1][x] != '1')
            return (-1);
        x++;
    }

    // 2. обходим всю карту:
    //    - считаем P/E/C
    //    - проверяем боковые стены
    //    - проверяем допустимые символы
    y = 0;
    while (y < map->height)
    {
        // стены слева и справа
        if (map->grid[y][0] != '1'
            || map->grid[y][map->width - 1] != '1')
        {
            printf("Walls error\n");
            return (-1);
        }
        x = 0;
        while (x < map->width)
        {
            char c = map->grid[y][x];

            if (c == 'P')
                map->spawn++;
            else if (c == 'E')
                map->exit++;
            else if (c == 'C')
                map->collectiable++;
            else if (c != '0' && c != '1')
            {
                printf("Invalid char in map: '%c'\n", c);
                return (-1);
            }
            x++;
        }
        y++;
    }

    // 3. итоговая проверка количества P/E/C
    if (map->spawn != 1)
        return (-1);
    if (map->exit != 1)
        return (-1);
    if (map->collectiable < 1)
        return (-1);
    if (map->height == map->width)
        return(-1);
    return (0);
}

//Копия карты из грид
static char **dup_grid(t_map *map)
{
    char **copy;
    int   y;

    copy = malloc(sizeof(char *) * (map->height + 1));
    if (!copy)
        return (NULL);
    y = 0;
    while (y < map->height)
    {
        copy[y] = strdup(map->grid[y]);
        if (!copy[y])
        {
            while (--y >= 0)
                free(copy[y]);
            free(copy);
            return (NULL);
        }
        y++;
    }
    copy[y] = NULL;
    return (copy);
}

static void free_grid_copy(char **copy, int height)
{
    int y = 0;

    while (y < height)
    {
        free(copy[y]);
        y++;
    }
    free(copy);
}

static void flood_collect(char **grid, int y, int x,
    t_map *map, int *found_c)
{
    char c;

    if (y < 0 || y >= map->height || x < 0 || x >= map->width)
    return;
    c = grid[y][x];

    // блокируем стены и дверь
    if (c == '1' || c == 'E' || c == 'V')
    return;

    if (c == 'C')
    (*found_c)++;

    grid[y][x] = 'V';

    flood_collect(grid, y - 1, x, map, found_c);
    flood_collect(grid, y + 1, x, map, found_c);
    flood_collect(grid, y, x - 1, map, found_c);
    flood_collect(grid, y, x + 1, map, found_c);
}

static void flood_exit(char **grid, int y, int x,
    t_map *map, int *exit_reachable)
{
    char c;

    if (y < 0 || y >= map->height || x < 0 || x >= map->width)
    return;
    c = grid[y][x];

    // блокируем только стены и уже посещенные
    if (c == '1' || c == 'V')
    return;

    if (c == 'E')
    {
    *exit_reachable = 1;
    // можно продолжить, но можно и остановиться, если хочешь
    // return;
    }

    grid[y][x] = 'V';

    flood_exit(grid, y - 1, x, map, exit_reachable);
    flood_exit(grid, y + 1, x, map, exit_reachable);
    flood_exit(grid, y, x - 1, map, exit_reachable);
    flood_exit(grid, y, x + 1, map, exit_reachable);
}


static int find_player(t_map *map, int *start_y, int *start_x)
{
    int y;
    int x;

    y = 0;
    while (y < map->height)
    {
        x = 0;
        while (x < map->width)
        {
            if (map->grid[y][x] == 'P')
            {
                *start_y = y;
                *start_x = x;
                return (0);
            }
            x++;
        }
        y++;
    }
    return (-1);
}

// полная проверка пути:
// 1) все C достижимы без прохода через E
// 2) дверь E достижима (если ходить по 0, C, P, E)
int check_path(t_map *map)
{
    int   start_x;
    int   start_y;
    int   found_c;
    int   exit_reachable;
    char  **copy;

    if (find_player(map, &start_y, &start_x) < 0)
        return (-1);

    // 1. собираем все C, рассматривая E как стену
    copy = dup_grid(map);
    if (!copy)
        return (-1);
    found_c = 0;
    flood_collect(copy, start_y, start_x, map, &found_c);
    free_grid_copy(copy, map->height);

    if (found_c != map->collectiable)
    {
        printf("Error: not all collectibles are reachable\n");
        return (-1);
    }

    // 2. проверяем достижимость E (E проходима)
    copy = dup_grid(map);
    if (!copy)
        return (-1);
    exit_reachable = 0;
    flood_exit(copy, start_y, start_x, map, &exit_reachable);
    free_grid_copy(copy, map->height);

    if (!exit_reachable)
    {
        printf("Error: exit is not reachable\n");
        return (-1);
    }

    return (0);
}
